#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DMA_RESERVE_LEN  256		//DMA保留长度,建议留够1包数据最大长度
#define LENGTHUSART1IN  4096        /* 串口1接收数据缓冲Buffer大小 */
#define LENGTHUSART1OUT  4096       /* 串口1发送数据缓冲Buffer大小 */

typedef void SeqQueue;
typedef unsigned char TSeqQueueNode;
typedef struct _tag_SeqQueue
{
    int capacity;           /* 数据缓冲Buffer大小 */
    int length;             /* 数据长度 */
    int front;              /* 头指针 */
    int rear;               /* 尾指针 */
    int wrxsize;            /* 已从数据缓冲区取出的数据长度 */
    int rxsize;             /* 实际收到的数据长度 */
    TSeqQueueNode* node;    /* 数据缓冲Buffer */
} TSeqQueue;


extern TSeqQueue Usart1QueueIn;
extern TSeqQueue Usart1QueueOut ;


void SeqQueueInit(void);
int SeqQueue_AppendPointer(SeqQueue* queue, int size);
int SeqQueue_Create(TSeqQueue* queue, int capacity, TSeqQueueNode* databuff);
int SeqQueue_Length(SeqQueue* queue);
int SeqQueue_Retrieve(SeqQueue* queue, TSeqQueueNode* data);
int SeqQueue_AppendMultiple(SeqQueue* queue, TSeqQueueNode* pitem, int size) ;
int SeqQueue_RetrieveMultiple(SeqQueue* queue, TSeqQueueNode* pitem, int maxsize);



#endif