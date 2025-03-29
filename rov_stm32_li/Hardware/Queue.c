#include "Queue.h"
TSeqQueue Usart1QueueIn;        /* ����1�������ݶ��� */
TSeqQueue Usart1QueueOut;       /* ����2�������ݶ��� */

TSeqQueueNode DataUsart1In[LENGTHUSART1IN + DMA_RESERVE_LEN] = {0};       /* ����1�������ݻ����� */
TSeqQueueNode DataUsart1Out[LENGTHUSART1OUT] = {0};     /* ����1�������ݻ����� */


/*********************************************************************************************************
** Function name:       SeqQueue_RetrieveMultiple
** Descriptions:        �Ӷ���ȡ���ݺ���
** input parameters:    queue ����ȡ���ݶ���
**                      pitem �����������Buffer
                        maxsize�����ȡ�����ֽ�����

** output parameters:   ��
** Returned value:      lenth  ʵ��ȡ�����ݳ���
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
    
    if(sQueue->capacity  > (lenth + sQueue->rear))//Ҫȡ�ĳ��Ȳ������±�0
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
** Descriptions:        �����з����ݺ���
** input parameters:    queue ����ȡ���ݶ���
**                      pitem �����������Buffer
                        maxsize�����Ŷ����ֽ�����

** output parameters:   ��
** Returned value:      lenth  ʵ�ʷ������ݳ���
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
** Descriptions:        �ӽ��ն�����ȡ1�ֽ�����
** input parameters:    queue ����ȡ���ݶ���
**                      data ������ݵ�ַ
** output parameters:   ��
** Returned value:      ��
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
** Descriptions:        ��������Ѵ�����ݳ���
** input parameters:    queue �����������
** output parameters:   �������ݳ���
** Returned value:      ��
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
** Descriptions:        ���г�ʼ��
** input parameters:    queue ������ʼ������
                        capacity��Buffer��������С
                        databuff��������Buffer�׵�ַ

** output parameters:   ��
** Returned value:      ��
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
** Descriptions:        ����Buffer��������ʹ�ô�С
** input parameters:    queue ������
                        size��Buffer��������С
** output parameters:   ��
** Returned value:      ��
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
** Descriptions:        ���г�ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void SeqQueueInit(void)
{
    SeqQueue_Create(&Usart1QueueIn, LENGTHUSART1IN, DataUsart1In);
	SeqQueue_Create(&Usart1QueueOut, LENGTHUSART1OUT, DataUsart1Out);
}



