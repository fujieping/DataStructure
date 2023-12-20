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
    LinkList * head;/* 链表的虚拟头结点*/

    int len;/* 链表长度*/
}LinkList;

/* 链表初始化*/
int LinkListInit(LinkList ** pList);

/* 链表头插*/
int LinkListHeadInsert(LinkList * plist, ELEMENTTYPE val);

/* 链表尾插*/
int LinkListTailInsert(LinkList * plist, ELEMENTTYPE val);

/* 链表指定位置插入*/
int LinkListAppointPosInsert(LinkList * plist, int pos, ELEMENTTYPE val);

/* 头删*/
int LinkListHeadDel(LinkList * plist);

/* 伪善*/
int LinkListTailDel(LinkList * plist);

/* 指定位置删*/
int LinkListDelAppointPos(LinkList * plist, int pos);

/* 删除链表的指定元素*/
int LinkListDelAppointData(LinkList * plist, ELEMENTTYPE val);

/* 获取链表的长度*/
int LinkListDetLen(LinkList * plist, int *pSize);

/* 链表的销毁*/
int LinkListDestroy(LinkList * plist);

/* 链表遍历接口*/
int LinkListForeach();

#endif