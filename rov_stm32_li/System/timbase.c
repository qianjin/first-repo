/************************************ʱ����ʱ��********************************/
/*
���ܣ�Ϊʱ��Ƭ��ת�ṩʱ��
*/
#include "timbase.h" 
#include "stm32f10x.h"                  // Device header
#include "Scheduler.h"



/*******************************��Ҫע��*****************************/
/*
���ڲ���STM32C8T6��Ƭ������ʱ����Դ��Ϊ���ţ��ʺ͵��PWM�������ͬһͨ�ö�ʱ����TIM4����
��ʱ����ʱ��ؼĴ�����ʼ������λ��motor.c�ļ��У��˴������жϽ��г�ʼ������ʱ��Ƶ��Ϊ200HZ��
*/
/*******************************��Ҫע��*****************************/


/*
ʱ����ʱ����ʼ������
*/
void Timebase_Init(void)
{
	TIMx_NVIC_Configuration ();
	TIMx_Configuration();
	macTIM_APBxClock_FUN (macTIM_CLK, ENABLE);
}

/*
ʱ����ʱ��NVIC��ʼ������
*/
void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = macTIM_IRQ;
	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
ʱ����ʱ�����ú���
*/
void TIMx_Configuration(void)
{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ����TIMx_CLK,x[6,7],���ڲ�ʱ��CK_INT=72M
    macTIM_APBxClock_FUN (macTIM_CLK, ENABLE);
//	TIM_InternalClockConfig(TIM4);
	
//		// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
//    TIM_TimeBaseStructure.TIM_Period=100;
//	
//    // �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
//	  // ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
//    TIM_TimeBaseStructure.TIM_Prescaler= 719;

//	
//	  // ��ʼ����ʱ��TIMx, x[6,7]
//    TIM_TimeBaseInit(macTIMbasex, &TIM_TimeBaseStructure);
	
		
		// ����������жϱ�־λ
    TIM_ClearFlag(macTIMbasex, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(macTIMbasex,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(macTIMbasex, ENABLE);																		
    
		// ��ʱ�ر�TIMx,x[6,7]��ʱ�ӣ��ȴ�ʹ��
    macTIM_APBxClock_FUN (macTIM_CLK, DISABLE);   
}
/*********************************************END OF FILE**********************/

