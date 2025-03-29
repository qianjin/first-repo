#ifndef _PID_H
#define _PID_H
#include "main.h"

struct PID//PID结构体
{
	float kP;//参数
	float kI;
	float kD;
	//float dt;
	float P;//相应输出
	float I;
	float D;
	float set;//目标设定值
	float feedback;//当前值
	float last_error;//上次误差
	float error;//本次误差
	float derror;//误差微分
	float Imax;//积分输出
	float outmax;//输出最大值
	float out;//最终输出量
	float fuzzy_interval;//模糊区间长度
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
