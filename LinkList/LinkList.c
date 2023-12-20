#include "LinkList"
#include <stdlib.h>
#include <string.h>

enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 链表初始化*/
int LinkListInit(LinkList ** pList)
{
    int ret = 0;
    LinkList * list =(LinkList *)malloc(sizeof(LinkList)*1);
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0 sizeof(LinkList) * 1);

    list->head = (LinkNOde *)malloc(sizeof(LinkList)*1);
    if(list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(LinkNOde) * 1);
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
    memset(newNode, 0, sizeof(LinNode) * 1);
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

}

/* 伪善*/
int LinkListTailDel(LinkList * pList)
{

}

/* 指定位置删*/
int LinkListDelAppointPos(LinkList * pList, int pos)
{

}

/* 删除链表的指定元素*/
int LinkListDelAppointData(LinkList * pList, ELEMENTTYPE val)
{

}

/* 获取链表的长度*/
int LinkListDetLen(LinkList * pList, int *pSize)
{
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }
    return ret;
}

/* 链表的销毁*/
int LinkListDestroy(LinkList * pList)
{

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