#ifndef __DOUBLELINKLISTQUEUE_H_
#define __DOUBLELINKLISTQUEUE_H_

#include "doubleLinkList.h"

typedef DoubleLinkList DoubleLinkListQueue;

/* 队列的初始化*/
int doubleLinkListQueueInit(DoubleLinkListQueue **pQueue);

/* 入队*/
int doubleLinkListQueuePush(DoubleLinkListQueue *pQueue, ELEMENTTYPE val);

/* 队头元素*/
int doubleLinkListQueueTop(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal);

/* 队尾元素*/
int doubleLinkListQueueRear(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal);

/* 出队*/
int doubleLinkListQueuePop(DoubleLinkListQueue *pQueue);

/* 队列大小*/
int doubleLinkListQueueGetSize(DoubleLinkListQueue *pQueue, int *pSize);

/* 队列判空*/
int doubleLinkListQueueIsEmpty(DoubleLinkListQueue *pQueue);

/* 队列销毁*/
int doubleLinkListQueueDestroy(DoubleLinkListQueue *pQueue);


#endif