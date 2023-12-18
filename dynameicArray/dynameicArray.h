#ifndef __DYNAMEIC_ARRAY_H_
#define __DYNAMEIC_ARRAY_H_

typedef int ELEMENTTYPE;
/* 避免头文件重复包含*/
typedef struct dynameicArray
{
    ELEMENTTYPE *data;    /* 数组的空间*/
    int len;     /* 数组的大小*/
    int capacity;/* 数组的容量*/

}dynameicArray;

#endif