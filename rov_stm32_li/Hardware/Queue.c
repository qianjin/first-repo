#include "Queue.h"
TSeqQueue Usart1QueueIn;        /* 串口1接收数据队列 */
TSeqQueue Usart1QueueOut;       /* 串口2发送数据队列 */

TSeqQueueNode DataUsart1In[LENGTHUSART1IN + DMA_RESERVE_LEN] = {0};       /* 串口1接收数据缓冲区 */
TSeqQueueNode DataUsart1Out[LENGTHUSART1OUT] = {0};     /* 串口1发送数据缓冲区 */


/*********************************************************************************************************
** Function name:       SeqQueue_RetrieveMultiple
** Descriptions:        从队列取数据函数
** input parameters:    queue ：待取数据队列
**                      pitem ：待存放数据Buffer
                        maxsize：最大取多少字节数据

** output parameters:   无
** Returned value:      lenth  实际取出数据长度
*********************************************************************************************************/
int SeqQueue_RetrieveMultiple(SeqQueue* queue, TSeqQueueNode* pitem, int maxsize)
{
    int lenth = 0;
    TSeqQueue* sQueue = (TSeqQueue*)queue;


    if(maxsize<=0)
    {
        return 0;
    }
		
		lenth = SeqQueue_Length(sQueue);
    
    if(lenth > maxsize)
    {
        lenth = maxsize;
    }
    
    if(sQueue->capacity  > (lenth + sQueue->rear))//要取的长度不经过下标0
    {
        memcpy(pitem, sQueue->node + sQueue->rear, lenth*sizeof(TSeqQueueNode));
        sQueue->rear += lenth;
    }
    else
    {
        memcpy(pitem, (sQueue->node+sQueue->rear), (sQueue->capacity-sQueue->rear) * sizeof(TSeqQueueNode));
        memcpy(pitem + (sQueue->capacity-sQueue->rear), sQueue->node, (lenth - (sQueue->capacity-sQueue->rear)) * sizeof(TSeqQueueNode));
        sQueue->rear += lenth;
        sQueue->rear -= sQueue->capacity;
    }
    return lenth;
}

/*********************************************************************************************************
** Function name:       SeqQueue_AppendMultiple
** Descriptions:        往队列放数据函数
** input parameters:    queue ：待取数据队列
**                      pitem ：待存放数据Buffer
                        maxsize：最大放多少字节数据

** output parameters:   无
** Returned value:      lenth  实际放入数据长度
*********************************************************************************************************/
int SeqQueue_AppendMultiple(SeqQueue* queue, TSeqQueueNode* pitem, int size)
{
    int num1 = 0;
    int ret = 0;
    TSeqQueue* sQueue = (TSeqQueue*)queue;
		ret = (sQueue != NULL);

    if((sQueue->front + size) <= (sQueue->capacity - 1))
    {
        memcpy(sQueue->node + sQueue->front, pitem, size * sizeof(TSeqQueueNode));
        sQueue->front += size;
    }
    else
    {
        num1 = sQueue->capacity - sQueue->front;
        memcpy(sQueue->node + sQueue->front, pitem, num1 * sizeof(TSeqQueueNode));
        memcpy(sQueue->node, pitem+num1, (size - num1) * sizeof(TSeqQueueNode));

        sQueue->front += size;
        sQueue->front -= sQueue->capacity;
    }
    if(sQueue->front == 0)
    {
        size = size;
    }

    return ret;
}
 
/*********************************************************************************************************
** Function name:       SeqQueue_Retrieve
** Descriptions:        从接收队列中取1字节数据
** input parameters:    queue ：待取数据队列
**                      data 存放数据地址
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int SeqQueue_Retrieve(SeqQueue* queue, TSeqQueueNode* data)
{
    int ret = 0;
    
    TSeqQueue* sQueue = (TSeqQueue*)queue;
    {
        *data = (sQueue->node[sQueue->rear]);
        sQueue->rear = (sQueue->rear + 1) % sQueue->capacity;
        ret = 1;
    }
    
    return ret;
}

/*********************************************************************************************************
** Function name:       SeqQueue_Length
** Descriptions:        计算队列已存放数据长度
** input parameters:    queue ：待计算队列
** output parameters:   队列数据长度
** Returned value:      无
*********************************************************************************************************/
int SeqQueue_Length(SeqQueue* queue)
{
    int ret = -1;
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if(sQueue != NULL )
    {
        if(sQueue->front >= sQueue->rear)
        {
            ret = sQueue->front - sQueue->rear;
        }
        else
        {
            ret = sQueue->front + sQueue->capacity - sQueue->rear;
        }
    }

    return ret;
}

/*********************************************************************************************************
** Function name:       SeqQueue_Create
** Descriptions:        队列初始化
** input parameters:    queue ：待初始化队列
                        capacity：Buffer缓冲区大小
                        databuff：缓冲区Buffer首地址

** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int SeqQueue_Create(TSeqQueue* queue, int capacity, TSeqQueueNode* databuff)
{
    int ret = 0;
    if(( capacity >= 0 )	&&(databuff != NULL))
    {
        queue->node = databuff;
        queue->capacity = capacity;
        queue->length = 0;
        queue->front = 0;
        queue->rear = 0;
        queue->node = databuff;
        ret = 1;
    }
    return ret;
}

/*********************************************************************************************************
** Function name:       SeqQueue_AppendPointer
** Descriptions:        计算Buffer缓冲区已使用大小
** input parameters:    queue ：队列
                        size：Buffer缓冲区大小
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int SeqQueue_AppendPointer(SeqQueue* queue, int size)
{
    int ret = 0;
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if((sQueue->front + size) < (sQueue->capacity))
    {
        ret = size;
    }
    else
    {
        ret = sQueue->capacity - sQueue->front;
    }
    
    return ret;
}

/*********************************************************************************************************
** Function name:       SeqQueueInit
** Descriptions:        队列初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void SeqQueueInit(void)
{
    SeqQueue_Create(&Usart1QueueIn, LENGTHUSART1IN, DataUsart1In);
	SeqQueue_Create(&Usart1QueueOut, LENGTHUSART1OUT, DataUsart1Out);
}



