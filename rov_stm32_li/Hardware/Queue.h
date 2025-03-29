#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DMA_RESERVE_LEN  256		//DMA��������,��������1��������󳤶�
#define LENGTHUSART1IN  4096        /* ����1�������ݻ���Buffer��С */
#define LENGTHUSART1OUT  4096       /* ����1�������ݻ���Buffer��С */

typedef void SeqQueue;
typedef unsigned char TSeqQueueNode;
typedef struct _tag_SeqQueue
{
    int capacity;           /* ���ݻ���Buffer��С */
    int length;             /* ���ݳ��� */
    int front;              /* ͷָ�� */
    int rear;               /* βָ�� */
    int wrxsize;            /* �Ѵ����ݻ�����ȡ�������ݳ��� */
    int rxsize;             /* ʵ���յ������ݳ��� */
    TSeqQueueNode* node;    /* ���ݻ���Buffer */
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