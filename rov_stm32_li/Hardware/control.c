/************************************���Ƴ�����ش���********************************/
/*
���ܣ�ROVģʽ�趨��˫�����ƴ��롢�ֱ����ƺ�������ƴ���
*/

#include "control.h"
#include "JY901.h"
#include "MS5837.h"
#include "PID.h"
#include "motor.h"
#include "command.h"
#include "math.h"
#include "Delay.h"

uint16_t control_mode=0x0000;//ROVģʽ�֣�16λ��Ӧ16��ģʽ���������н�ʹ��������

struct PID pidData_pitch;//PID�ṹ�� ������
struct PID pidData_pitch_w;//PID�ṹ�� �����ǽǼ��ٶ�
struct PID pidData_yaw_w;//PID�ṹ�� ƫ���ǽǼ��ٶ�
struct PID pidData_depth;////PID�ṹ�� ���

Handle handle={128,128,128,128};//�ֱ��ĸ�������ʼ��Ϊ��λֵ

int16_t handle_speed_forward;//�ֱ���Ӧ��ǰ���ٶ�

/*
���Ƴ����ʼ����������������
*/
void Control_Init(void)
{
	Control_Setmode(MODE_PID,OFF);//�ر�PIDģʽ
	Control_Setmode(MODE_HANDLE,ON);//�����ֱ�����ģʽ
	
	//	PID��ʼ������ KP KI KD �������ֵ ������ֵ ģ�����䣨��
	PIDdataInit(&pidData_depth,30,0.3,120,500,999,0.4);//��·PID��ʼ�����趨��ز���
	PIDdataInit(&pidData_pitch_w,40,0,50,500,999,0.3);
	PIDdataInit(&pidData_pitch,3,0,0.1,15,60,0.3);
	PIDdataInit(&pidData_yaw_w,60,0.5,10,300,999,0.15);
	
	UpdateStatus(Startbit_Motion);
//	UpdateStatus(Startbit_PIDData);//��������PID����
//	UpdateStatus(Startbit_PIDData);
}

/*
 �ڻ����� 100Hz ���ƶ�����ȡ������ǽǼ��ٶȡ�ƫ���ǽǼ��ٶ�
*/
void Control_Inner_loop(void)
{
	pidData_depth.feedback=MS5837_Val.depth;//���PID���Ƶ�ǰ����ֵΪˮ�������ֵ
	pidData_pitch_w.feedback=JY901_val.gyro_x;//�����ǽǼ��ٶ�PID���Ƶ�ǰ����ֵΪJY901X��Ǽ��ٶ�
	pidData_yaw_w.feedback=JY901_val.gyro_z;//ƫ���ǽǼ��ٶ�PID���Ƶ�ǰ����ֵΪJY901Z��Ǽ��ٶ� ˳ʱ��Ϊ��
	
	PIDUpData(&pidData_depth);//���⻷������������PID����
	PIDUpData(&pidData_pitch_w);
	PIDUpData(&pidData_yaw_w);
		
	GetPID(&pidData_depth);//�õ�PID���ֵ
	GetPID(&pidData_pitch_w);
	GetPID(&pidData_yaw_w);

/****************ROV����Ų�ʾ��ͼ***************/
/*
���1���� ���2����      ���(3):��  ���(4):��  
���(5)���� ���(6)����  ���7:��  ���8:��

 --------��----
|    1   2 	  |	
|		 	  |
|  3       4  |
|  5       6  |
|			  | 
|    7   8    |
 --------------
 ���1(��)���� ���2����      ���(3):��  ���(4):��
���(5)���� ���(6)����  

 --------��----
|   2    1 	  |	
|		 	  |
|   6    5    |
|             |
|	4	 3	  | 
|             |
 --------------
*/
/***********************************************/

//	//��
//	Motor.motor3_speed=constrain_int32(pidData_depth.out,-999,999);//3�ŵ�����ܳ���	
//	Motor.motor6_speed=constrain_int32(pidData_depth.out,-999,999);//6�ŵ�����ܳ���
	Motor.motor5_speed=constrain_int32(pidData_depth.out,999,999);//5�ŵ�����ܳ���	
	Motor.motor6_speed=constrain_int32(pidData_depth.out,-999,999);//6�ŵ�����ܳ���

//	//��
//	Motor.motor4_speed=constrain_int32(pidData_pitch_w.out,-999,999);//4�ŵ�����ܸ���
//	Motor.motor5_speed=constrain_int32(pidData_pitch_w.out,-999,999);//5�ŵ�����ܸ���
//	
//	//��
//	Motor.motor7_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ�����ǰ���ٶ��������β������ˮƽ�����
//	Motor.motor8_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ�����ǰ���ٶ��������β������ˮƽ�����
	Motor.motor4_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ�����ǰ���ٶ��������β������ˮƽ�����
	Motor.motor3_speed=constrain_int32(handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ�����ǰ���ٶ��������β������ˮƽ�����

//	
//	//��
//	Motor.motor1_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ������ٶ��������ͷ������ˮƽ�����
//	Motor.motor2_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ������ٶ��������ͷ������ˮƽ�����
	Motor.motor2_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ������ٶ��������ͷ������ˮƽ�����
	Motor.motor1_speed=constrain_int32(-handle_speed_forward + pidData_yaw_w.out,-999,999);//ƫ���ǽǼ��ٶȵ������ٶ��������ͷ������ˮƽ�����	
}

/*
 �⻷���� 50Hz ���ƶ��󣺸�����
*/
void Control_Outter_loop(void)
{
	pidData_pitch.feedback=JY901_val.angle_x;//������PID���Ƶ�ǰ����ֵΪJY901X��Ƕ�
	PIDUpData(&pidData_pitch);//����PID
	GetPID(&pidData_pitch);//���PID���ֵ
	pidData_pitch_w.set = pidData_pitch.out;//��ֵ������PID���ֵΪ�����ǽǼ��ٶ�PID�趨ֵ
}

/*
�ж�ROV��ǰ����ģʽ�Ƿ�Ϊmode
ͨ����ȡcontrol_mode���������λ
�����mode������1�����ǣ��򷵻�0
*/
uint8_t Ismode(uint16_t mode)
{
	if(control_mode&mode)
			return 1;
	else
			return 0;
}

/*
�趨ROV��ǰ����ģʽ��modeΪstate״̬��ON/OFF��
ͨ���趨control_mode�����λ
*/
void Control_Setmode(uint16_t mode,uint8_t state)
{
	if(state==ON)
		control_mode|=mode;
	else
		control_mode&=~mode;
}

/*
�ֱ����ƺ���
��������λ�������ֱ��������ֱ��ź�ʱ��ROV�˶����п���
*/
void Control_Handle(void)
{
//	uint8_t KeyData;
	
//	KeyData=handle.Key;
	
	//����2���������
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
	
	int16_t speed_up;//�����ٶ�
	int16_t speed_front;//ǰ���ٶ�
	int16_t speed_left;//��ת�ٶ�

	float left_y;//ҡ����ҡ��yֵ��-1~0~1��Ӧ��~��~������ͬ
	float right_x;
	float right_y;

	left_y=((float)handle.left_y)/128.0F-1;//�����ֽ��ֱ���Ϣ��0~255����һ��ת����-1~1�ĸ���
	right_x=((float)handle.right_x)/128.0F-1;
	right_y=((float)handle.right_y)/128.0F-1;	//1 ���� -1

	speed_up=left_y*999.0F;//�ϸ��ٶ��趨
	speed_front=right_y*999.0F;//ǰ���ٶ��趨
	speed_left=right_x*999.0F;//��ת�ٶ��趨
	
	if(!Ismode(MODE_PID))//���û�д�PID����ģʽ
	{
		Motor.motor5_speed=-speed_up;//������36�ŵ������
		Motor.motor6_speed=-speed_up;
	
//		Motor.motor4_speed=-speed_up/5;//45�ŵ��ƥ�����������ʣ�����Ϊ���֮һ�ɱ���ƽ��,��С����
//		Motor.motor5_speed=-speed_up/5;
		
//		Motor.motor2_speed=constrain_int32(speed_front + speed_left,-999,999);//��ת
// 		Motor.motor7_speed=constrain_int32(-speed_front + speed_left,-999,999);
		Motor.motor1_speed=constrain_int32(speed_front + speed_left,-999,999);//��ת
 		Motor.motor4_speed=constrain_int32(-speed_front + speed_left,-999,999);
//		Motor.motor1_speed=constrain_int32(-speed_front + speed_left,-999,999);//��ת
//		Motor.motor8_speed=constrain_int32(speed_front + speed_left,-999,999);
		Motor.motor2_speed=constrain_int32(-speed_front + speed_left,-999,999);//��ת
		Motor.motor3_speed=constrain_int32(speed_front + speed_left,-999,999);
		
	}
	else
	{
		handle_speed_forward=speed_front;//�ֱ�ǰ���ٶ�Ϊǰ���ٶ��趨
		pidData_yaw_w.set=right_x*-40;//ƫ���ǽǼ��ٶ��趨ֵΪ��ҡ��x�����-40
	}
}
