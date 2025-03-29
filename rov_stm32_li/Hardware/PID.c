/************************************PID自动控制代码********************************/
/*
PID自动控制代码，运用面向对象的编程思想，用结构体表示各个PID运算
*/


#include "PID.h"
#include "math.h"



//限幅函数，参数：输入值，限定最小值，限定最大值
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high) 
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//PID初始化函数，设置kp ki kd 积分最大值 输出最大值 模糊区间（目标值和当前值差值绝对值小于模糊区间长度时，不进行调节）
void PIDdataInit(struct PID* pidData,float kp,float ki,float kd,float imax,float outmax,float fuzzy_interval)
{
	pidData->Imax=imax;
	pidData->outmax=outmax;
	pidData->kP=kp;
	pidData->kI=ki;
	pidData->kD=kd;
	pidData->P=0;
	pidData->I=0;
	pidData->D=0;
	pidData->error=0;
	pidData->last_error=0;
	pidData->derror=0;
	//pidData->set=0;
	pidData->out=0;
	pidData->fuzzy_interval=fuzzy_interval;
}

//PID计算函数
void PIDUpData(struct PID* pidData)
{
	pidData->error = pidData->set - pidData->feedback;//求当前误差
	
		
	if(fabs(pidData->error) < pidData->fuzzy_interval)//如果误差绝对值小于模糊区间长度
		pidData->error = 0;//则将误差视为0
	else if(pidData->error > 0)//否则将误差向0调整模糊区间长度
		pidData->error -= pidData->fuzzy_interval;
	else
		pidData->error += pidData->fuzzy_interval;
	
	
	pidData->derror = pidData->error - pidData->last_error;//计算误差微分
	pidData->last_error = pidData->error;//顺延赋值

	
	pidData->P = pidData->kP * pidData->error;//计算比例输出
	
	pidData->I += constrain_int32(pidData->kI * pidData->error, -pidData->Imax/10, +pidData->Imax/10);
	//计算积分输出，积分增加最大值为最大积分值十分之一
	pidData->I = constrain_int32(pidData->I, -pidData->Imax, +pidData->Imax);	//计算积分输出
	
	if(pidData->kI==0)//如果ki为0，清零积分（防止调参时将ki清零之后，积分消不掉）
		pidData->I=0;
	pidData->D = pidData->kD * pidData->derror;//计算微分输出
	
}

void ResetI(struct PID* pidData)//将积分输出清零
{
	pidData->I = 0;
}

void ResetPID(struct PID* pidData)//重置PID结构体中输出相关项
{
	
	pidData->error=0;
	pidData->derror=0;
	pidData->last_error=0;
	pidData->P=0;
	pidData->I = 0;
	pidData->D=0;
	
	
}

void GetP(struct PID* pidData)//输出P
{
	pidData->out = pidData->P;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPI(struct PID* pidData)//输出P和I
{
	pidData->out = pidData->P + pidData->I;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPD(struct PID* pidData)//输出P和D
{
	pidData->out = pidData->P + pidData->D;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPID(struct PID* pidData)//输出P I D 三者
{
	pidData->out = pidData->P + pidData->I + pidData->D;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

