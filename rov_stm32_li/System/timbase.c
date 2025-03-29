/************************************时基定时器********************************/
/*
功能：为时间片轮转提供时基
*/
#include "timbase.h" 
#include "stm32f10x.h"                  // Device header
#include "Scheduler.h"



/*******************************重要注释*****************************/
/*
由于采用STM32C8T6单片机，定时器资源较为紧张，故和电调PWM输出共用同一通用定时器（TIM4），
定时器定时相关寄存器初始化代码位于motor.c文件中，此处仅对中断进行初始化（定时器频率为200HZ）
*/
/*******************************重要注释*****************************/


/*
时基定时器初始化函数
*/
void Timebase_Init(void)
{
	TIMx_NVIC_Configuration ();
	TIMx_Configuration();
	macTIM_APBxClock_FUN (macTIM_CLK, ENABLE);
}

/*
时基定时器NVIC初始化函数
*/
void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = macTIM_IRQ;
	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
时基定时器配置函数
*/
void TIMx_Configuration(void)
{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启TIMx_CLK,x[6,7],即内部时钟CK_INT=72M
    macTIM_APBxClock_FUN (macTIM_CLK, ENABLE);
//	TIM_InternalClockConfig(TIM4);
	
//		// 自动重装载寄存器周的值(计数值)
//    TIM_TimeBaseStructure.TIM_Period=100;
//	
//    // 累计 TIM_Period个频率后产生一个更新或者中断
//	  // 时钟预分频数为71，则驱动计数器的时钟CK_CNT = CK_INT / (71+1)=1M
//    TIM_TimeBaseStructure.TIM_Prescaler= 719;

//	
//	  // 初始化定时器TIMx, x[6,7]
//    TIM_TimeBaseInit(macTIMbasex, &TIM_TimeBaseStructure);
	
		
		// 清除计数器中断标志位
    TIM_ClearFlag(macTIMbasex, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(macTIMbasex,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(macTIMbasex, ENABLE);																		
    
		// 暂时关闭TIMx,x[6,7]的时钟，等待使用
    macTIM_APBxClock_FUN (macTIM_CLK, DISABLE);   
}
/*********************************************END OF FILE**********************/

