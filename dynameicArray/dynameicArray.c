#include "dynameicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 状态码*/
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
};

#define DEFAULT_SIZE 10
/* 动态数组的初始化*/
int dynameicArrayInit(dynameicArray *pArray,int capacity)
{
    if(pArray == NULL)
    {
        return NULL_PTR;
    }

    if(capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if(pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);

    pArray->len = 0;
    pArray->capacity = capacity;
    return ON_SUCCESS;
}

/* 动态数组插入数据(默认插到数组的末尾)*/
int dynameicArrayInsertData(dynameicArray *pArray, ELEMENTTYPE val);

/* 动态数组插入数据，在指定位置插入*/
int dynameicArrayAppointPosInserData(dynameicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组修改指定位置数据*/
int dynameicArrayModifyAppointPosData(dynameicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组删除数据(默认删除数组末尾)*/
int dynameicArrayDeleteData(dynameicArray *pArray);

/* 动态数组删除数据，删除指定位置数据*/
int dynameicArrayDeleteAppointPosData(dynameicArray *pArray, int pos);

/* 动态数组删除指定的元素*/
int dynameicArrayDeleteAppointData(dynameicArray *pArray, ELEMENTTYPE val);

/* 动态数组销毁*/
int dynameicArrayDestroy(dynameicArray *pArray);

/* 获取动态数组的大小*/
int dynameicArrayGetSize(dynameicArray *pArray, int *pSize);

/* 获取动态数组的容量*/
int dynameicArrayGetCapacity(dynameicArray *pArray, int *pCapacity);