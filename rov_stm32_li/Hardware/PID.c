/************************************PID�Զ����ƴ���********************************/
/*
PID�Զ����ƴ��룬�����������ı��˼�룬�ýṹ���ʾ����PID����
*/


#include "PID.h"
#include "math.h"



//�޷�����������������ֵ���޶���Сֵ���޶����ֵ
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high) 
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//PID��ʼ������������kp ki kd �������ֵ ������ֵ ģ�����䣨Ŀ��ֵ�͵�ǰֵ��ֵ����ֵС��ģ�����䳤��ʱ�������е��ڣ�
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

//PID���㺯��
void PIDUpData(struct PID* pidData)
{
	pidData->error = pidData->set - pidData->feedback;//��ǰ���
	
		
	if(fabs(pidData->error) < pidData->fuzzy_interval)//���������ֵС��ģ�����䳤��
		pidData->error = 0;//�������Ϊ0
	else if(pidData->error > 0)//���������0����ģ�����䳤��
		pidData->error -= pidData->fuzzy_interval;
	else
		pidData->error += pidData->fuzzy_interval;
	
	
	pidData->derror = pidData->error - pidData->last_error;//�������΢��
	pidData->last_error = pidData->error;//˳�Ӹ�ֵ

	
	pidData->P = pidData->kP * pidData->error;//����������
	
	pidData->I += constrain_int32(pidData->kI * pidData->error, -pidData->Imax/10, +pidData->Imax/10);
	//�����������������������ֵΪ������ֵʮ��֮һ
	pidData->I = constrain_int32(pidData->I, -pidData->Imax, +pidData->Imax);	//����������
	
	if(pidData->kI==0)//���kiΪ0��������֣���ֹ����ʱ��ki����֮�󣬻�����������
		pidData->I=0;
	pidData->D = pidData->kD * pidData->derror;//����΢�����
	
}

void ResetI(struct PID* pidData)//�������������
{
	pidData->I = 0;
}

void ResetPID(struct PID* pidData)//����PID�ṹ������������
{
	
	pidData->error=0;
	pidData->derror=0;
	pidData->last_error=0;
	pidData->P=0;
	pidData->I = 0;
	pidData->D=0;
	
	
}

void GetP(struct PID* pidData)//���P
{
	pidData->out = pidData->P;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPI(struct PID* pidData)//���P��I
{
	pidData->out = pidData->P + pidData->I;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPD(struct PID* pidData)//���P��D
{
	pidData->out = pidData->P + pidData->D;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPID(struct PID* pidData)//���P I D ����
{
	pidData->out = pidData->P + pidData->I + pidData->D;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

