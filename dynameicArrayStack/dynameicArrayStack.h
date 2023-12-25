#ifndef __DYNAMIC_ARRAY_STACK_H_
#define __DYNAMIC_ARRAY_STACK_H_

/* 初始化*/
int dynameicArrayStackInit();

/* 压栈*/
int dynameicArrayStackPush();

/* 查看暂定元素*/
int dynameicArrayStackTop();

/* 出栈*/
int dynameicArrayStackPop();

/* 栈是否为空*/
int dynameicArrayStackEmpty();

/* 获得栈的大小*/
int dynameicArrayStackSize();

/* 栈的销毁*/
int dynameicArrayStackDestroy();

#endif