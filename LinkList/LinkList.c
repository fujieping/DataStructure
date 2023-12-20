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
    LinkList *list =(LinkList *)malloc(sizeof(LinkList)*1);
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
    /* 链表的长度为0*/
    list->len = 0;

    *pList = list;

    return ret;
}

/* 链表头插*/
int LinkListHeadInsert(LinkList * plist, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插*/
int LinkListTailInsert(LinkList * plist, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList , pList->len, val);
}

/* 链表指定位置插入*/
int LinkListAppointPosInsert(LinkList * plist, int pos, ELEMENTTYPE val)
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
    while(pos)
    {
        travelNode = travelNode->next;
        pos--;
    }
    /* 修改结点指向*/
    newNode->next = travelNode->next;
    travelNode->next = newNode;

    /* 更新链表长度*/
    (pList->len)++;
    return ret;

}

/* 头删*/
int LinkListHeadDel(LinkList * plist)
{

}

/* 伪善*/
int LinkListTailDel(LinkList * plist)
{

}

/* 指定位置删*/
int LinkListDelAppointPos(LinkList * plist, int pos)
{

}

/* 删除链表的指定元素*/
int LinkListDelAppointData(LinkList * plist, ELEMENTTYPE val)
{

}

/* 获取链表的长度*/
int LinkListDetLen(LinkList * plist, int *pSize)
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
int LinkListDestroy(LinkList * plist)
{

}

/* 链表遍历接口*/
int LinkListForeach(LinkList * )
{

}