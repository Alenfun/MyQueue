/**
  ******************************************************************************
  * @file    MyQueue.c
  * @author  mgdg
  * @version V1.0.0
  * @date    2017-09-13
  * @brief   
  ******************************************************************************
 **/


#include "MyQueue.h"


/**
  * @brief	��ʼ������
  * @param	*queue�����ж���
  * @param	*buffer�����������׵�ַ
  * @param	max_size����������

  * @return	void	
  * @remark		
  */
void queue_init_static(Queue_Typedef *queue, uint8_t *buffer, uint16_t max_size) 
{
    queue->buffer = buffer;
    queue->max_size = max_size;
    queue->front = queue->rear = 0;
}

/**
  * @brief	����������ݸ���
  * @param	*QUEUE�����ж���
  *
  * @return	uint16_t:�������ݸ���	
  * @remark		
  */
uint16_t  queue_GetCount(Queue_Typedef *queue)
{
	if(queue->front < queue->rear)
		return queue->front + queue->max_size - queue->rear;
	else
		return queue->front - queue->rear;
}

/**
  * @brief	�������ʣ�����ݸ���
  * @param	*QUEUE�����ж���
  *
  * @return	uint16_t:����ʣ�����ݸ���	
  * @remark		
  */
uint16_t queue_GetLeftCount(Queue_Typedef *queue)
{
	if(queue->front < queue->rear)
		return (queue->rear - queue->front);
	else
		return (queue->max_size - (queue->front - queue->rear));
}

/**
  * @brief	��������
  * @param	*QUEUE�����ж���
  *
  * @return	bool:������״̬
  * @remark		
  */
bool queue_IsFull(Queue_Typedef *queue)
{
	return queue_GetCount(queue)  == (queue->max_size - 1);
}

/**
  * @brief	�����п�
  * @param	*QUEUE�����ж���
  *
  * @return	bool:���п�״̬
  * @remark		
  */
bool queue_IsEmpty(Queue_Typedef *queue)
{
	return queue_GetCount(queue) == 0;
};

/**
  * @brief	��ȡ��������
  * @param	*QUEUE�����ж���
  *
  * @return	uint16_t:��������
  * @remark		
  */
uint16_t queue_GetQueSize(Queue_Typedef *queue)
{	
	return queue->max_size;
};

/**
  * @brief	�����г�Ա�������
  * @param	*QUEUE�����ж���
  * @param	ch������
  *
  * @return	bool:����״̬
  * @remark		
  */
bool queue_Put(Queue_Typedef *queue,uint8_t ch)
{
  	if(!queue_IsFull(queue))
  	{
    	queue->buffer[queue->front]= ch;
    	queue->front ++;
    	queue->front %= queue->max_size; 
    	return true;
  	}
  	else
    	return false;
}

/**
  * @brief	��ָ�����ȳ�Ա�������
  * @param	*QUEUE�����ж���
  * @param	buf������
  * @param	len������
  * @return	bool:����״̬
  * @remark	��bug�����иպô�����ʱ��ᵼ�¶���Ϊ�գ����Զ��в��ܴ���	
  */
bool queue_PutLength(Queue_Typedef *queue,const uint8_t *buf,uint16_t len)
{
	uint16_t i;
	if(len < queue_GetLeftCount(queue))
	{
		for(i=0;i<len;i++)
		{
			queue->buffer[queue->front]= *(buf++);
    		queue->front ++;
    		queue->front %= queue->max_size;
		}
		return true;
	}
	else
		return false;
}

/**
  * @brief	�����г�Աȡ������
  * @param	*QUEUE�����ж���
  * @param	ch������
  * @return	bool:����״̬
  * @remark		
  */
bool queue_Get(Queue_Typedef *queue,uint8_t *ch)
{
  	if (queue_GetCount(queue))
  	{
    	*ch = queue->buffer[queue->rear];
    	queue->rear++;
    	queue->rear%=queue->max_size;   
    	return true;
  	}
  	else
    	return false;
}

/**
  * @brief	��ȡ���ݣ����ǲ���������
  * @param	*QUEUE�����ж���
  * @param	ch������
  * @return	bool:����״̬
  * @remark		
  */
bool queue_Peek(Queue_Typedef *queue,uint8_t *ch)
{
  	if (queue_GetCount(queue))
  	{
    	*ch = queue->buffer[queue->rear];
    	return true;
  	}
  	else
    	return false;
}

/**
  * @brief	��ȡָ���������ݣ����ǲ���������
  * @param	*QUEUE�����ж���
  * @param	*buffer�������׵�ַ
  * @param	length�����ݳ���
  * @return	bool:����״̬
  * @remark		
  */
bool queue_PeekLength(Queue_Typedef *queue,uint8_t *buffer,uint16_t length)
{
	uint16_t i;
	
	if(length > queue_GetCount(queue))
		return false;
	
	for (i = 0; i < length; ++i)
	{
		*(buffer++) = queue->buffer[(queue->rear + i) % queue->max_size];
	}

	return true;
}

/**
  * @brief	��ȡ�������ݣ����ǲ���������
  * @param	*QUEUE�����ж���
  * @param	*buffer�������׵�ַ
  * @return	bool:����״̬
  * @remark	�������ռ�С�ڶ���ʱ�����´���	
  */
bool queue_PeekAll(Queue_Typedef *queue,uint8_t *buffer)
{
	uint16_t back_tail;

	if( !buffer ) return false;

	back_tail = queue->rear;
	
	while (back_tail != queue->front)
	{
		*(buffer++) = queue->buffer[back_tail++];
		back_tail %= queue->max_size;
	}

	return true;
}

/**
  * @brief	POPһ�����ݣ���ʹ������
  * @param	*QUEUE�����ж���
  * @return	bool:����״̬
  * @remark		
  */
bool queue_Pop(Queue_Typedef *queue)
{
  	if (queue_GetCount(queue))
  	{
    	queue->rear++;
    	queue->rear%=queue->max_size;   
		return true;
  	}
	else
		return false;
}

/**
  * @brief	��ȡ������ָ��ƫ��λ�õ�һ������
  * @param	*QUEUE�����ж���
  * @param	offset��ƫ��
  * 
  * @return	bool:����״̬
  * @remark		
  */
bool queue_Peek_Offset(Queue_Typedef *queue,uint8_t *ch,uint16_t offset)
{
	uint16_t temp;

	if((offset+1) > (queue_GetCount(queue)))
		return false;
	
	temp = queue->rear+offset;
	temp %= queue->max_size; 
	*ch = queue->buffer[temp];
	return true;
}

//ȡ��ָ�����ȣ�������
/**
  * @brief	ȡ��ָ�����ȣ�������
  * @param	*QUEUE�����ж���
  * @param	*buffer�������׵�ַ
  * @param	length������
  * 
  * @return	bool:����״̬
  * @remark		
  */
bool queue_PeekPopLength(Queue_Typedef *queue,uint8_t *buffer,uint16_t length)
{
	uint16_t i;
	
	if(length > queue_GetCount(queue))
		return false;
	
	for (i = 0; i < length; ++i)
	{
		*(buffer++) = queue->buffer[(queue->rear) % queue->max_size];
		queue->rear++;
		queue->rear%=queue->max_size; 

	}
	return true;
}

/**
  * @brief	POPָ���������ݣ���ʹ������
  * @param	*QUEUE�����ж���
  * @param	length������
  * 
  * @return	bool:����״̬
  * @remark		
  */
bool queue_PopLength(Queue_Typedef *queue,uint16_t length)
{
	if(length <= queue_GetCount(queue))
  	{
    	queue->rear+=length;
    	queue->rear%=queue->max_size;   
		return true;
  	}
	else
		return false;
}

/**
  * @brief	POP�������ݣ���ʹ������
  * @param	*QUEUE�����ж���
  * @return	void
  * @remark		
  */
void queue_PopAll(Queue_Typedef *queue)
{
	queue->rear = queue->front;
}
  


//demo
#if 0 

#define DEMO_QUEUE_MAX_SIZE	128
static queue_Typedef DemoQueue;			//״̬���¼�����
static uint8_t queuebuf[DEMO_QUEUE_MAX_SIZE];

//��ʼ������
queue_init_static(&DemoQueue,queuebuf,DEMO_QUEUE_MAX_SIZE);

//�����ݷ������
bool put_in_queue(const uint8_t* pBuf,uint16_t len)
{
	if( !pBuf || len <1 ) 
		return false;

	if(queue_PutLength(&DemoQueue,pBuf,len))
		return true;
	else
		return false;
}

#endif