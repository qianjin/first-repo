/************************************JY901���������Ǵ�����********************************/
/*
�ٷ��ṩ���������룬��ע�ʹų���δʹ�ò�����ش���
���ܣ�ΪROV�ṩ����Ƕȡ����ٶȡ��Ǽ��ٶ�
ע��ƫ���ǣ�angle_z��Ϊ�����ǻ��ֵó����ǳ�����ȷ���ڹ����в�δʹ��
		JY901֧��IICͨ�źʹ���ͨ�ţ�������ʹ�õ�Ƭ������2����ͨ�ţ��ڴ����ж��е���JY901_DataHandler��������������ݼ���
		JY901_val�еĸ�������Ϊ���յ���̬����
ʹ�÷������ڴ����ж��е���JY901_DataHandler�����������ԭʼ���ݣ�JY901_val�еĸ�������Ϊ���յ���̬����
*/
#include "JY901.h"
#include "usart2.h"
#include "string.h"//�ں�memcpy����
#include "dma_circular_queue.h"

//�ٷ����̶���ĸ��ֽṹ�壬������ᣬֱ�ӵ��ò�������
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

//���պ������õ����Ƕ�ֵ
void JY901_DataHandler(uint8_t ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
//			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
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
		ucRxCnt=0;//��ջ�����
	}
	
		
	JY901_val.acc_x = (float)stcAcc.a[0]/32768*16;//����õ����˶���̬����
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
