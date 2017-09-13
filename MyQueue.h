/**
  ******************************************************************************
  * @file    MyQueue.h
  * @author  mgdg
  * @version V1.0.0
  * @date    2017-09-13
  * @brief   
  ******************************************************************************
 **/


#ifndef __MYQUEUE_H
#define __MYQUEUE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
  uint8_t *buffer;    // ���ݻ�����
  uint16_t max_size;  // ������󳤶�
  uint16_t front;     // ����ͷ
  uint16_t rear;      // ����β
	
}Queue_Typedef;


void queue_init_static(Queue_Typedef *queue, uint8_t *buffer, uint16_t max_size);
uint16_t  queue_GetCount(Queue_Typedef *queue);
uint16_t queue_GetLeftCount(Queue_Typedef *queue);
bool queue_IsFull(Queue_Typedef *queue);
bool queue_IsEmpty(Queue_Typedef *queue);
uint16_t queue_GetQueSize(Queue_Typedef *queue);
bool queue_Put(Queue_Typedef *queue,uint8_t ch);
bool queue_PutLength(Queue_Typedef *queue,const uint8_t *buf,uint16_t len);
bool queue_Get(Queue_Typedef *queue,uint8_t *ch);
bool queue_Peek(Queue_Typedef *queue,uint8_t *ch);
bool queue_Peek_Offset(Queue_Typedef *queue,uint8_t *ch,uint16_t offset);
bool queue_PeekPopLength(Queue_Typedef *queue,uint8_t *buffer,uint16_t length);
bool queue_PeekLength(Queue_Typedef *queue,uint8_t *buffer,uint16_t length);
bool queue_PeekAll(Queue_Typedef *queue,uint8_t *buffer);
bool queue_Pop(Queue_Typedef *queue);
bool queue_PopLength(Queue_Typedef *queue,uint16_t length);
void queue_PopAll(Queue_Typedef *queue);



#endif

