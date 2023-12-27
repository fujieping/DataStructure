
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doubleLinkList.h"
enum STATUS_CODEH
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 静态函数，静态前置声明*/
static int DoubleLinkListAccrdAppointValGetPos(DoubleLinkList *pList, ELEMENTTYPE val, int *pPos);
/* 封装新建新结点，封装成函数*/
static DoubleLinkNode *createDoubleLinkNode(ELEMENTTYPE val);

/* 链表初始化*/
int DoubleLinkListInit(DoubleLinkList **pList)
{
    int ret = 0;
    DoubleLinkList *list = (DoubleLinkList *)malloc(sizeof(DoubleLinkList) * 1);
    if (list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(DoubleLinkList) * 1);

    list->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(DoubleLinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;
    list->head->prev = NULL;

    /* 尾指针初始化*/
    list->tail = list->head;

    /* 链表的长度为0*/
    list->len = 0;

    *pList = list;

    return ret;
}

/* 链表头插*/
int DoubleLinkListHeadInsert(DoubleLinkList *pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插*/
int DoubleLinkListTailInsert(DoubleLinkList *pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, pList->len, val);
}

static DoubleLinkNode *createDoubleLinkNode(ELEMENTTYPE val)
{
    /* 封装结点*/
    DoubleLinkNode *newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (newNode == NULL)
    {
        return NULL;
    }
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;
    newNode->prev = NULL;

    /* 赋值*/
    newNode->data = val;

    /* 返回新建结点*/
    return newNode;
}
/* 链表指定位置插入*/
int DoubleLinkListAppointPosInsert(DoubleLinkList *pList, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    /* 封装新建新结点，封装成函数*/
    DoubleLinkNode *newNode = createDoubleLinkNode(val);
    if(newNode == NULL)
    {
        return NULL_PTR;
    }
#else
    /* 封装结点*/
    DoubleLinkNode *newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;

    /* 赋值*/
    newNode->data = val;
#endif
#if 1
    /* 从头节点开始遍历*/
    DoubleLinkNode *travelNode = pList->head;
#else
    DoubleLinkNode *travelNode = pList->head->next;
#endif
    int flag = 0;
    /* 这种情况下需要标记尾指针*/
    if (pos == pList->len)
    {
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while (pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        travelNode->next->prev = newNode;
    }

    /* 修改结点指向*/
    newNode->next = travelNode->next;
    newNode->prev = travelNode; 
    travelNode->next = newNode;
    if (flag)
    {
        /* 尾指针更新位置*/
        pList->tail = newNode;
    }

    /* 更新链表长度*/
    (pList->len)++;
    return ret;
}

/* 头删*/
int DoubleLinkListHeadDel(DoubleLinkList *pList)
{
    return DoubleLinkListDelAppointPos(pList, 1);
}

/* 尾删 */
int DoubleLinkListTailDel(DoubleLinkList *pList)
{
    return DoubleLinkListDelAppointPos(pList, pList->len);
}

/* 指定位置删*/
int DoubleLinkListDelAppointPos(DoubleLinkList *pList, int pos)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    DoubleLinkNode *travelNode = pList->head;
#else
#endif
    DoubleLinkNode *needDelNode = NULL;
    //int flag = 0;
    /* 需要修改尾指针*/
    if (pos == pList->len)
    {
        //flag = 1;

        DoubleLinkNode * tmpNode = pList->tail;
        pList->tail = pList->tail->prev;
        needDelNode = tmpNode;
    }
    else
    {
        while (--pos)
        {
            /* 向后移动位置*/
            travelNode = travelNode->next;
            // pos--;
        }
        /* 跳出循环找到一个结点*/
        needDelNode = travelNode->next;
        travelNode->next = needDelNode->next;
        needDelNode->next->prev = travelNode;
    }
    
    // if (flag)
    // {
    //     /* 调整尾指针*/
    //     pList->tail = travelNode;
    // }

    /* 释放内存*/
    if (needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    /* 链表长度减短*/
    pList->len--;
    return ret;
}

/* 根据指定的元素得到在链表中的位置*/
static int DoubleLinkListAccrdAppointValGetPos(DoubleLinkList *pList, ELEMENTTYPE val, int *pPos)
{
    /* 静态函数只给本原文件的函数使用，不需要判断合法性*/
    int ret;
#if 0
    DoubleLinkNode * travelNode = pList->head;
#else
    int pos = 1;
    DoubleLinkNode *travelNode = pList->head->next;
#endif

    while (travelNode != NULL)
    {
        if (travelNode->data == val)
        {
            /* 解引用*/
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }
    *pPos = NOT_FIND;
    return NOT_FIND;
}
/* 删除链表的指定元素*/
int DoubleLinkListDelAppointData(DoubleLinkList *pList, ELEMENTTYPE val, int (*Deletefunc)(ELEMENTTYPE vla1, ELEMENTTYPE val2))
{
    int ret = 0;
#if 0
    /* 在链表中的位置*/
    int pos = 0;
    /* 链表长度*/
    int size = 0;
    while (DoubleLinkListDetLen(pList, &size) && pos != NOT_FIND)
    {
        DoubleLinkListAccrdAppointValGetPos(pList, val, &pos);
        DoubleLinkListDelAppointPos(pList, pos);
    }
#endif
    int pos = 1;
    DoubleLinkNode *travelNode = pList->head->next;
    while (travelNode != NULL)
    {
        ret = Deletefunc(val, travelNode->data);
        travelNode = travelNode->next;
        if (ret == 1)
        {
            DoubleLinkListDelAppointPos(pList, pos);
            ret = 0;
            pos--;
        }

        pos++;
    }

    return ON_SUCCESS;
}

/* 获取链表的长度*/
int DoubleLinkListDetLen(DoubleLinkList *pList, int *pSize)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pSize)
    {
        *pSize = pList->len;
    }
    /* 返回链表的长度*/
    return pList->len;
}

/* 链表的销毁*/
int DoubleLinkListDestroy(DoubleLinkList *pList)
{
    /* 我们使用头删删除释放链表*/
    int size = 0;
    while (DoubleLinkListDetLen(pList, &size))
    {
        DoubleLinkListHeadDel(pList);
    }

    if (pList->head != NULL)
    {
        free(pList->head);
        pList->head = NULL;
        pList->tail = NULL;
    }
}

/* 链表遍历接口*/
int DoubleLinkListForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }
#if 0
    /* travelNode指向虚拟头节点*/
    DoubleLinkNode * travelNode = pList->head;
    while(travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        printf("travelNode->data:%d\n", travelNode->data);
    }
#else
    DoubleLinkNode *travelNode = pList->head->next;
    while (travelNode != NULL)
    {
#if 0
        printf("travelNode->data:%d\n", travelNode->data);
#else
        /* 包装器，钩子，回调函数*/
        printFunc(travelNode->data);
#endif
        travelNode = travelNode->next;
    }
#endif

    return ret;
}

/* 双向链表的逆序*/
int DoubleLinkListReverseForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    DoubleLinkNode *travelNode = pList->tail;
    while (travelNode != pList->head)
    {
        printFunc(travelNode->data);
        travelNode = travelNode->prev;
    }

    return ret;
    
}

/* 获取链表首位置的值*/
int DoubleLinkListHeadVal(DoubleLinkList *pList, ELEMENTTYPE *pVal)
{
    #if 1
    return DoubleLinkListGetAppointPosVal(pList, 1, pVal);
    #else
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    if(pVal)
    *pVal = pList->head->next->data;
    return ret;
    #endif
}

/* 获取链表尾位置的值*/
int DoubleLinkListTailVal(DoubleLinkList *pList, ELEMENTTYPE *pVal)
{
    return DoubleLinkListGetAppointPosVal(pList, pList->len - 1, pVal);
}

/* 获取链表指定位置的值*/
int DoubleLinkListGetAppointPosVal(DoubleLinkList *pList, int pos, ELEMENTTYPE *pVal)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    DoubleLinkNode * travelNode = pList->head->next;

    while(--pos)
    {
        travelNode = travelNode->next;
    }
    *pVal = travelNode->data;

    return ret;
}