#include "dynameicArrayStack.h"
#include <stdio.h>
#include "dynameicArray.h"
#define DEFAULT_SIZE 10

/* 初始化*/
int dynameicArrayStackInit(dynameicArrayStack *pStack)
{
    return dynameicArrayInit(pStack, DEFAULT_SIZE);
}

/* 压栈*/
int dynameicArrayStackPush(dynameicArrayStack *pStack, ELEMENTTYPE val)
{
    /* 调用动态数组的尾插*/
    return dynameicArrayInsertData(pStack, val);
}

/* 查看栈顶元素*/
int dynameicArrayStackTop(dynameicArrayStack *pStack, ELEMENTTYPE *pVal)
{
    /* 获取指定位置的元素*/
    return dynameicArrayDeleteAppointPosVal(pStack, pStack->len - 1, pVal);
}

/* 出栈*/
int dynameicArrayStackPop(dynameicArrayStack *pStack)
{
    return dynameicArrayDeleteData(pStack);
}

/* 栈是否为空*/
int dynameicArrayStackEmpty(dynameicArrayStack *pStack)
{
    int size = 0;
    dynameicArrayGetSize(pStack, &size);
    return size == 0 ? 1 : 0;
}

/* 获得栈的大小*/
int dynameicArrayStackGetSize(dynameicArrayStack *pStack, int *pSize)
{
#if 1
    return dynameicArrayGetSize(pStack, pSize);
#else
    dynameicArrayGetSize(pStack, pSize);
#endif
}

/* 栈的销毁*/
int dynameicArrayStackDestroy(dynameicArrayStack *pStack)
{
    return dynameicArrayDestroy(pStack);
}