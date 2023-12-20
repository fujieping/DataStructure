#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#define ELEMENTTYPE int

/* 链表结点取别名*/
typedef struct LinkNode
{
    ELEMENTTYPE data;
    /* 指向下一个节点的指针*/
    struct LinkNode *next;/* 指针类型*/
}LinkNode;

/* 链表*/
typedef struct LinkList
{
    LinkNode * head;/* 链表的虚拟头结点*/
    LinkNode * tail;/* 尾指针不需要分配空间*/
    int len;/* 链表长度*/
}LinkList;

/* 链表初始化*/
int LinkListInit(LinkList ** pList);

/* 链表头插*/
int LinkListHeadInsert(LinkList * pList, ELEMENTTYPE val);

/* 链表尾插*/
int LinkListTailInsert(LinkList * pList, ELEMENTTYPE val);

/* 链表指定位置插入*/
int LinkListAppointPosInsert(LinkList * pList, int pos, ELEMENTTYPE val);

/* 头删*/
int LinkListHeadDel(LinkList * pList);

/* 伪善*/
int LinkListTailDel(LinkList * pList);

/* 指定位置删*/
int LinkListDelAppointPos(LinkList * pList, int pos);

/* 删除链表的指定元素*/
int LinkListDelAppointData(LinkList * pList, ELEMENTTYPE val);

/* 获取链表的长度*/
int LinkListDetLen(LinkList * pList, int *pSize);

/* 链表的销毁*/
int LinkListDestroy(LinkList * pList);

/* 链表遍历接口*/
int LinkListForeach();

#endif