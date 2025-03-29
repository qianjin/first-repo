/************************************摄像头舵机驱动代码********************************/
/*
驱动180度的sg90舵机
*/
#include "camera.h"
#include "stm32f10x.h"                  // Device header

uint8_t camera_angle=128;//舵机角度，0~180°映射到该变量的0~225

/*
摄像头舵机GPIO初始化
*/
static void Camera_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  CAMERA_TIM_GPIO_APBxClock_FUN  ( CAMERA_TIM_GPIO_CLK, ENABLE );

  GPIO_InitStructure.GPIO_Pin =  CAMERA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init( CAMERA_PORT, &GPIO_InitStructure );
}
/*
摄像头舵机PWM通用定时器设定函数
*/
static void Camera_TIMMode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	CAMERA_TIM_APBxClock_FUN ( CAMERA_TIM_CLK, ENABLE );

  /* 基本定时器配置 */		 
  TIM_TimeBaseStructure.TIM_Period = 999;     							 
  TIM_TimeBaseStructure.TIM_Prescaler = 72000/Frequency_CAM-1;	    							//根据预设参数设置预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频(这里用不到)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
  TIM_TimeBaseInit(CAMERA_TIMx, &TIM_TimeBaseStructure);

  /* PWM模式配置 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
  TIM_OCInitStructure.TIM_Pulse = 0;										  			//设置初始PWM脉冲宽度为0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为高电平

  CAMERA_TIM_OCxInit ( CAMERA_TIMx, &TIM_OCInitStructure );	 									//使能通道3
  CAMERA_TIM_OCxPreloadConfig ( CAMERA_TIMx, TIM_OCPreload_Enable );						//使能预装载	

  TIM_ARRPreloadConfig(CAMERA_TIMx, ENABLE);			 										//使能TIM3重载寄存器ARR
	
  /* TIM3 enable counter */
  TIM_Cmd(CAMERA_TIMx, ENABLE);                   										//使能定时器3	
}

/*
摄像头舵机初始化函数
*/
void Camera_Init(void)
{
	Camera_GPIO_Init();//GPIO初始化
	Camera_TIMMode_Config();//PWM通用定时器初始化
	Camera_SetPercent(camera_angle);//设定摄像头舵机角度为初始角度
}

/*
功能：用于设置舵机行程内百分比
参数：angle 0~255对应0~180°
*/
void Camera_SetPercent(uint8_t angle)
{
	float percent=((float)(angle))/2.560F;//将百分比0~100映射到变量angle的0~225
	uint16_t time=(Time_Max_CAM-Time_Min_CAM)*(percent/100.0)+Time_Min_CAM;//通过计算求出高电平时间
	CAMERA_CCR=(time)/(1000/(Frequency_CAM));//将计算后的CCR值赋值
}
