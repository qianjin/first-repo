#ifndef _MOTION_H
#define _MOTION_H

#include "main.h"


extern uint16_t control_mode;

#define		MODE_PID				0x0080//PID模式相关位
#define		MODE_HANDLE			0x0008//手柄控制相关位

#define   ON							1
#define   OFF							0

extern struct PID pidData_pitch;
extern struct PID pidData_roll;

extern struct PID pidData_pitch_w;//俯仰角角加速度
extern struct PID pidData_roll_w;
extern struct PID pidData_yaw_w;//偏航角角加速度

extern struct PID pidData_depth;

extern int16_t handle_speed_forward;	//手柄对应的前进速度


typedef struct
{
	uint8_t left_x;
	uint8_t left_y;
	uint8_t right_x;
	uint8_t right_y;
	uint8_t Key;
}Handle;//手柄信息结构体，摇杆模拟量

extern Handle handle;

void Control_Inner_loop(void);
void Control_Outter_loop(void);
void Control_Init(void);
uint8_t Ismode(uint16_t mode);
void Control_Setmode(uint16_t mode,uint8_t state);
void Control_Handle(void);

#endif
