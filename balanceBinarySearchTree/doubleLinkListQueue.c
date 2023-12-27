#include "doubleLinkListQueue.h"
#include "doubleLinkList.h"


/* 队列的初始化*/
int doubleLinkListQueueInit(DoubleLinkListQueue **pQueue)
{
    return DoubleLinkListInit(pQueue);
}

/* 入队*/
int doubleLinkListQueuePush(DoubleLinkListQueue *pQueue, ELEMENTTYPE val)
{
    return DoubleLinkListTailInsert(pQueue, val);
}

/* 获取队头元素*/
int doubleLinkListQueueTop(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal)
{
    return DoubleLinkListHeadVal(pQueue, pVal);
}

/* 队尾元素*/
int doubleLinkListQueueRear(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal)
{
    return DoubleLinkListTailVal(pQueue, pVal);
}

/* 出队*/
int doubleLinkListQueuePop(DoubleLinkListQueue *pQueue)
{
    return DoubleLinkListHeadDel(pQueue);
}

/* 队列大小*/
int doubleLinkListQueueGetSize(DoubleLinkListQueue *pQueue, int *pSize)
{
    return DoubleLinkListDetLen(pQueue, pSize);
}

/* 队列判空*/
int doubleLinkListQueueIsEmpty(DoubleLinkListQueue *pQueue)
{
    int size = 0;
    DoubleLinkListDetLen(pQueue, &size);
    return size == 0 ? 1:0;
}

/* 队列销毁*/
int doubleLinkListQueueDestroy(DoubleLinkListQueue *pQueue)
{
    return DoubleLinkListDestroy(pQueue);
}