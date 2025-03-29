#ifndef  FUNC_H
#define FUNC_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "muart.h"


#define MAXCMDLEN 256             /* 临时存放待处理数据Buffer大小 */

extern struct uartfunc_str CmdDataArg ;

void SendDataToDebug(uint8_t* pbuff, uint16_t dsize);
uint8_t  GetCmdData(uint8_t *dbuff , uint16_t *lenth,uint8_t cdata ,void *flagstart);



#endif

