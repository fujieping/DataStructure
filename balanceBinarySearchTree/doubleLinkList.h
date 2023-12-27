#ifndef __DOUBLELINKLIST_H_
#define __DOUBLELINKLIST_H_

#include "common.h"

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

/* 获取链表指定位置的值*/
int DoubleLinkListHeadVal(DoubleLinkList *pList, ELEMENTTYPE *pVal);

/* 获取链表指定位置的值*/
int DoubleLinkListTailVal(DoubleLinkList *pList, ELEMENTTYPE *pVal);

/* 获取链表指定位置的值*/
int DoubleLinkListGetAppointPosVal(DoubleLinkList *pList, int pos, ELEMENTTYPE *pVal);

#endif