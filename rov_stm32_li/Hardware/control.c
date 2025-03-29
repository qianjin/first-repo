/************************************控制程序相关代码********************************/
/*
功能：ROV模式设定，双环控制代码、手柄控制和外设控制代码
*/

#include "control.h"
#include "JY901.h"
#include "MS5837.h"
#include "PID.h"
#include "motor.h"
#include "command.h"
#include "math.h"
#include "Delay.h"

uint16_t control_mode=0x0000;//ROV模式字，16位对应16种模式。本工程中仅使用了两种

struct PID pidData_pitch;//PID结构体 俯仰角
struct PID pidData_pitch_w;//PID结构体 俯仰角角加速度
struct PID pidData_yaw_w;//PID结构体 偏航角角加速度
struct PID pidData_depth;////PID结构体 深度

Handle handle={128,128,128,128};//手柄四个轴量初始化为中位值

int16_t handle_speed_forward;//手柄对应的前进速度

/*
控制程序初始化函数，开机运行
*/
void Control_Init(void)
{
	Control_Setmode(MODE_PID,OFF);//关闭PID模式
	Control_Setmode(MODE_HANDLE,ON);//开启手柄控制模式
	
	//	PID初始化函数 KP KI KD 积分最大值 输出最大值 模糊区间（误差）
	PIDdataInit(&pidData_depth,30,0.3,120,500,999,0.4);//四路PID初始化，设定相关参数
	PIDdataInit(&pidData_pitch_w,40,0,50,500,999,0.3);
	PIDdataInit(&pidData_pitch,3,0,0.1,15,60,0.3);
	PIDdataInit(&pidData_yaw_w,60,0.5,10,300,999,0.15);
	
	UpdateStatus(Startbit_Motion);
//	UpdateStatus(Startbit_PIDData);//开机发送PID参数
//	UpdateStatus(Startbit_PIDData);
}

/*
 内环控制 100Hz 控制对象：深度、俯仰角角加速度、偏航角角加速度
*/
void Control_Inner_loop(void)
{
	pidData_depth.feedback=MS5837_Val.depth;//深度PID控制当前反馈值为水深传感器数值
	pidData_pitch_w.feedback=JY901_val.gyro_x;//俯仰角角加速度PID控制当前反馈值为JY901X轴角加速度
	pidData_yaw_w.feedback=JY901_val.gyro_z;//偏航角角加速度PID控制当前反馈值为JY901Z轴角加速度 顺时针为正
	
	PIDUpData(&pidData_depth);//对外环三个参数进行PID计算
	PIDUpData(&pidData_pitch_w);
	PIDUpData(&pidData_yaw_w);
		
	GetPID(&pidData_depth);//得到PID输出值
	GetPID(&pidData_pitch_w);
	GetPID(&pidData_yaw_w);

/****************ROV电机排布示意图***************/
/*
电机1：正 电机2：正      电机(3):反  电机(4):正  
电机(5)：正 电机(6)：反  电机7:反  电机8:反

 --------—----
|    1   2 	  |	
|		 	  |
|  3       4  |
|  5       6  |
|			  | 
|    7   8    |
 --------------
 电机1(正)：正 电机2：正      电机(3):反  电机(4):反
电机(5)：正 电机(6)：反  

 --------—----
|   2    1 	  |	
|		 	  |
|   6    5    |
|             |
|	4	 3	  | 
|             |
 --------------
*/
/***********************************************/

//	//反
//	Motor.motor3_speed=constrain_int32(pidData_depth.out,-999,999);//3号电机主管沉浮	
//	Motor.motor6_speed=constrain_int32(pidData_depth.out,-999,999);//6号电机主管沉浮
	Motor.motor5_speed=constrain_int32(pidData_depth.out,999,999);//5号电机主管沉浮	
	Motor.motor6_speed=constrain_int32(pidData_depth.out,-999,999);//6号电机主管沉浮

//	//正
//	Motor.motor4_speed=constrain_int32(pidData_pitch_w.out,-999,999);//4号电机主管俯仰
//	Motor.motor5_speed=constrain_int32(pidData_pitch_w.out,-999,999);//5号电机主管俯仰
//	
//	//反
//	Motor.motor7_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在前进速度上输出到尾部两个水平电机上
//	Motor.motor8_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在前进速度上输出到尾部两个水平电机上
	Motor.motor4_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在前进速度上输出到尾部两个水平电机上
	Motor.motor3_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在前进速度上输出到尾部两个水平电机上

//	
//	//正
//	Motor.motor1_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在速度上输出到头部两个水平电机上
//	Motor.motor2_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在速度上输出到头部两个水平电机上
	Motor.motor2_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在速度上输出到头部两个水平电机上
	Motor.motor1_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//偏航角角加速度叠加在速度上输出到头部两个水平电机上	
}

/*
 外环控制 50Hz 控制对象：俯仰角
*/
void Control_Outter_loop(void)
{
	pidData_pitch.feedback=JY901_val.angle_x;//俯仰角PID控制当前反馈值为JY901X轴角度
	PIDUpData(&pidData_pitch);//计算PID
	GetPID(&pidData_pitch);//获得PID输出值
	pidData_pitch_w.set = pidData_pitch.out;//赋值俯仰角PID输出值为俯仰角角加速度PID设定值
}

/*
判断ROV当前工作模式是否为mode
通过读取control_mode变量的相关位
如果是mode，返回1；不是，则返回0
*/
uint8_t Ismode(uint16_t mode)
{
	if(control_mode&mode)
			return 1;
	else
			return 0;
}

/*
设定ROV当前工作模式的mode为state状态（ON/OFF）
通过设定control_mode的相关位
*/
void Control_Setmode(uint16_t mode,uint8_t state)
{
	if(state==ON)
		control_mode|=mode;
	else
		control_mode&=~mode;
}

/*
手柄控制函数
用于在上位机连接手柄并发送手柄信号时对ROV运动进行控制
*/
void Control_Handle(void)
{
//	uint8_t KeyData;
	
//	KeyData=handle.Key;
	
	//长按2秒启动电机
//	if(KeyData == 5)
//	{
//		delay_ms(2000);
//		if(KeyData == 5)
//		{
//			Motor_SetOne();
//			delay_ms(1500);
//			Motor_SetTwo();
//			delay_ms(1000);
//			Motor_SetLow();
//		}
//	}
	
	int16_t speed_up;//上升速度
	int16_t speed_front;//前进速度
	int16_t speed_left;//左转速度

	float left_y;//摇杆左摇柄y值，-1~0~1对应正~中~反，下同
	float right_x;
	float right_y;

	left_y=((float)handle.left_y)/128.0F-1;//将单字节手柄信息（0~255）归一化转换成-1~1的浮点
	right_x=((float)handle.right_x)/128.0F-1;
	right_y=((float)handle.right_y)/128.0F-1;	//1 …… -1

	speed_up=left_y*999.0F;//上浮速度设定
	speed_front=right_y*999.0F;//前进速度设定
	speed_left=right_x*999.0F;//左转速度设定
	
	if(!Ismode(MODE_PID))//如果没有打开PID控制模式
	{
		Motor.motor5_speed=-speed_up;//沉浮由36号电机主管
		Motor.motor6_speed=-speed_up;
	
//		Motor.motor4_speed=-speed_up/5;//45号电机匹配沉浮输出功率，估算为五分之一可保持平衡,大小待定
//		Motor.motor5_speed=-speed_up/5;
		
//		Motor.motor2_speed=constrain_int32(speed_front + speed_left,-999,999);//右转
// 		Motor.motor7_speed=constrain_int32(-speed_front + speed_left,-999,999);
		Motor.motor1_speed=constrain_int32(speed_front + speed_left,-999,999);//右转
 		Motor.motor4_speed=constrain_int32(-speed_front + speed_left,-999,999);
//		Motor.motor1_speed=constrain_int32(-speed_front + speed_left,-999,999);//左转
//		Motor.motor8_speed=constrain_int32(speed_front + speed_left,-999,999);
		Motor.motor2_speed=constrain_int32(-speed_front + speed_left,-999,999);//左转
		Motor.motor3_speed=constrain_int32(speed_front + speed_left,-999,999);
		
	}
	else
	{
		handle_speed_forward=speed_front;//手柄前进速度为前进速度设定
		pidData_yaw_w.set=right_x*-40;//偏航角角加速度设定值为右摇杆x轴乘以-40
	}
}
