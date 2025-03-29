/************************************�����������********************************/
/*
���ܣ����4·PWM�źŵ��������������4���ƽ������
�����Ϣ�����Ƽ�˫�����������ز�����motor.h�к궨��
�������ڲ��ļ��㹫ʽ�����Ը���motor.h�������õ�Ƶ�ʡ������С����λ����ʱ�䣬�Զ����ٶ�ֵӳ�䵽CCR��PSC�ȼĴ���
�Ӷ�ͨ���޸�motor.h�к��ֵ��������Ӧ���ֲ�ͬ�����ĵ��
*/


/****************ROV����Ų�ʾ��ͼ***************/
/*
���1(��)���� ���2����      ���(3):��  ���(4):��
���(5)���� ���(6)����  

 --------��----
|   2    1 	  |	
|		 	  |
|   6    5    |
|             |
|	4	 3	  | 
|             |
 --------------
*/
/**********************************/


#include "motor.h"
#include "Delay.h"
#include "tim.h"
MOTOR Motor={0,0,0,0};//��ʼ�����ת�ٽṹ��

void Motor_Init(void)    //���������ʼ��
{
	//Motor_TIM_Motor_GPIO_Config();
	//Motor_TIM_Motor_Mode_Config();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	delay_ms(1000);
	Motor_SetOne();
	delay_ms(1500);	
	Motor_SetTwo();
	delay_ms(1000);
	Motor_SetLow();
}

//�����ʱ��GPIO��ʼ��
//static void Motor_TIM_Motor_GPIO_Config(void) 
//{	
//	GPIO_InitTypeDef GPIOB_InitStructure;
//	GPIO_InitTypeDef GPIOA_InitStructure;
//	
//	//������ӳ�䣬C8T6ֻ����ӳ��һ�Σ��˴�ѡ��TIM4����ӳ��
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
//	
//	RCC_APB2PeriphClockCmd(Motor_TIM_GPIOB_CLK, ENABLE );
//	RCC_APB2PeriphClockCmd(Motor_TIM_GPIOA_CLK, ENABLE );	
//	
//	
////	GPIO_InitStructure.GPIO_Pin =  Motor_TIM_Motor1_PIN ;
//	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    
//	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIOA_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP;
//	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor1_PIN;
//	GPIO_Init(Motor_TIM_Motor1_PORT, &GPIOB_InitStructure );
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor2_PIN;
//	GPIO_Init(Motor_TIM_Motor2_PORT, &GPIOB_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor3_PIN;
//	GPIO_Init(Motor_TIM_Motor3_PORT, &GPIOB_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor4_PIN;
//	GPIO_Init(Motor_TIM_Motor4_PORT, &GPIOB_InitStructure);
//	
//	
//	
//	GPIOA_InitStructure.GPIO_Pin =  Motor_TIM_Motor5_PIN;
//	GPIO_Init(Motor_TIM_Motor5_PORT, &GPIOA_InitStructure );
//	
//	GPIOA_InitStructure.GPIO_Pin =  Motor_TIM_Motor6_PIN;
//	GPIO_Init(Motor_TIM_Motor6_PORT, &GPIOA_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor7_PIN;
//	GPIO_Init(Motor_TIM_Motor7_PORT, &GPIOB_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor8_PIN;
//	GPIO_Init(Motor_TIM_Motor8_PORT, &GPIOB_InitStructure);
//	
////	//��ӳ�䣬��ͨ��3��4ӳ�䵽 PB10 PB11
////	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
//}

/*******************************��Ҫע��*****************************/
/*
���ڲ���STM32C8T6��Ƭ������ʱ����Դ��Ϊ���ţ��ʵ��PWM�������ͨ�ö�ʱ����ʱ����ʱ������ͬһͨ�ö�ʱ����TIM4����
��ʱ���ж���ؼĴ�����ʼ������λ��timbase.c�ļ��У��˴����Զ�ʱ��ؼĴ������г�ʼ��
�����¶�ʱ����ʼ��������κ��޸��п���Ӱ�쵽ʱ����������������ע�⡣
*/
/*******************************��Ҫע��*****************************/

//static void Motor_TIM_Motor_Mode_Config(void)//�����ʱ��ģʽ��ʼ��
//{
//	TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM4_OCInitStructure;																				
//	
//	RCC_APB1PeriphClockCmd( Motor_TIM4_CLK, ENABLE );
//	
//	//��ӳ��,���Ӵ˺�����ʹTIM4�޷�����ʹ��
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4 , ENABLE);
//	

//  /* TIM4������ʱ������ */		 
//	TIM4_TimeBaseStructure.TIM_Period = 1000 - 1;       						 //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
//	TIM4_TimeBaseStructure.TIM_Prescaler = 72000/Frequency-1;	    			//����Ԥ��Ƶ��ͨ������ó���
//	TIM4_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
//	TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
//	TIM_TimeBaseInit(Motor_TIM4, &TIM4_TimeBaseStructure);

//  /* PWMģʽ���� */
//	TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
//	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
//	TIM4_OCInitStructure.TIM_Pulse = 0;//	15						   //���ó�ʼPWM������Ϊ0	���˴�����Ҫ����ʼ������������������룩
//	TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ

//	Motor_TIM_Motor1OCInit( Motor_TIM4, &TIM4_OCInitStructure );	 		//ʹ�ܸ���ͨ�������ͨ��					
//	Motor_TIM_Motor2OCInit( Motor_TIM4, &TIM4_OCInitStructure );	
//	Motor_TIM_Motor3OCInit( Motor_TIM4, &TIM4_OCInitStructure );	 	
//	Motor_TIM_Motor4OCInit( Motor_TIM4, &TIM4_OCInitStructure );	 		
//	
//	Motor_TIM_Motor1PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );	//ʹ�ܸ���ͨ����CCRԤװ�ع���
//	Motor_TIM_Motor2PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor3PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor4PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );


//	TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM3_OCInitStructure;																				
//	
//	RCC_APB1PeriphClockCmd( Motor_TIM3_CLK, ENABLE );

//  /* TIM3������ʱ������ */		 
//	TIM3_TimeBaseStructure.TIM_Period = 1000 - 1;       							  //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
//	TIM3_TimeBaseStructure.TIM_Prescaler = 72000/Frequency-1;	    		//����Ԥ��Ƶ��ͨ������ó���	//200Hz
//	TIM3_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
//	TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
//	TIM_TimeBaseInit(Motor_TIM3, &TIM3_TimeBaseStructure);

//  /* PWMģʽ���� */
//	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
//	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
//	TIM3_OCInitStructure.TIM_Pulse = 0;	//15									  			//���ó�ʼPWM������Ϊ0	���˴�����Ҫ����ʼ������������������룩
//	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ

//	Motor_TIM_Motor1OCInit( Motor_TIM3, &TIM3_OCInitStructure );	 		//ʹ�ܸ���ͨ�������ͨ��					
//	Motor_TIM_Motor2OCInit( Motor_TIM3, &TIM3_OCInitStructure );	
//	Motor_TIM_Motor3OCInit( Motor_TIM3, &TIM3_OCInitStructure );	 	
//	Motor_TIM_Motor4OCInit( Motor_TIM3, &TIM3_OCInitStructure );	 		
//	
//	Motor_TIM_Motor1PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );	//ʹ�ܸ���ͨ����CCRԤװ�ع���
//	Motor_TIM_Motor2PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor3PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor4PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );
//	
//	

//	TIM_ARRPreloadConfig(Motor_TIM4, ENABLE);			 				//ʹ��Motor_TIM4���ؼĴ���ARR
//	TIM_ARRPreloadConfig(Motor_TIM3, ENABLE);			 				//ʹ��Motor_TIM3���ؼĴ���ARR

//	TIM_Cmd(Motor_TIM4, ENABLE);                   						//ʹ�ܶ�ʱ��	
//	TIM_Cmd(Motor_TIM3, ENABLE);                   						//ʹ�ܶ�ʱ��		
//}

/**********************************************************
��������void Motor_SetSpeed(uint8_t Motornum,int16_t Speed)
���ܣ��趨ָ�������ת��
������	������motornum��Motor1~4
			�ٶ�speed -999~999��Ӧ����ת~������
���أ���
�������ڲ��ļ��㹫ʽ�����Ը���motor.h�������õ�Ƶ�ʡ������С����λ����ʱ�䣬�Զ����ٶ�ֵӳ�䵽����Ƚ�CCR�Ĵ���
�Ӷ�ͨ���޸�motor.h�к��ֵ��������Ӧ���ֲ�ͬ�����ĵ��
**********************************************************/
void Motor_SetSpeed(uint8_t motornum,int16_t speed)
{	
	uint16_t Tim_CCR;
	if(speed>999||speed<-999)//������Χ�򷵻�
		return;
	if(speed>0)
		Tim_CCR=((double)Frequency/1000.0-1.0)*((double)Time_Mid+((double)speed/999.0)*(double)(Time_Max-Time_Mid));
	else
		Tim_CCR=((double)Frequency/1000.0-1.0)*((double)Time_Mid-((double)(-speed)/999.0)*(double)(Time_Mid-Time_Min));
	switch(motornum)
		{
			case Motor1: Motor1_Speed=Tim_CCR;break;
			case Motor2: Motor2_Speed=Tim_CCR;break;
			case Motor3: Motor3_Speed=Tim_CCR;break;
			case Motor4: Motor4_Speed=Tim_CCR;break;
			case Motor5: Motor5_Speed=Tim_CCR;break;
			case Motor6: Motor6_Speed=Tim_CCR;break;
//			case Motor7: Motor7_Speed=Tim_CCR;break;
//			case Motor8: Motor8_Speed=Tim_CCR;break;
		}
}

/**********************************************************
��������void Motor_fun(void)
���ܣ��ж��з���ִ�еĵ����������Motor�ṹ���е��ĸ����ת��ʵ�ֵ�PWM����ź���
��������
���أ���
**********************************************************/
void Motor_fun(void)
{
	Motor_SetSpeed(Motor1,Motor.motor1_speed);
	Motor_SetSpeed(Motor2,Motor.motor2_speed);
	Motor_SetSpeed(Motor3,Motor.motor3_speed);
	Motor_SetSpeed(Motor4,Motor.motor4_speed);
	
	Motor_SetSpeed(Motor5,Motor.motor5_speed);
	Motor_SetSpeed(Motor6,Motor.motor6_speed);
//	Motor_SetSpeed(Motor7,Motor.motor7_speed);
//	Motor_SetSpeed(Motor8,Motor.motor8_speed);
}

//�����ʼ��
void Motor_SetOne(void)
{
//	TIM_SetCompare1(TIM4,300);//��ʱ����������ڵ��� ��ARR+1��*(PSC+1)/CLK	ClKΪ72MHz
//	TIM_SetCompare2(TIM4,300);		
//	TIM_SetCompare3(TIM4,300);		
//	TIM_SetCompare4(TIM4,300);	

//	TIM_SetCompare1(TIM3,300);	
//	TIM_SetCompare2(TIM3,300);		
//	TIM_SetCompare3(TIM3,300);		
//	TIM_SetCompare4(TIM3,300);	
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,300);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,300);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,300);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,300);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,300);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,300);
}

void Motor_SetTwo(void)
{
//	TIM_SetCompare1(TIM4,400);
//	TIM_SetCompare2(TIM4,400);		
//	TIM_SetCompare3(TIM4,400);		
//	TIM_SetCompare4(TIM4,400);
//	                    
//	TIM_SetCompare1(TIM3,400);	
//	TIM_SetCompare2(TIM3,400);		
//	TIM_SetCompare3(TIM3,400);		
//	TIM_SetCompare4(TIM3,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,400);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,400);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,400);
}

void Motor_SetLow(void)
{
//	TIM_SetCompare1(TIM4,0);
//	TIM_SetCompare2(TIM4,0);		
//	TIM_SetCompare3(TIM4,0);		
//	TIM_SetCompare4(TIM4,0);
//	
//	TIM_SetCompare1(TIM3,0);	
//	TIM_SetCompare2(TIM3,0);		
//	TIM_SetCompare3(TIM3,0);		
//	TIM_SetCompare4(TIM3,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,0);
}
