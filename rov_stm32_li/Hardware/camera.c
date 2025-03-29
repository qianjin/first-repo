/************************************����ͷ�����������********************************/
/*
����180�ȵ�sg90���
*/
#include "camera.h"
#include "stm32f10x.h"                  // Device header

uint8_t camera_angle=128;//����Ƕȣ�0~180��ӳ�䵽�ñ�����0~225

/*
����ͷ���GPIO��ʼ��
*/
static void Camera_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  CAMERA_TIM_GPIO_APBxClock_FUN  ( CAMERA_TIM_GPIO_CLK, ENABLE );

  GPIO_InitStructure.GPIO_Pin =  CAMERA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init( CAMERA_PORT, &GPIO_InitStructure );
}
/*
����ͷ���PWMͨ�ö�ʱ���趨����
*/
static void Camera_TIMMode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	CAMERA_TIM_APBxClock_FUN ( CAMERA_TIM_CLK, ENABLE );

  /* ������ʱ������ */		 
  TIM_TimeBaseStructure.TIM_Period = 999;     							 
  TIM_TimeBaseStructure.TIM_Prescaler = 72000/Frequency_CAM-1;	    							//����Ԥ���������Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
  TIM_TimeBaseInit(CAMERA_TIMx, &TIM_TimeBaseStructure);

  /* PWMģʽ���� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = 0;										  			//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ

  CAMERA_TIM_OCxInit ( CAMERA_TIMx, &TIM_OCInitStructure );	 									//ʹ��ͨ��3
  CAMERA_TIM_OCxPreloadConfig ( CAMERA_TIMx, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	

  TIM_ARRPreloadConfig(CAMERA_TIMx, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR
	
  /* TIM3 enable counter */
  TIM_Cmd(CAMERA_TIMx, ENABLE);                   										//ʹ�ܶ�ʱ��3	
}

/*
����ͷ�����ʼ������
*/
void Camera_Init(void)
{
	Camera_GPIO_Init();//GPIO��ʼ��
	Camera_TIMMode_Config();//PWMͨ�ö�ʱ����ʼ��
	Camera_SetPercent(camera_angle);//�趨����ͷ����Ƕ�Ϊ��ʼ�Ƕ�
}

/*
���ܣ��������ö���г��ڰٷֱ�
������angle 0~255��Ӧ0~180��
*/
void Camera_SetPercent(uint8_t angle)
{
	float percent=((float)(angle))/2.560F;//���ٷֱ�0~100ӳ�䵽����angle��0~225
	uint16_t time=(Time_Max_CAM-Time_Min_CAM)*(percent/100.0)+Time_Min_CAM;//ͨ����������ߵ�ƽʱ��
	CAMERA_CCR=(time)/(1000/(Frequency_CAM));//��������CCRֵ��ֵ
}
