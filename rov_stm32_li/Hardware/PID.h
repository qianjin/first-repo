#ifndef _PID_H
#define _PID_H
#include "main.h"

struct PID//PID�ṹ��
{
	float kP;//����
	float kI;
	float kD;
	//float dt;
	float P;//��Ӧ���
	float I;
	float D;
	float set;//Ŀ���趨ֵ
	float feedback;//��ǰֵ
	float last_error;//�ϴ����
	float error;//�������
	float derror;//���΢��
	float Imax;//�������
	float outmax;//������ֵ
	float out;//���������
	float fuzzy_interval;//ģ�����䳤��
};

void PIDdataInit(struct PID* pidData,float kp,float ki,float kd,float imax,float outmax,float fuzzy_interval);
void PIDUpData(struct PID* pidData);
void ResetI(struct PID* pidData);
void ResetPID(struct PID* pidData);
void GetP(struct PID* pidData);
void GetPD(struct PID* pidData);
void GetPI(struct PID* pidData);
void GetPID(struct PID* pidData);
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high) ;

#endif
