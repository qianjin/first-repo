/************************************����2����********************************/
/*
���ܣ�����2�����ļ���������ȡJY901���ڷ��ص�ԭʼ����
JY901����������Ϊ9600�����ùٷ���λ��miniMU�������ò����ʣ�����������JY901�����ʱ�����Ϊ115200
��ʼ�����빦����usart.c����ͬ
*/
#include "USART2.h"
#include "usart.h"
//void USART2x_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

//	USART2x_APBxClock_FUN (USART2x_CLK , ENABLE);
//	
//	USART2x_GPIO_APBxClock_FUN(USART2x_GPIO_CLK ,ENABLE);

//	GPIO_InitStructure.GPIO_Pin = USART2x_TX_PIN ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(USART2x_TX_PORT   , &GPIO_InitStructure);    
//	GPIO_InitStructure.GPIO_Pin = USART2x_RX_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(USART2x_TX_PORT   , &GPIO_InitStructure);
//	
//	/* USART1 mode config */
//	USART_InitStructure.USART_BaudRate =9600;//JY901����������Ϊ9600�����ùٷ���λ��miniMU��������115200�����ʣ�����������JY901�����ʱ�����Ϊ115200
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART2x, &USART_InitStructure);
//	USART_ITConfig(USART2x, USART_IT_RXNE, ENABLE);

//	USART_Cmd(USART2x, ENABLE);
//	USART_ClearFlag(USART2x,USART_FLAG_TC);
//	NVIC_USART2x_Configuration();
//}

//void NVIC_USART2x_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure; 
//	/* Configure the NVIC Preemption Priority Bits */  

//	
//	/* Enable the USARTy Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = USART2x_IRQn;	 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		

	}
	else if(huart==&huart2)	
	{
	
	
	
	
	
	
	}









}

int USART2x_SendByte(uint8_t ch)
{
	/* ��Printf���ݷ������� */
//	USART_SendData(USART2x, ch);
//	while (!(USART2x->SR & USART_FLAG_TXE));
//	
	HAL_UART_Transmit_DMA(&huart1,&ch,1);
	return (ch);
	
}

