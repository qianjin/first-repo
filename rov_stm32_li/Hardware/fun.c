#include "func.h"

uint16_t  CmdDataLenth = 0;         //���������ݳ���
uint8_t CmdDataBuff[MAXCMDLEN];     //��ʱ��Ŵ���������Buffer

struct uartfunc_str CmdDataArg = {CmdDataBuff, &CmdDataLenth, (void*)&huart1};


/*********************************************************************************************************
** Function name:       GetCmdData
** Descriptions:        �Ӵ����������ҵ��������ݣ���������һ������
** input parameters:    dbuff ������ָ��
                        lenth �����ݳ���
                        cdata����ǰ�յ����ֽ�
                        flagstart���յİ�ͷ��־
** output parameters:   parg����Ӧ���޸Ĳ���ָ��
** Returned value:      ��
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
** Descriptions:        ���ڷ������ݺ�����װ
** input parameters:    dbuff ������ָ��
**                      lenth �����ݳ���
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void SendDataToDebug(uint8_t* pbuff, uint16_t dsize)
{
    SendUartBuff(&huart1, pbuff, dsize);
}


