#include <stdlib.h>
#include <string.h>
#include "LinkList.h"


enum STATUS_CODEH
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 静态函数，静态前置声明*/
static int LinkListAccrdAppointValGetPos(LinkList * pList, ELEMENTTYPE val, int *pPos);

/* 链表初始化*/
int LinkListInit(LinkList ** pList)
{
    int ret = 0;
    LinkList * list =(LinkList *)malloc(sizeof(LinkList)*1);
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(LinkList) * 1);

    list->head = (LinkNode *)malloc(sizeof(LinkList)*1);
    if(list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(LinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;

    /* 尾指针初始化*/
    list->tail = list->head;

    /* 链表的长度为0*/
    list->len = 0;

    *pList = list;

    return ret;
}

/* 链表头插*/
int LinkListHeadInsert(LinkList * pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插*/
int LinkListTailInsert(LinkList * pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList , pList->len, val);
}

/* 链表指定位置插入*/
int LinkListAppointPosInsert(LinkList * pList, int pos, ELEMENTTYPE val)
{
    int ret = 0; 
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 封装结点*/
    LinkNode * newNode = (LinkNode *)malloc(sizeof(LinkNode)*1);
    if(newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(LinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;

    /* 赋值*/
    newNode->data = val;
#if 1
    /* 从头节点开始遍历*/
    LinkNode * travelNode = pList->head;
#else
    LinkNode * travelNode = pList->head->next;
#endif
    int flag = 0;
    /* 这种情况下需要标记尾指针*/
    if(pos == pList->len)
    {
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
    }
    
    /* 修改结点指向*/
    newNode->next = travelNode->next;
    travelNode->next = newNode;
    if(flag)
    {
        /* 尾指针更新位置*/
        pList->tail = newNode;
    }

    /* 更新链表长度*/
    (pList->len)++;
    return ret;

}

/* 头删*/
int LinkListHeadDel(LinkList * pList)
{
    return LinkListDelAppointPos(pList, 1);
}

/* 伪善*/
int LinkListTailDel(LinkList * pList)
{
    return LinkListDelAppointPos(pList, pList->len);
}

/* 指定位置删*/
int LinkListDelAppointPos(LinkList * pList, int pos)
{
    int ret = 0; 
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    LinkNode * travelNode = pList->head;
#else
#endif
    while(--pos)
    {
        /* 向后移动位置*/
        travelNode = travelNode->next;
        //pos--;
    }

    /* 跳出循环找到一个结点*/
    LinkNode * needDelNode = travelNode->next;
    travelNode->next = needDelNode->next;

    /* 释放内存*/
    if(needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    /* 链表长度减短*/
    pList->len--;
    return ret;
}

/* 根据指定的元素得到在链表中的位置*/
static int LinkListAccrdAppointValGetPos(LinkList * pList, ELEMENTTYPE val, int *pPos)
{
    /* 静态函数只给本原文件的函数使用，不需要判断合法性*/
    int ret;
#if 0
    LinkNode * travelNode = pList->head;
#else
    int pos = 1;
    LinkNode * travelNode = pList->head->next;
#endif
    
    while(travelNode != NULL)
    {
        if(travelNode->data == val)
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
int LinkListDelAppointData(LinkList * pList, ELEMENTTYPE val)
{
    int ret = 0;
    /* 在链表中的位置*/
    int pos = 0;
    /* 链表长度*/
    int size = 0;
    while(LinkListDetLen(pList,&size) && pos != NOT_FIND)
    {
        LinkListAccrdAppointValGetPos(pList, val, &pos);
        LinkListDelAppointPos(pList, pos);
    }
    
    return ret;
}

/* 获取链表的长度*/
int LinkListDetLen(LinkList * pList, int *pSize)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }
    /* 返回链表的长度*/
    return pList->len;
}

/* 链表的销毁*/
int LinkListDestroy(LinkList * pList)
{
    /* 我们使用头删删除释放链表*/
    int size = 0;
    while(LinkListDetLen(pList, &size))
    {
        LinkListHeadDel(pList);
    }

    if(pList->head != NULL)
    {
        free(pList->head);
        pList->head = NULL;
        pList->tail = NULL;
    }
}

/* 链表遍历接口*/
int LinkListForeach(LinkList * pList)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
 #if 0
    /* travelNode指向虚拟头节点*/
    LinkNode * travelNode = pList->head;
    while(travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        printf("travelNode->data:%d\n", travelNode->data);
    }
#else
    LinkNode * travelNode = pList->head->next;
    while(travelNode != NULL)
    {
        printf("travelNode->data:%d\n", travelNode->data);
        travelNode = travelNode->next;
    }
#endif
    
    return ret;
}