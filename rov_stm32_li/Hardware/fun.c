#include "func.h"

uint16_t  CmdDataLenth = 0;         //待处理数据长度
uint8_t CmdDataBuff[MAXCMDLEN];     //临时存放待处理数据Buffer

struct uartfunc_str CmdDataArg = {CmdDataBuff, &CmdDataLenth, (void*)&huart1};


/*********************************************************************************************************
** Function name:       GetCmdData
** Descriptions:        从串口数据中找到整包数据，待进行下一步分析
** input parameters:    dbuff ：数据指针
                        lenth ：数据长度
                        cdata：当前收到的字节
                        flagstart：收的包头标志
** output parameters:   parg：对应的修改参数指针
** Returned value:      无
*********************************************************************************************************/
uint8_t GetCmdData(uint8_t* dbuff, uint16_t* lenth, uint8_t cdata, void* flagstart)
{
	dbuff[(*lenth)++] = cdata;
	
	if((*lenth) >= MAXCMDLEN)
	{
		(*lenth) = 0;
	}

	if(((dbuff[(*lenth) - 1]) == 0x0A)&&((dbuff[(*lenth) - 2]) == 0x0D))
	{
		SendDataToDebug("----recv OK!\r\n", strlen("----recv OK!\r\n"));
		(*lenth) = 0;
	}
    return 0;
}
/*********************************************************************************************************
** Function name:       SendDataToDebug
** Descriptions:        串口发送数据函数封装
** input parameters:    dbuff ：数据指针
**                      lenth ：数据长度
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void SendDataToDebug(uint8_t* pbuff, uint16_t dsize)
{
    SendUartBuff(&huart1, pbuff, dsize);
}


