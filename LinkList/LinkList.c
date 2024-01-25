#include "LinkList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* 链表的初始化 */
int linkListInit(linkList **pList)
{
    int ret = 0;
    linkList *plist = (linkList *)malloc(sizeof(linkList) * 1);    
    if (!plist)
    {
        return -1;
    }
    /* 清空内存中的脏数据 */
    memset(plist, 0, sizeof(linkList) * 1);
    
    plist->head = (Node *)malloc(sizeof(Node) * 1);
    if (!(plist->head))
    {
        return -1;
    }
    /* 清空内存中的脏数据 */
    memset(plist->head, 0, sizeof(Node) * 1);
    /* 初始化链表 */
    plist->len = 0;
    /* 初始化虚拟结点*/
    plist->head->val = 0;
    plist->head->next = NULL;

    *pList = plist;
    return ret;
}

/* 头插 */
int linkListHeadInsert(linkList *pList, ELEMENTTYPE val)
{
    return linkListAppointPosInsert(pList, 0, val);
}

/* 尾插 */
int linkListTailInsert(linkList *pList, ELEMENTTYPE val)
{
    int pos = pList->len;
    return linkListAppointPosInsert(pList, pos, val);
}

/* 指定位置插 */
int linkListAppointPosInsert(linkList *pList, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    if (!pList)
    {
        return NULL_PTR;
    }
    Node *newnode = (Node *)malloc(sizeof(Node) * 1);
    if (!newnode)
    {
        return MALLOC_ERR;
    }
    memset(newnode, 0, sizeof(Node));
    /* 维护新的节点 */
    newnode->val = val;
    newnode->next = NULL;

    /* 判断位置是否合法 */
    if (pos < 0 || pos > pList->len)
    {
        return INVAILD_ACCESS;
    }

    Node * travelNode = pList->head;
    while (pos)
    {
        pos--;
        travelNode = travelNode->next;
    }
    newnode->next = travelNode->next;
    travelNode->next = newnode;
    /* 更新长度 */
    (pList->len)++;
    return ret;
}

/* 获取链表的数据 */
int linkListGetLength(linkList *pList, int *pLen)
{
    int ret;
    if (!pList || !pLen)
    {
        return -1;
    }
    /* 解引用 */
    *pLen = pList->len;
    return ret;
}

/* 遍历链表 */
int linkListForeach(linkList *pList, void (*printFunc)(void *arg))
{
    int ret = 0;
    if (!pList)
    {
        return -1;
    }

    Node *travelNode = pList->head->next;
    while(travelNode != NULL)
    {
        #if 0
        printf("%d\t->", travelNode->val);
        #else
        printFunc(travelNode->val);
        #endif
        travelNode = travelNode->next;
    }
    printf("\n");
    return ret;
}

/* 头删 */
int linkListHeadDel(linkList *pList)
{
    int ret;
    ret = linkListAppointPosDel(pList, 1);
    return ret;
}

/* 尾删 */
int linkListTailDel(linkList *pList)
{
    int ret;
    int pos = pList->len;
    ret = linkListAppointPosDel(pList, pos);
    return ret;
}

/* 按指定位置删除 */
int linkListAppointPosDel(linkList *pList, int pos)
{
    int ret;
    if (!pList)
    {
        return NULL_PTR;
    }
    if (pos < 0 || pos > pList->len)
    {
        return INVAILD_ACCESS;
    }   

#if 0
    /* 双指针 */
    Node * travelNode = pList->head->next;
    Node * prevNode = pList->head;
    while (--pos)
    {
        prevNode =  travelNode;
        travelNode = travelNode->next;
    }
    /* 更换结点指针 */
    prevNode->next = travelNode->next;
#else
    Node * travelNode = pList->head;
    /* 此循环是找到删除结点的前一个结点 */
    while (--pos)
    {
        travelNode = travelNode->next;
    }
    Node * delNode = travelNode->next;
    travelNode->next = delNode->next;
#endif
    free(delNode);
    delNode = NULL;

    /* 数据结点减一 */
    pList->len--;

    return ret;
}

/* 链表销毁 */
int linkListDestroy(linkList *pList)
{
    int ret = 0;
    
    int length = pList->len;
    for (int idx = 0; idx < length; idx++)
    {
        linkListHeadDel(pList);
    }

    /* 释放虚拟头结点 */
    if (pList->head)
    {
        free(pList->head);
        pList->head = NULL;
    }

    if (pList)
    {
        free(pList);
        pList = NULL;
    }
    return ret;
}

/* 链表删除指定数据 */
int linkListAppointValDel(linkList *pList, ELEMENTTYPE val)
{
    int ret = 0;

    return ret;
}