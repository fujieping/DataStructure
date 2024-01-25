#include "dynameicArray.h"
#include "dynameicArrayStack.h"

/* 栈的初始化 */
int arrayStackInit(ArrayStack * pStack)
{
    return dynamicArrayInit(pStack);
}

/* 栈的插入数据 */
int arrayStackPush(ArrayStack * pStack, ELEMENTTYPE val)
{
    return dynamicArrayInsert(pStack, val);
}

/* 栈的弹出数据 */
int arrayStackPop(ArrayStack * pStack)
{
    int ret = 0;

    int stackSize = 0;
    /* 获取栈的大小 */
    dynamicArrayGetSize(pStack, &stackSize);
    /* 删除末尾位置 */
    return dynamicArrayDelAppointPos(pStack, stackSize);
}

/* 查看栈顶数据 */
int arrayStackTop(ArrayStack * pStack, ELEMENTTYPE *pVal)
{
    int ret = 0;
    int stackSize = 0;
    /* 获取栈的大小 */
    dynamicArrayGetSize(pStack, &stackSize);
    /* 获取栈顶的数据 */
    dynamicArrayGetAppointPosVal(pStack, stackSize - 1, pVal);
    return ret;
}

/* 获取栈的大小 */
int arrayStackGetSize(ArrayStack * pStack, int *pSize)
{
    dynamicArrayGetSize(pStack, pSize);
    return *pSize;
}

/* 栈的销毁 */
int arrayStackDestory(ArrayStack * pStack)
{
    int ret = 0;
    return dynamicArrayDestory(pStack);
}