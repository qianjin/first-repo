#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"


typedef struct
{
	int16_t motor1_speed;
	int16_t motor2_speed;
	int16_t motor3_speed;
	int16_t motor4_speed;
	
	int16_t motor5_speed;
	int16_t motor6_speed;
//	int16_t motor7_speed;
//	int16_t motor8_speed;
}MOTOR;//����ٶȽṹ�壬����8�������ת�٣���ֵ��Χ-999~+999��Ӧ����ת~������

extern MOTOR Motor;//extern�ؼ��֣��������ⲿ����



/*************��������궨��***********/
/*
���޸���Щ������������Ӧ��ͬ�������
*/
#define		Frequency		200//PWM���Ƶ�ʣ���λ����Hz��ע����Ƶ���ڱ�������ͬʱҲΪʱ����ʱ��Ƶ�ʣ��޸Ļ�������Ӱ�죩
#define		Time_Min		1040//�����СPWM�ߵ�ƽʱ�䣬��λ΢��us
#define		Time_Mid		1500//�����λPWM�ߵ�ƽʱ�䣬��λ΢��us
#define		Time_Max		1940//������PWM�ߵ�ƽʱ�䣬��λ΢��us




/***************************��ʱ�����PWM���****************************************/

//#define             Motor_TIM_GPIOA_CLK                        	RCC_APB2Periph_GPIOA
//#define             Motor_TIM_GPIOB_CLK              			RCC_APB2Periph_GPIOB

//#define				Motor_TIM4_CLK							    RCC_APB1Periph_TIM4
#define				Motor_TIM1									TIM1
//#define             Motor_TIM_Motor1_PORT                       GPIOB
//#define             Motor_TIM_Motor1_PIN                        GPIO_Pin_6
//#define             Motor_TIM_Motor2_PORT                       GPIOB
//#define             Motor_TIM_Motor2_PIN                        GPIO_Pin_7
//#define             Motor_TIM_Motor3_PORT                       GPIOB
//#define             Motor_TIM_Motor3_PIN                        GPIO_Pin_8
//#define             Motor_TIM_Motor4_PORT                       GPIOB
//#define             Motor_TIM_Motor4_PIN                        GPIO_Pin_9

//#define				Motor_TIM3_CLK							    RCC_APB1Periph_TIM3
#define				Motor_TIM2									TIM2
//#define             Motor_TIM_Motor5_PORT                       GPIOA
//#define             Motor_TIM_Motor5_PIN                        GPIO_Pin_6
//#define             Motor_TIM_Motor6_PORT                       GPIOA
//#define             Motor_TIM_Motor6_PIN                        GPIO_Pin_7
//#define             Motor_TIM_Motor7_PORT                       GPIOB
//#define             Motor_TIM_Motor7_PIN                        GPIO_Pin_0
//#define             Motor_TIM_Motor8_PORT                       GPIOB
//#define             Motor_TIM_Motor8_PIN                        GPIO_Pin_1


//#define             Motor_TIM_Motor1OCInit                      TIM_OC1Init         
//#define             Motor_TIM_Motor1PreloadConfig               TIM_OC1PreloadConfig  
//#define             Motor_TIM_Motor2OCInit                      TIM_OC2Init         
//#define             Motor_TIM_Motor2PreloadConfig               TIM_OC2PreloadConfig
//#define             Motor_TIM_Motor3OCInit                      TIM_OC3Init         
//#define             Motor_TIM_Motor3PreloadConfig               TIM_OC3PreloadConfig
//#define             Motor_TIM_Motor4OCInit                      TIM_OC4Init         
//#define             Motor_TIM_Motor4PreloadConfig               TIM_OC4PreloadConfig

//#define             Motor_TIM_Motor5OCInit                      TIM_OC1Init         
//#define             Motor_TIM_Motor5PreloadConfig               TIM_OC1PreloadConfig  
//#define             Motor_TIM_Motor6OCInit                      TIM_OC2Init         
//#define             Motor_TIM_Motor6PreloadConfig               TIM_OC2PreloadConfig
//#define             Motor_TIM_Motor7OCInit                      TIM_OC3Init         
//#define             Motor_TIM_Motor7PreloadConfig               TIM_OC3PreloadConfig
//#define             Motor_TIM_Motor8OCInit                      TIM_OC4Init         
//#define             Motor_TIM_Motor8PreloadConfig               TIM_OC4PreloadConfig

#define				Motor1_Speed								Motor_TIM1->CCR1	//�����CCR����
#define				Motor2_Speed								Motor_TIM1->CCR2
#define				Motor3_Speed								Motor_TIM1->CCR3
#define				Motor4_Speed								Motor_TIM1->CCR4
																		 
#define				Motor5_Speed								Motor_TIM2->CCR1	//�����CCR����
#define				Motor6_Speed								Motor_TIM2->CCR2
//#define				Motor7_Speed								Motor_TIM3->CCR3
//#define				Motor8_Speed								Motor_TIM3->CCR4





#define					Motor1			1
#define					Motor2			2
#define					Motor3			3
#define					Motor4			4
#define					Motor5			5
#define					Motor6			6
//#define					Motor7			7
//#define					Motor8			8

				



/**************************��������********************************/

void Motor_Init(void);
//static void Motor_TIM_Motor_GPIO_Config(void);
//static void Motor_TIM_Motor_Mode_Config(void);
void Motor_SetSpeed (uint8_t motornum,int16_t speed);
void Motor_fun(void);
void Motor_SetOne(void);
void Motor_SetTwo(void);
void Motor_SetLow(void);
#endif
