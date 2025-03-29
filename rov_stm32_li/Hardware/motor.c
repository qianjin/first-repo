/************************************电机驱动代码********************************/
/*
功能：输出4路PWM信号到电调，用于驱动4个推进器电机
电调信息：格邦科技双向电调，电调相关参数见motor.h中宏定义
本函数内部的计算公式，可以根据motor.h中所设置的频率、最大、最小、中位油门时间，自动将速度值映射到CCR、PSC等寄存器
从而通过修改motor.h中宏的值，即可适应各种不同参数的电调
*/


/****************ROV电机排布示意图***************/
/*
电机1(正)：正 电机2：正      电机(3):反  电机(4):反
电机(5)：正 电机(6)：反  

 --------—----
|   2    1 	  |	
|		 	  |
|   6    5    |
|             |
|	4	 3	  | 
|             |
 --------------
*/
/**********************************/


#include "motor.h"
#include "Delay.h"
#include "tim.h"
MOTOR Motor={0,0,0,0};//初始化电机转速结构体

void Motor_Init(void)    //辅助电机初始化
{
	//Motor_TIM_Motor_GPIO_Config();
	//Motor_TIM_Motor_Mode_Config();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	delay_ms(1000);
	Motor_SetOne();
	delay_ms(1500);	
	Motor_SetTwo();
	delay_ms(1000);
	Motor_SetLow();
}

//电机定时器GPIO初始化
//static void Motor_TIM_Motor_GPIO_Config(void) 
//{	
//	GPIO_InitTypeDef GPIOB_InitStructure;
//	GPIO_InitTypeDef GPIOA_InitStructure;
//	
//	//开启重映射，C8T6只能重映射一次，此处选择TIM4的重映射
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
//	
//	RCC_APB2PeriphClockCmd(Motor_TIM_GPIOB_CLK, ENABLE );
//	RCC_APB2PeriphClockCmd(Motor_TIM_GPIOA_CLK, ENABLE );	
//	
//	
////	GPIO_InitStructure.GPIO_Pin =  Motor_TIM_Motor1_PIN ;
//	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    
//	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIOA_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP;
//	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor1_PIN;
//	GPIO_Init(Motor_TIM_Motor1_PORT, &GPIOB_InitStructure );
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor2_PIN;
//	GPIO_Init(Motor_TIM_Motor2_PORT, &GPIOB_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor3_PIN;
//	GPIO_Init(Motor_TIM_Motor3_PORT, &GPIOB_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor4_PIN;
//	GPIO_Init(Motor_TIM_Motor4_PORT, &GPIOB_InitStructure);
//	
//	
//	
//	GPIOA_InitStructure.GPIO_Pin =  Motor_TIM_Motor5_PIN;
//	GPIO_Init(Motor_TIM_Motor5_PORT, &GPIOA_InitStructure );
//	
//	GPIOA_InitStructure.GPIO_Pin =  Motor_TIM_Motor6_PIN;
//	GPIO_Init(Motor_TIM_Motor6_PORT, &GPIOA_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor7_PIN;
//	GPIO_Init(Motor_TIM_Motor7_PORT, &GPIOB_InitStructure);
//	
//	GPIOB_InitStructure.GPIO_Pin =  Motor_TIM_Motor8_PIN;
//	GPIO_Init(Motor_TIM_Motor8_PORT, &GPIOB_InitStructure);
//	
////	//重映射，将通道3和4映射到 PB10 PB11
////	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
//}

/*******************************重要注释*****************************/
/*
由于采用STM32C8T6单片机，定时器资源较为紧张，故电调PWM输出所用通用定时器与时基定时器共用同一通用定时器（TIM4），
定时器中断相关寄存器初始化代码位于timbase.c文件中，此处仅对定时相关寄存器进行初始化
对以下定时器初始化代码的任何修改有可能影响到时基的正常工作，请注意。
*/
/*******************************重要注释*****************************/

//static void Motor_TIM_Motor_Mode_Config(void)//电机定时器模式初始化
//{
//	TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM4_OCInitStructure;																				
//	
//	RCC_APB1PeriphClockCmd( Motor_TIM4_CLK, ENABLE );
//	
//	//重映射,不加此函数会使TIM4无法正常使用
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4 , ENABLE);
//	

//  /* TIM4基本定时器配置 */		 
//	TIM4_TimeBaseStructure.TIM_Period = 1000 - 1;       						 //当定时器从0计数到999，即为1000次，为一个定时周期
//	TIM4_TimeBaseStructure.TIM_Prescaler = 72000/Frequency-1;	    			//设置预分频（通过计算得出）
//	TIM4_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频(这里用不到)
//	TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
//	TIM_TimeBaseInit(Motor_TIM4, &TIM4_TimeBaseStructure);

//  /* PWM模式配置 */
//	TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//配置为PWM模式1
//	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
//	TIM4_OCInitStructure.TIM_Pulse = 0;//	15						   //设置初始PWM脉冲宽度为0	（此处不重要，初始化会运行油门置零代码）
//	TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为低电平

//	Motor_TIM_Motor1OCInit( Motor_TIM4, &TIM4_OCInitStructure );	 		//使能各个通道的输出通道					
//	Motor_TIM_Motor2OCInit( Motor_TIM4, &TIM4_OCInitStructure );	
//	Motor_TIM_Motor3OCInit( Motor_TIM4, &TIM4_OCInitStructure );	 	
//	Motor_TIM_Motor4OCInit( Motor_TIM4, &TIM4_OCInitStructure );	 		
//	
//	Motor_TIM_Motor1PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );	//使能各个通道的CCR预装载功能
//	Motor_TIM_Motor2PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor3PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor4PreloadConfig  ( Motor_TIM4, TIM_OCPreload_Enable );


//	TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM3_OCInitStructure;																				
//	
//	RCC_APB1PeriphClockCmd( Motor_TIM3_CLK, ENABLE );

//  /* TIM3基本定时器配置 */		 
//	TIM3_TimeBaseStructure.TIM_Period = 1000 - 1;       							  //当定时器从0计数到999，即为1000次，为一个定时周期
//	TIM3_TimeBaseStructure.TIM_Prescaler = 72000/Frequency-1;	    		//设置预分频（通过计算得出）	//200Hz
//	TIM3_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频(这里用不到)
//	TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
//	TIM_TimeBaseInit(Motor_TIM3, &TIM3_TimeBaseStructure);

//  /* PWM模式配置 */
//	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//配置为PWM模式1
//	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
//	TIM3_OCInitStructure.TIM_Pulse = 0;	//15									  			//设置初始PWM脉冲宽度为0	（此处不重要，初始化会运行油门置零代码）
//	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为低电平

//	Motor_TIM_Motor1OCInit( Motor_TIM3, &TIM3_OCInitStructure );	 		//使能各个通道的输出通道					
//	Motor_TIM_Motor2OCInit( Motor_TIM3, &TIM3_OCInitStructure );	
//	Motor_TIM_Motor3OCInit( Motor_TIM3, &TIM3_OCInitStructure );	 	
//	Motor_TIM_Motor4OCInit( Motor_TIM3, &TIM3_OCInitStructure );	 		
//	
//	Motor_TIM_Motor1PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );	//使能各个通道的CCR预装载功能
//	Motor_TIM_Motor2PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor3PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );	
//	Motor_TIM_Motor4PreloadConfig  ( Motor_TIM3, TIM_OCPreload_Enable );
//	
//	

//	TIM_ARRPreloadConfig(Motor_TIM4, ENABLE);			 				//使能Motor_TIM4重载寄存器ARR
//	TIM_ARRPreloadConfig(Motor_TIM3, ENABLE);			 				//使能Motor_TIM3重载寄存器ARR

//	TIM_Cmd(Motor_TIM4, ENABLE);                   						//使能定时器	
//	TIM_Cmd(Motor_TIM3, ENABLE);                   						//使能定时器		
//}

/**********************************************************
函数名：void Motor_SetSpeed(uint8_t Motornum,int16_t Speed)
功能：设定指定电机的转速
参数：	电机编号motornum，Motor1~4
			速度speed -999~999对应满反转~满正传
返回：无
本函数内部的计算公式，可以根据motor.h中所设置的频率、最大、最小、中位油门时间，自动将速度值映射到输出比较CCR寄存器
从而通过修改motor.h中宏的值，即可适应各种不同参数的电调
**********************************************************/
void Motor_SetSpeed(uint8_t motornum,int16_t speed)
{	
	uint16_t Tim_CCR;
	if(speed>999||speed<-999)//超过范围则返回
		return;
	if(speed>0)
		Tim_CCR=((double)Frequency/1000.0-1.0)*((double)Time_Mid+((double)speed/999.0)*(double)(Time_Max-Time_Mid));
	else
		Tim_CCR=((double)Frequency/1000.0-1.0)*((double)Time_Mid-((double)(-speed)/999.0)*(double)(Time_Mid-Time_Min));
	switch(motornum)
		{
			case Motor1: Motor1_Speed=Tim_CCR;break;
			case Motor2: Motor2_Speed=Tim_CCR;break;
			case Motor3: Motor3_Speed=Tim_CCR;break;
			case Motor4: Motor4_Speed=Tim_CCR;break;
			case Motor5: Motor5_Speed=Tim_CCR;break;
			case Motor6: Motor6_Speed=Tim_CCR;break;
//			case Motor7: Motor7_Speed=Tim_CCR;break;
//			case Motor8: Motor8_Speed=Tim_CCR;break;
		}
}

/**********************************************************
函数名：void Motor_fun(void)
功能：中断中反复执行的电机函数，将Motor结构体中的四个电机转速实现到PWM输出信号上
参数：无
返回：无
**********************************************************/
void Motor_fun(void)
{
	Motor_SetSpeed(Motor1,Motor.motor1_speed);
	Motor_SetSpeed(Motor2,Motor.motor2_speed);
	Motor_SetSpeed(Motor3,Motor.motor3_speed);
	Motor_SetSpeed(Motor4,Motor.motor4_speed);
	
	Motor_SetSpeed(Motor5,Motor.motor5_speed);
	Motor_SetSpeed(Motor6,Motor.motor6_speed);
//	Motor_SetSpeed(Motor7,Motor.motor7_speed);
//	Motor_SetSpeed(Motor8,Motor.motor8_speed);
}

//电调初始化
void Motor_SetOne(void)
{
//	TIM_SetCompare1(TIM4,300);//定时器输出总周期等于 （ARR+1）*(PSC+1)/CLK	ClK为72MHz
//	TIM_SetCompare2(TIM4,300);		
//	TIM_SetCompare3(TIM4,300);		
//	TIM_SetCompare4(TIM4,300);	

//	TIM_SetCompare1(TIM3,300);	
//	TIM_SetCompare2(TIM3,300);		
//	TIM_SetCompare3(TIM3,300);		
//	TIM_SetCompare4(TIM3,300);	
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,300);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,300);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,300);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,300);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,300);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,300);
}

void Motor_SetTwo(void)
{
//	TIM_SetCompare1(TIM4,400);
//	TIM_SetCompare2(TIM4,400);		
//	TIM_SetCompare3(TIM4,400);		
//	TIM_SetCompare4(TIM4,400);
//	                    
//	TIM_SetCompare1(TIM3,400);	
//	TIM_SetCompare2(TIM3,400);		
//	TIM_SetCompare3(TIM3,400);		
//	TIM_SetCompare4(TIM3,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,400);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,400);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,400);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,400);
}

void Motor_SetLow(void)
{
//	TIM_SetCompare1(TIM4,0);
//	TIM_SetCompare2(TIM4,0);		
//	TIM_SetCompare3(TIM4,0);		
//	TIM_SetCompare4(TIM4,0);
//	
//	TIM_SetCompare1(TIM3,0);	
//	TIM_SetCompare2(TIM3,0);		
//	TIM_SetCompare3(TIM3,0);		
//	TIM_SetCompare4(TIM3,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,0);
}
