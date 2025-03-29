#ifndef _USART2_H_
#define _USART2_H_


#include "main.h"
#include <stdio.h>

///***********************´®¿ÚÓ²¼þÅäÖÃ******************************************/
//#define 			USART2x									USART2
//#define				USART2x_IRQn							USART2_IRQn	
//#define             USART2x_APBxClock_FUN                   RCC_APB1PeriphClockCmd
//#define             USART2x_CLK                             RCC_APB1Periph_USART2
//#define             USART2x_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
//#define             USART2x_GPIO_CLK                        (RCC_APB2Periph_GPIOA )     
//#define             USART2x_TX_PORT                         GPIOA   
//#define             USART2x_TX_PIN                          GPIO_Pin_2
//#define             USART2x_RX_PORT                         GPIOA 
//#define             USART2x_RX_PIN                          GPIO_Pin_3
//#define				USART2x_IRQHandler						USART2_IRQHandler
//	
//void USART2x_Config(void);
//void NVIC_USART2x_Configuration(void);
int USART2x_SendByte(uint8_t ch);
#endif

