#ifndef _MOTION_H
#define _MOTION_H

#include "main.h"


extern uint16_t control_mode;

#define		MODE_PID				0x0080//PIDģʽ���λ
#define		MODE_HANDLE			0x0008//�ֱ��������λ

#define   ON							1
#define   OFF							0

extern struct PID pidData_pitch;
extern struct PID pidData_roll;

extern struct PID pidData_pitch_w;//�����ǽǼ��ٶ�
extern struct PID pidData_roll_w;
extern struct PID pidData_yaw_w;//ƫ���ǽǼ��ٶ�

extern struct PID pidData_depth;

extern int16_t handle_speed_forward;	//�ֱ���Ӧ��ǰ���ٶ�


typedef struct
{
	uint8_t left_x;
	uint8_t left_y;
	uint8_t right_x;
	uint8_t right_y;
	uint8_t Key;
}Handle;//�ֱ���Ϣ�ṹ�壬ҡ��ģ����

extern Handle handle;

void Control_Inner_loop(void);
void Control_Outter_loop(void);
void Control_Init(void);
uint8_t Ismode(uint16_t mode);
void Control_Setmode(uint16_t mode,uint8_t state);
void Control_Handle(void);

#endif
