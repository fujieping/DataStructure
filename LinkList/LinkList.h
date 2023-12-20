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
int LinkListInit();

/* 链表头插*/
int LinkListHeadInsert();

/* 链表尾插*/
int LinkListTailInsert();

/* 链表指定位置插入*/
int LinkListAppointPosInsert();

/* 头删*/
int LinkListHeadDel();

/* 伪善*/
int LinkListTailDel();

/* 指定位置删*/
int LinkListDelAppointPos();

/* 删除链表的指定元素*/
int LinkListDelAppointData();

/* 获取链表的长度*/
int LinkListDetLen();

/* 链表的销毁*/
int LinkListDestroy();

#endif