/************************************时间片轮转相关代码********************************/
/*
功能：根据实际定时器，按照不同频率运行相应ROV代码
*/
#include "usart1.h"
#include "usart2.h"
//#include "timbase.h"
#include "PID.h"
#include "motor.h"
#include "JY901.h"
#include "MS5837.h"
#include "command.h"
#include "Scheduler.h"
#include "control.h"
//#include "camera.h"
#include "math.h"
//#include "servo.h"

struct ROVScheduler scheduler={0,0,0,0,0,0};//ROV时间片结构体初始化



static void Loop_200Hz(void)	//5ms执行一次 接收数据并处理
{	

		
}

static void Loop_100Hz(void)	//10ms执行一次
{	
	if(Ismode(MODE_PID))//如果是PID模式
	Control_Inner_loop();//进行PID运算

	MS5837_Read();	//水深传感器读取参数
}

static void Loop_50Hz(void)	//20ms执行一次
{
	if(Ismode(MODE_PID))//如果是PID模式
		Control_Outter_loop();//外环控制50Hz
	else//如果不是PID控制模式
	{
		ResetPID(&pidData_pitch);//清零所有PID输出
		ResetPID(&pidData_pitch_w);
		ResetPID(&pidData_yaw_w);
		ResetPID(&pidData_depth);
	}
//	Camera_SetPercent(camera_angle);//摄像头舵机设置角度
	Motor_fun();//电机设置转速
//	Servo_fun();//舵机设置角度	
}

static void Loop_20Hz(void)	//50ms执行一次
{

	if(Ismode(MODE_HANDLE))//如果是手柄控制模式
	{
		Control_Handle();//手柄控制函数
	}
}

static void Loop_10Hz(void)	//100ms执行一次
{
//	UpdateStatus(Startbit_Motion);//上传运动姿态信息
	
	
//	UpdateStatus(Startbit_Motion_Control);//上传PID目标设定值
//	if(SendDataFlag_PID==1)//如果PID数据发送标志位为一，则向上位机发送PID参数数据
//	{
//		UpdateStatus(Startbit_PIDData);//向上位机发送PID参数数据
//		SendDataFlag_PID=0;//PID数据发送标志位置零
//	}
}

static void Loop_1Hz(void)//1000ms执行一次
{
//	static uint8_t i=0;
//	i++;
//	if(i==10)
//	{
//		i=0;
//		UpdateStatus(Startbit_PIDData);//每十秒发送一次PID设定指令
//	}
//	
}

//控制策略 分时控制，通过判定不同计数值大小运行不同频率的代码服务
void ROV_Loop(void)
{
	if(scheduler.cnt_5ms >= 5){
		Loop_200Hz();
		scheduler.cnt_5ms = 0;
	}		
	if(scheduler.cnt_10ms >= 10){	
		Loop_100Hz();
		scheduler.cnt_10ms = 0;
	}
	if(scheduler.cnt_20ms >= 20){		
		Loop_50Hz();
		scheduler.cnt_20ms = 0;
	}
	if(scheduler.cnt_50ms >= 50){		
		Loop_20Hz();
		scheduler.cnt_50ms = 0;
	}
	if(scheduler.cnt_100ms >= 100){		
		Loop_10Hz();
		scheduler.cnt_100ms = 0;
	}
	if(scheduler.cnt_1000ms >= 1000){		
		Loop_1Hz();
		scheduler.cnt_1000ms = 0;
	}		
}

/*
时间片计数函数，在中断中进行调用。由于时基定时器频率为200Hz，故自增数量为5
*/
void Scheduler_Counter(void)
{
	scheduler.cnt_5ms+=5;
	scheduler.cnt_10ms+=5;
	scheduler.cnt_20ms+=5;
	scheduler.cnt_50ms+=5;
	scheduler.cnt_100ms+=5;
	scheduler.cnt_1000ms+=5;
}

//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//获取中断标志位
//	{
//		Scheduler_Counter();
//		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志位
//	}
//}

