/**
  * @auther whlphlg
  * @brief task.c��������Ҫ���е������������ļ���������ģ����ɶȽϴ�
  * @changedate 2020.09.13
  */
	
//�û�include
#include "main.h"
#include "gpio.h"
//�����������д�ģ�����include������
#include "task.h"
#include "usart.h"
#include "sys.h"
#include "Queue.h"
uint8_t txdata[20]="hello world";
uint8_t rxdata[20]={0};
uint8_t count=66;

void task1()
{

	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);

}
void task2()
{
////	System_TaskOut(TASK1,4000);
	SeqQueue_AppendMultiple(&Usart1QueueIn,txdata,20);
	SeqQueue_RetrieveMultiple(&Usart1QueueIn,rxdata,20);
	HAL_UART_Transmit(&huart1,txdata,30,100);
}
void task3()
{
	
}



