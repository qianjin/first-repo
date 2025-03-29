#ifndef _CAMERA_H
#define _CAMERA_H

#include "stm32f10x.h"


#define		Frequency_CAM		50//PWM���Ƶ��
/*��λus*/
#define		Time_Min_CAM		780//��СPWM����ߵ�ƽʱ�� ��λ΢��us
#define		Time_Max_CAM		2000//���PWM����ߵ�ƽʱ�� ��λ΢��us


extern uint8_t camera_angle;



#define             CAMERA_TIMx                                TIM3

#define             CAMERA_TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             CAMERA_TIM_CLK                             RCC_APB1Periph_TIM3
#define             CAMERA_TIM_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             CAMERA_TIM_GPIO_CLK                        RCC_APB2Periph_GPIOA

#define             CAMERA_PORT      	          				GPIOA
#define             CAMERA_PIN                     				GPIO_Pin_6
#define             CAMERA_TIM_OCxInit                         TIM_OC1Init            //ͨ��ѡ��1~4
#define             CAMERA_TIM_OCxPreloadConfig                TIM_OC1PreloadConfig  

#define             CAMERA_CCRx                                CCR1

#define							CAMERA_CCR																	CAMERA_TIMx->CAMERA_CCRx
#define							CAMERA_PSC																	CAMERA_TIMx->PSC
#define							CAMERA_ARR															  	CAMERA_TIMx->ARR

void Camera_Init(void);
void Camera_SetPercent(uint8_t angle);
	
#endif
