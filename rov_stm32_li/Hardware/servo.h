#ifndef _SERVO_H
#define _SERVO_H

#include "main.h"


#define		Frequency_Servo		200
/*单位us*/
#define		Time_Min_Servo		495
#define		Time_Max_Servo		2500



uint16_t extern servo1;
uint16_t extern servo2;
uint16_t extern servo3;
uint16_t extern servo4;

extern uint8_t servo_sample_falg;

#define             SERVO1_TIMx                                TIM3
#define             SERVO2_TIMx                                TIM3
#define             SERVO3_TIMx                                TIM3
#define             SERVO4_TIMx                                TIM3

//#define             SERVO1_TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
//#define             SERVO1_TIM_CLK                             RCC_APB1Periph_TIM3
//#define             SERVO1_TIM_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
//#define             SERVO1_TIM_GPIO_CLK                        RCC_APB2Periph_GPIOA

//#define             SERVO2_TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
//#define             SERVO2_TIM_CLK                             RCC_APB1Periph_TIM3
//#define             SERVO2_TIM_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
//#define             SERVO2_TIM_GPIO_CLK                        RCC_APB2Periph_GPIOB

//#define             SERVO3_TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
//#define             SERVO3_TIM_CLK                             RCC_APB1Periph_TIM3
//#define             SERVO3_TIM_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
//#define             SERVO3_TIM_GPIO_CLK                        RCC_APB2Periph_GPIOB

//#define             SERVO4_TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
//#define             SERVO4_TIM_CLK                             RCC_APB1Periph_TIM3
//#define             SERVO4_TIM_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
//#define             SERVO4_TIM_GPIO_CLK                        RCC_APB2Periph_GPIOA

//#define             SERVO1_PORT                      				  GPIOA
//#define             SERVO1_PIN                         				GPIO_Pin_7

//#define             SERVO2_PORT                      				  GPIOB
//#define             SERVO2_PIN                         				GPIO_Pin_0

//#define             SERVO3_PORT                      				  GPIOB
//#define             SERVO3_PIN                         				GPIO_Pin_1

//#define             SERVO4_PORT                      				  GPIOA
//#define             SERVO4_PIN                         				GPIO_Pin_6

//#define             SERVO1_TIM_OCxInit                         TIM_OC2Init        
//#define             SERVO1_TIM_OCxPreloadConfig                TIM_OC2PreloadConfig  
#define             SERVO1_CCRx                                CCR2

//#define             SERVO2_TIM_OCxPreloadConfig                TIM_OC3PreloadConfig  
//#define             SERVO2_TIM_OCxInit                         TIM_OC3Init  //通道选择，3~4
#define             SERVO2_CCRx                                CCR3

//#define             SERVO3_TIM_OCxInit                         TIM_OC4Init        
//#define             SERVO3_TIM_OCxPreloadConfig                TIM_OC4PreloadConfig  
#define             SERVO3_CCRx                                CCR4

//#define             SERVO4_TIM_OCxInit                         TIM_OC1Init        
//#define             SERVO4_TIM_OCxPreloadConfig                TIM_OC1PreloadConfig  
#define             SERVO4_CCRx                                CCR1


#define							SERVO1_CCR																	SERVO1_TIMx->SERVO1_CCRx
#define							SERVO2_CCR																	SERVO2_TIMx->SERVO2_CCRx
#define							SERVO3_CCR																	SERVO3_TIMx->SERVO3_CCRx
#define							SERVO4_CCR																	SERVO4_TIMx->SERVO4_CCRx

void Servo_Init(void);
void Servo_SetPercent(uint8_t num,uint16_t percent);
void Servo_fun(void);
void Servo_SampleStart(void);
void Servo_SampleStop(void);

#endif
