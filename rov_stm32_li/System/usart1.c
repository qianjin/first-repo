/************************************串口通信********************************/
/*
功能：串口1初始化代码，用于和上位机通信。
本代码为硬件层，软件层代码见command.c文件
*/
#include "usart.h"
#include "usart1.h"

///*
//串口1初始化函数
//参数：波特率
//*/
//void USART1_Config(uint32_t baudrate)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

//	RCC_APB2PeriphClockCmd(USART1_CLK | RCC_APB2Periph_GPIOA, ENABLE);

//	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);    
//	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	/* USART1 mode config */
//	USART_InitStructure.USART_BaudRate =baudrate;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART1, &USART_InitStructure);
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

//	USART_Cmd(USART1, ENABLE);
//	USART_ClearFlag(USART1,USART_FLAG_TC);
//	NVIC_USART1_Configuration();
//}

///*
//串口1NVIC初始化程序
//*/
//void NVIC_USART1_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure; 
//	/* Configure the NVIC Preemption Priority Bits */  

//	
//	/* Enable the USARTy Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}

///*
//串口1重定向功能，用于用printf函数输出串口
//*/
int fputc(int ch, FILE *f)
{
//	/* 将Printf内容发往串口 */
//	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
//	
	HAL_UART_Transmit(&huart1,(const uint8_t*)&ch,1,HAL_MAX_DELAY);
	return ch;
}
/*
串口1输出字符函数
参数：输出字符
*/
void USART1_PutChar(char ch)
{
//	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	 
	HAL_UART_Transmit_DMA(&huart1,(const uint8_t*)&ch,1);
}

/***********
串口1输出字节
参数：输出字节
************/
void USART1_SendByte(uint8_t Byte)
{
//	USART_SendData(USART1,Byte);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	HAL_UART_Transmit_DMA(&huart1,&Byte,1);
	
}

