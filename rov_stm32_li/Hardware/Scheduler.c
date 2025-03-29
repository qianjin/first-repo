/************************************ʱ��Ƭ��ת��ش���********************************/
/*
���ܣ�����ʵ�ʶ�ʱ�������ղ�ͬƵ��������ӦROV����
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

struct ROVScheduler scheduler={0,0,0,0,0,0};//ROVʱ��Ƭ�ṹ���ʼ��



static void Loop_200Hz(void)	//5msִ��һ�� �������ݲ�����
{	

		
}

static void Loop_100Hz(void)	//10msִ��һ��
{	
	if(Ismode(MODE_PID))//�����PIDģʽ
	Control_Inner_loop();//����PID����

	MS5837_Read();	//ˮ�������ȡ����
}

static void Loop_50Hz(void)	//20msִ��һ��
{
	if(Ismode(MODE_PID))//�����PIDģʽ
		Control_Outter_loop();//�⻷����50Hz
	else//�������PID����ģʽ
	{
		ResetPID(&pidData_pitch);//��������PID���
		ResetPID(&pidData_pitch_w);
		ResetPID(&pidData_yaw_w);
		ResetPID(&pidData_depth);
	}
//	Camera_SetPercent(camera_angle);//����ͷ������ýǶ�
	Motor_fun();//�������ת��
//	Servo_fun();//������ýǶ�	
}

static void Loop_20Hz(void)	//50msִ��һ��
{

	if(Ismode(MODE_HANDLE))//������ֱ�����ģʽ
	{
		Control_Handle();//�ֱ����ƺ���
	}
}

static void Loop_10Hz(void)	//100msִ��һ��
{
//	UpdateStatus(Startbit_Motion);//�ϴ��˶���̬��Ϣ
	
	
//	UpdateStatus(Startbit_Motion_Control);//�ϴ�PIDĿ���趨ֵ
//	if(SendDataFlag_PID==1)//���PID���ݷ��ͱ�־λΪһ��������λ������PID��������
//	{
//		UpdateStatus(Startbit_PIDData);//����λ������PID��������
//		SendDataFlag_PID=0;//PID���ݷ��ͱ�־λ����
//	}
}

static void Loop_1Hz(void)//1000msִ��һ��
{
//	static uint8_t i=0;
//	i++;
//	if(i==10)
//	{
//		i=0;
//		UpdateStatus(Startbit_PIDData);//ÿʮ�뷢��һ��PID�趨ָ��
//	}
//	
}

//���Ʋ��� ��ʱ���ƣ�ͨ���ж���ͬ����ֵ��С���в�ͬƵ�ʵĴ������
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
ʱ��Ƭ�������������ж��н��е��á�����ʱ����ʱ��Ƶ��Ϊ200Hz������������Ϊ5
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
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//��ȡ�жϱ�־λ
//	{
//		Scheduler_Counter();
//		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־λ
//	}
//}

