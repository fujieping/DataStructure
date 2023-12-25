#ifndef __DYNAMIC_ARRAY_STACK_H_
#define __DYNAMIC_ARRAY_STACK_H_

#include "dynameicArray.h"

/* 取别名*/
typedef dynameicArray dynameicArrayStack;

/* 初始化*/
int dynameicArrayStackInit(dynameicArrayStack *pStack);

/* 压栈*/
int dynameicArrayStackPush(dynameicArrayStack *pStack, ELEMENTTYPE val);

/* 查看栈顶元素*/
int dynameicArrayStackTop(dynameicArrayStack *pStack, ELEMENTTYPE *pVal);

/* 出栈*/
int dynameicArrayStackPop(dynameicArrayStack *pStack);

/* 栈是否为空*/
int dynameicArrayStackEmpty(dynameicArrayStack *pStack);

/* 获得栈的大小*/
int dynameicArrayStackGetSize(dynameicArrayStack *pStack, int *pSize);

/* 栈的销毁*/
int dynameicArrayStackDestroy(dynameicArrayStack *pStack);

#endif