/************************************JY901九轴陀螺仪传感器********************************/
/*
官方提供的驱动代码，已注释磁场等未使用参数相关代码
功能：为ROV提供各轴角度、加速度、角加速度
注：偏航角（angle_z）为陀螺仪积分得出，非常不精确，在工程中并未使用
		JY901支持IIC通信和串口通信，本工程使用单片机串口2进行通信，在串口中断中调用JY901_DataHandler函数处理接收数据即可
		JY901_val中的各个参数为最终的姿态参数
使用方法：在串口中断中调用JY901_DataHandler函数处理接收原始数据，JY901_val中的各个参数为最终的姿态参数
*/
#include "JY901.h"
#include "usart2.h"
#include "string.h"//内含memcpy函数
#include "dma_circular_queue.h"

//官方例程定义的各种结构体，不用理会，直接调用参数即可
struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;

JY901_ValTypedef JY901_val;
DMA_CIRCULAR_QUEUE_RRD JY901_Queme;

void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}
short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}



void JY901_Queme_Init(void)
{
	//USART2x_Config();
	
}

//接收函数，得到各角度值
void JY901_DataHandler(uint8_t ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
//			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
//			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
//			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
//			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
//			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
//			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
//			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//清空缓存区
	}
	
		
	JY901_val.acc_x = (float)stcAcc.a[0]/32768*16;//计算得到各运动姿态参数
	JY901_val.acc_y = (float)stcAcc.a[1]/32768*16;
	JY901_val.acc_z = (float)stcAcc.a[2]/32768*16;
	JY901_val.gyro_x = (float)stcGyro.w[0]/32768*2000;
	JY901_val.gyro_y = (float)stcGyro.w[1]/32768*2000;
	JY901_val.gyro_z = (float)stcGyro.w[2]/32768*2000;
//	JY901_val.h_x = stcMag.h[0];
//	JY901_val.h_y = stcMag.h[1];
//	JY901_val.h_z = stcMag.h[2];
	JY901_val.angle_x = (float)stcAngle.Angle[0]/32768*180;
	JY901_val.angle_y = (float)stcAngle.Angle[1]/32768*180;
	JY901_val.angle_z = (float)stcAngle.Angle[2]/32768*180;
	
}
