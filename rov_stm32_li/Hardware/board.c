/************************************�ײ�������ش���********************************/
/*
���ܣ�����оƬ�ĵײ�����
*/

#include "board.h"

//#include "servo.h"

/*
�ײ����������ʼ������
�ϵ�����
*/
void Board_Init(void)
{
//	delay_init(72);//��ʱ���ܳ�ʼ��������оƬʱ��Ƶ��Ϊ72MHz
	Motor_Init();//���PWM�����ʼ��		
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//��ʼ��NVIC���ȼ�������
//	USART1_Config(115200);//����1��ʼ����������115200
//	JY901_Init();//JY901�����ǳ�ʼ��	
//	Camera_Init();//����ͷ�����ʼ��
	MS5837_Init();//��ȴ�������ʼ��
//	Servo_Init();//������������ʼ��
	
//	Timebase_Init();//ʱ����ʱ����ʼ��
}

