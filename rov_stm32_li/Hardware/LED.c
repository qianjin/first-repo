#include "LED.h"                  // Device header



void LED1_ON(void)
{
	//GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
}

void LED1_OFF(void)
{
	//GPIO_SetBits(GPIOA,GPIO_Pin_4);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
}


void LED2_ON(void)
{
	//GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_RESET);
}

void LED2_OFF(void)
{
	//GPIO_SetBits(GPIOA,GPIO_Pin_5);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET);
}

void LED3_ON(void)
{
	//GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
}

void LED3_OFF(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
}

