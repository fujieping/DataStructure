#ifndef __DOUBLE_LINKLIST_QUEUE_H_
#define __DOUBLE_LINKLIST_QUEUE_H_
#include "common.h"


typedef struct linkList doubleLinkListQueue;

/* 双向链表队列 初始化 */
int doublelinklistQueueInit(doubleLinkListQueue ** pQueue);

/* 双向链表队列 入队 */
int doublelinklistQueuePush(doubleLinkListQueue * pQueue, ELEMENTTYPE val);

/* 双向链表队列 出队 */
int doublelinklistQueuePop(doubleLinkListQueue * pQueue);

/* 双向链表队列 队头元素 */
int doublelinklistQueueTop(doubleLinkListQueue * pQueue, ELEMENTTYPE *pVal);

/* 双向链表队列 队尾元素 */
int doublelinklistQueueRear(doubleLinkListQueue * pQueue, ELEMENTTYPE *pVal);

/* 双向链表队列 大小 */
int doublelinklistQueueSize(doubleLinkListQueue * pQueue, int *pSize);

/* 双向链表队列 销毁 */
int doublelinklistQueueDestory(doubleLinkListQueue * pQueue);

#endif  // __DOUBLELINKLISTQUEUE_H_