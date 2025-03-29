#ifndef TIMEBASE_H
#define TIMEBASE_H


#include "stm32f10x.h"




#define             macTIMbasex                 TIM4//和motor.c中电调PWM输出共用同一定时器
#define             macTIM_APBxClock_FUN    RCC_APB1PeriphClockCmd
#define             macTIM_CLK              RCC_APB1Periph_TIM4
#define             macTIM_IRQ              TIM4_IRQn
#define             macTIM_INT_FUN          TIM4_IRQHandler



/**************************函数声明********************************/
void               TIMx_NVIC_Configuration                   (void);
void               TIMx_Configuration                        (void);
void 						   Timebase_Init									   					(void);

#endif

