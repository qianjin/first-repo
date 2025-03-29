#ifndef _COMMAND_H
#define _COMMAND_H

#include "main.h"
#include "motor.h"

/****************************���ݳ���*************************/
#define TX_BUFF_LENTH 42
#define Engine_Control_BUFF_LENTH 16
#define PID_BUFF_LENTH 48
#define	Motion_Control_BUFF_LENTH	12
#define Handle_BUFF_LENTH	5
#define Servo_BUFF_LENTH	8
#define Mode_BUFF_LENTH	1

/****************************����ͷ***************************/
#define 			Startbit_Motion					  	0xAA		//�˶���Ϣ
#define 			Startbit_PIDData					0xAC		//PID����(����)
#define 			Startbit_Engine_Control 	 		0xBA		//�������
#define 			Startbit_Mode						0xBB		//ģʽѡ��
#define				Startbit_Motion_Control				0xBC		//�˶�����
#define				Startbit_Handle						0xBE		//�ֱ�����
//#define				Startbit_Camera						0xCC		//����ͷ
#define				Startbit_Servo						0xDC		//��е��


/****************************������������**************************/
/*
Ϊʲôʹ�������壿
�������ڸ���Ա����ʼ��ַ����ͬ�ģ���Ҳ����ζ�ţ����������нṹ���ÿһ����Ա���ֽ���ʽ��
��������������������һ��������ʼ��ַ��ͬ���ֽ���������ʾ��������ɷǳ������ʵ�ָ��ָ�ʽ
���������ֽڸ�ʽ֮���ת����
*/

typedef union {
	struct
		{
			int16_t engine1;		//
			int16_t engine2;
			int16_t engine3;
			int16_t engine4;			
			int16_t engine5;
			int16_t engine6;
			int16_t engine7;
			int16_t engine8;
			
			float angle_x;
			float angle_y;
			float gyro_x;
			float gyro_y;
			float gyro_z;
			float deapth;
			
			uint16_t mode;				//
			
//			uint16_t servo1;
//			uint16_t servo2;
//			uint16_t servo3;
//			uint16_t servo4;
		}motiondata;
uint8_t TX_Buff[TX_BUFF_LENTH];
}TX_Motion_Buff_Union;//ROV�˶���Ϣ������ROV����


typedef union {
	struct
		{
			float pitch_P;
			float pitch_I;
			float pitch_D;
			float pitch_w_P;
			float pitch_w_I;
			float pitch_w_D;
			float depth_P;
			float depth_I;
			float depth_D;	
			float yaw_w_P;
			float yaw_w_I;
			float yaw_w_D;	
		}piddata;
uint8_t Buff[PID_BUFF_LENTH];
}PID_Buff_Union;//PID���������ڷ��ͺͽ���


typedef union {
	struct
		{
			float depth_set;
			float pitch_set;
			float yaw_w_set;
		
		}setpara;
uint8_t Buff[Motion_Control_BUFF_LENTH];
}Motion_Contorl_Buff_Union;//PID�趨Ŀ��ֵ�����ڷ��ͺͽ���


typedef union {
	struct
		{
			int16_t engine1;
			int16_t engine2;
			int16_t engine3;
			int16_t engine4;
			int16_t engine5;
			int16_t engine6;
			int16_t engine7;
			int16_t engine8;
		}engine;
uint8_t RX_Buff[Engine_Control_BUFF_LENTH];
}RX_Engine_Control_Buff_Union;//ROV����趨ֵ������ROV����


typedef union 
{
	uint8_t mode;
	uint8_t RX_Buff[1];
}RX_Mode_Buff_Union;//ROV����ģʽ������ROV����


typedef union {
	struct
		{
			uint8_t left_x;			//�ֱ�ģ����
			uint8_t left_y;
			uint8_t right_x;
			uint8_t right_y;
			uint8_t Key;
		}handle;
uint8_t Buff[80];
}Handle_Buff_Union;//��λ�����ƶ˷������ֱ�ҡ����Ϣ������ROV����

//typedef union {
//	struct
//		{
//			uint16_t	servo1;
//			uint16_t	servo2;
//			uint16_t	servo3;
//			uint16_t	servo4;
//		}data;
//uint8_t Buff[Servo_BUFF_LENTH];
//}Servo_Buff_Union;//ROV�ĸ�������г̰ٷֱȣ����ڷ��ͺͽ���



extern uint8_t SendDataFlag_PID;//PID���ݷ��ͱ�־λ

/******************************��������*********************************/
void Engine_DataHandler(RX_Engine_Control_Buff_Union rx_data);
void Command_Handler(uint8_t);
void UpdateStatus(uint8_t startbit);
void PID_DataHandler(PID_Buff_Union pid_data);
void Setpara_Handler(Motion_Contorl_Buff_Union setpara_data);
float ByteToFloat(unsigned char *p);
void FloatToByte(float floatNum, unsigned char *byteArry);


void Command_Handler_R(uint8_t Data);


#endif

