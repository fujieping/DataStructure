#include "doubleLinkListQueue.h"
#include "doubleLinkList.h"

/* 双向链表队列 初始化 */
int doublelinklistQueueInit(doubleLinkListQueue ** pQueue)
{
    int ret = 0;
    doubleLinkListInit(pQueue);
    return ret;
}

/* 双向链表队列 入队 */
int doublelinklistQueuePush(doubleLinkListQueue * pQueue, ELEMENTTYPE val)
{
    return doubleLinkListTailInsert(pQueue, val);
}

/* 双向链表队列 出队 */
int doublelinklistQueuePop(doubleLinkListQueue * pQueue)
{
    return doubleLinkListHeadDel(pQueue);
}

/* 双向链表队列 队头元素 */
int doublelinklistQueueTop(doubleLinkListQueue * pQueue, ELEMENTTYPE *pVal)
{
    return doubleLinkListGetHeadVal(pQueue, pVal);
}

/* 双向链表队列 队尾元素 */
int doublelinklistQueueRear(doubleLinkListQueue * pQueue, ELEMENTTYPE *pVal)
{
    return doubleLinkListGetTailVal(pQueue, pVal);
}

/* 双向链表队列 大小 */
int doublelinklistQueueSize(doubleLinkListQueue * pQueue, int *pSize)
{
    doubleLinkListGetLength(pQueue, pSize);
    return *pSize;
}

/* 双向链表队列 销毁 */
int doublelinklistQueueDestory(doubleLinkListQueue * pQueue)
{
    int ret = 0;
    doubleLinkListDestory(pQueue);
    return ret;
}