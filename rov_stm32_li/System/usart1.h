#ifndef _USART1_H
#define _USART1_H


#include "main.h"
#include <stdio.h>

///***********************����Ӳ������******************************************/
//#define             USART1_APBxClock_FUN                   RCC_APB2PeriphClockCmd
//#define             USART1_CLK                             RCC_APB2Periph_USART1
//#define             USART1_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
//#define             USART1_GPIO_CLK                        (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)     
//#define             USART1_TX_PORT                         GPIOA   
//#define             USART1_TX_PIN                          GPIO_Pin_9
//#define             USART1_RX_PORT                         GPIOA  
//#define             USART1_RX_PIN                          GPIO_Pin_10



/*************************��������******************************************/

//void USART1_Config(uint32_t baudrate);
//void NVIC_USART1_Configuration(void);
int fputc(int ch, FILE *f);
void USART1_PutChar(char ch);
void USART1_SendByte(uint8_t Byte);
#endif
