#ifndef _COMMAND_H
#define _COMMAND_H

#include "main.h"
#include "motor.h"

/****************************数据长度*************************/
#define TX_BUFF_LENTH 42
#define Engine_Control_BUFF_LENTH 16
#define PID_BUFF_LENTH 48
#define	Motion_Control_BUFF_LENTH	12
#define Handle_BUFF_LENTH	5
#define Servo_BUFF_LENTH	8
#define Mode_BUFF_LENTH	1

/****************************数据头***************************/
#define 			Startbit_Motion					  	0xAA		//运动信息
#define 			Startbit_PIDData					0xAC		//PID数据(调参)
#define 			Startbit_Engine_Control 	 		0xBA		//电机控制
#define 			Startbit_Mode						0xBB		//模式选择
#define				Startbit_Motion_Control				0xBC		//运动控制
#define				Startbit_Handle						0xBE		//手柄数据
//#define				Startbit_Camera						0xCC		//摄像头
#define				Startbit_Servo						0xDC		//机械臂


/****************************各数据联合体**************************/
/*
为什么使用联合体？
联合体内各成员的起始地址是相同的，这也就意味着，在联合体中结构体的每一个成员的字节形式，
都可以由联合体中另外一个和它起始地址相同的字节数组来表示。这样便可非常方便的实现各种格式
的数据与字节格式之间的转换。
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
}TX_Motion_Buff_Union;//ROV运动信息，用于ROV发送


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
}PID_Buff_Union;//PID参数，用于发送和接收


typedef union {
	struct
		{
			float depth_set;
			float pitch_set;
			float yaw_w_set;
		
		}setpara;
uint8_t Buff[Motion_Control_BUFF_LENTH];
}Motion_Contorl_Buff_Union;//PID设定目标值，用于发送和接收


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
}RX_Engine_Control_Buff_Union;//ROV电机设定值，用于ROV接收


typedef union 
{
	uint8_t mode;
	uint8_t RX_Buff[1];
}RX_Mode_Buff_Union;//ROV工作模式，用于ROV接收


typedef union {
	struct
		{
			uint8_t left_x;			//手柄模拟量
			uint8_t left_y;
			uint8_t right_x;
			uint8_t right_y;
			uint8_t Key;
		}handle;
uint8_t Buff[80];
}Handle_Buff_Union;//上位机控制端发来的手柄摇杆信息，用于ROV接收

//typedef union {
//	struct
//		{
//			uint16_t	servo1;
//			uint16_t	servo2;
//			uint16_t	servo3;
//			uint16_t	servo4;
//		}data;
//uint8_t Buff[Servo_BUFF_LENTH];
//}Servo_Buff_Union;//ROV四个舵机的行程百分比，用于发送和接收



extern uint8_t SendDataFlag_PID;//PID数据发送标志位

/******************************函数声明*********************************/
void Engine_DataHandler(RX_Engine_Control_Buff_Union rx_data);
void Command_Handler(uint8_t);
void UpdateStatus(uint8_t startbit);
void PID_DataHandler(PID_Buff_Union pid_data);
void Setpara_Handler(Motion_Contorl_Buff_Union setpara_data);
float ByteToFloat(unsigned char *p);
void FloatToByte(float floatNum, unsigned char *byteArry);


void Command_Handler_R(uint8_t Data);


#endif

