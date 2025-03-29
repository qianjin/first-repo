/************************************底层驱动相关代码********************************/
/*
功能：配置芯片的底层驱动
*/

#include "board.h"

//#include "servo.h"

/*
底层驱动程序初始化函数
上电运行
*/
void Board_Init(void)
{
//	delay_init(72);//延时功能初始化，所用芯片时钟频率为72MHz
	Motor_Init();//电调PWM输出初始化		
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//初始化NVIC优先级组配置
//	USART1_Config(115200);//串口1初始化，波特率115200
//	JY901_Init();//JY901陀螺仪初始化	
//	Camera_Init();//摄像头舵机初始化
	MS5837_Init();//深度传感器初始化
//	Servo_Init();//外设各个舵机初始化
	
//	Timebase_Init();//时基定时器初始化
}

