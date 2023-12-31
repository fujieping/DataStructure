#ifndef __DOUBLELinkList_H_
#define __DOUBLELinkList_H_

#define ELEMENTTYPE void*

/* 链表结点取别名*/
typedef struct DoubleLinkNode
{
    ELEMENTTYPE data;
    /* 指向前一个节点的指针*/
    struct DoubleLinkNode *prev;
    /* 指向下一个节点的指针*/
    struct DoubleLinkNode *next;/* 指针类型*/
}DoubleLinkNode;

/* 链表*/
typedef struct DoubleLinkList
{
    DoubleLinkNode * head;/* 链表的虚拟头结点*/
    DoubleLinkNode * tail;/* 尾指针不需要分配空间*/
    int len;/* 链表长度*/
}DoubleLinkList;

/* 链表初始化*/
int DoubleLinkListInit(DoubleLinkList ** pList);

/* 链表头插*/
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表尾插*/
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表指定位置插入*/
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList, int pos, ELEMENTTYPE val);

/* 头删*/
int DoubleLinkListHeadDel(DoubleLinkList * pList);

/* 伪善*/
int DoubleLinkListTailDel(DoubleLinkList * pList);

/* 指定位置删*/
int DoubleLinkListDelAppointPos(DoubleLinkList * pList, int pos);

/* 删除链表的指定元素*/
int DoubleLinkListDelAppointData(DoubleLinkList * pList, ELEMENTTYPE val, int(*Deletefunc)(ELEMENTTYPE vla1, ELEMENTTYPE val2));

/* 获取链表的长度*/
int DoubleLinkListDetLen(DoubleLinkList * pList, int *pSize);

/* 链表的销毁*/
int DoubleLinkListDestroy(DoubleLinkList * pList);

/* 链表遍历接口*/
int DoubleLinkListForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE));              

/* 双向链表的逆序*/
int DoubleLinkListReverseForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE));
#endif