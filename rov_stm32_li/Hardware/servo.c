//����дע���ˣ����������ƴ�������ǰд�ģ�����ˮƽ
#include "servo.h"

#define servo1_max	90
#define servo1_min	60

#define servo3_max	80
#define servo3_min	45

#define servo4_max	22
#define servo4_min	5

uint16_t servo1=90;//��� ��90���ϣ�   С60���£�
uint16_t servo2=50;//С�쳤������
uint16_t servo3=80;//35�� 80����
uint16_t servo4=servo4_max;//С��  5�� 17��
uint8_t servo_sample_falg=0;

//static void Servo_GPIO_Init(void)
//{
//	 GPIO_InitTypeDef GPIO_InitStructure;
//  SERVO1_TIM_GPIO_APBxClock_FUN  ( SERVO1_TIM_GPIO_CLK, ENABLE );
//  SERVO2_TIM_GPIO_APBxClock_FUN  ( SERVO2_TIM_GPIO_CLK, ENABLE );
//	SERVO3_TIM_GPIO_APBxClock_FUN  ( SERVO3_TIM_GPIO_CLK, ENABLE );
//  SERVO4_TIM_GPIO_APBxClock_FUN  ( SERVO4_TIM_GPIO_CLK, ENABLE );
//	
//  /* ���ú������õ���PB0���� */

//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//  
//	GPIO_InitStructure.GPIO_Pin =  SERVO1_PIN;
//  GPIO_Init( SERVO1_PORT, &GPIO_InitStructure );
//	
//	GPIO_InitStructure.GPIO_Pin =  SERVO2_PIN;
//  GPIO_Init( SERVO2_PORT, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin =  SERVO3_PIN;
//  GPIO_Init( SERVO3_PORT, &GPIO_InitStructure );
//	
//	GPIO_InitStructure.GPIO_Pin =  SERVO4_PIN;
//  GPIO_Init( SERVO4_PORT, &GPIO_InitStructure );
//	
//	
//}

//static void Servo_TIMMode_Config(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
//	
//	
//	/* ����TIM3CLK ʱ��Ϊ72MHZ */
////  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 					//ʹ��TIM3ʱ��
//	SERVO1_TIM_APBxClock_FUN ( SERVO1_TIM_CLK, ENABLE );
//	SERVO2_TIM_APBxClock_FUN ( SERVO2_TIM_CLK, ENABLE );
//	SERVO3_TIM_APBxClock_FUN ( SERVO3_TIM_CLK, ENABLE );
//	SERVO4_TIM_APBxClock_FUN ( SERVO4_TIM_CLK, ENABLE );
//	
//  /* ������ʱ������ */		 
//  TIM_TimeBaseStructure.TIM_Period = 999;     							 
//  TIM_TimeBaseStructure.TIM_Prescaler = 72000/Frequency_Servo-1;	    							//����Ԥ��Ƶ��
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
//	
//  TIM_TimeBaseInit(SERVO1_TIMx, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(SERVO2_TIMx, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(SERVO3_TIMx, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(SERVO4_TIMx, &TIM_TimeBaseStructure);

//  /* PWMģʽ���� */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
//  TIM_OCInitStructure.TIM_Pulse = 0;										  			//���ó�ʼPWM������Ϊ0	
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ

//  SERVO1_TIM_OCxInit ( SERVO1_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��3
//  SERVO2_TIM_OCxInit ( SERVO2_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��3	
//	SERVO3_TIM_OCxInit ( SERVO3_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��3
//  SERVO4_TIM_OCxInit ( SERVO4_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��3	

//  SERVO1_TIM_OCxPreloadConfig ( SERVO1_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	
//  SERVO2_TIM_OCxPreloadConfig ( SERVO2_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	
//	SERVO3_TIM_OCxPreloadConfig ( SERVO3_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	
//  SERVO4_TIM_OCxPreloadConfig ( SERVO4_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	
//	
//	TIM_ARRPreloadConfig(SERVO1_TIMx, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR
//	TIM_ARRPreloadConfig(SERVO2_TIMx, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR
//	TIM_ARRPreloadConfig(SERVO3_TIMx, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR
//	TIM_ARRPreloadConfig(SERVO4_TIMx, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR

//  /* TIM3 enable counter */
//	TIM_Cmd(SERVO1_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��3	
//	TIM_Cmd(SERVO2_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��3	
//	TIM_Cmd(SERVO3_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��3	
//	TIM_Cmd(SERVO4_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��3	
//}

void Servo_Init(void)
{
//	Servo_GPIO_Init();
//	Servo_TIMMode_Config();
//	Servo_SetPercent(1,50);
//	Servo_SetPercent(2,50);
//	Servo_SetPercent(3,50);
//	Servo_SetPercent(4,50);
	Servo_SampleStop();

}

/*
���ܣ��������ö���г��ڰٷֱ�
������percent 0~100С��
*/
void Servo_SetPercent(uint8_t num,uint16_t percent)
{

	uint16_t time=(Time_Max_Servo-Time_Min_Servo)*((float)percent/100.0F)+Time_Min_Servo;
	
	if(servo3>servo3_max)
		servo3=servo3_max;
	if(servo3<servo3_min)
		servo3=servo3_min;
	
	if(servo4>servo4_max)
		servo4=servo4_max;
	if(servo4<servo4_min)
		servo4=servo4_min;
	
		
	if(servo1>servo1_max)
		servo1=servo1_max;
	if(servo1<servo1_min)
		servo1=servo1_min;
	
	switch(num)
	{	
		case 1:SERVO1_CCR=(time)/(1000/(Frequency_Servo));break;
		case 2:SERVO2_CCR=(time)/(1000/(Frequency_Servo));break;
		case 3:SERVO3_CCR=(time)/(1000/(Frequency_Servo));break;
		case 4:SERVO4_CCR=(time)/(1000/(Frequency_Servo));break;
	}
	

}

uint16_t cnt;

void Servo_fun(void)
{
	
	Servo_SetPercent(1,servo1);

	Servo_SetPercent(3,servo3);
	Servo_SetPercent(4,servo4);
	

		cnt++;
	if(cnt==75)
	{
		Servo_SampleStop();
		cnt=75;
	}
	
}

void Servo_SampleStart(void)
{

			servo2=60;
		cnt=0;
			Servo_SetPercent(2,servo2);
		
}

void Servo_SampleStop(void)
{
	servo2=50;
	SERVO2_CCR=0;
}

