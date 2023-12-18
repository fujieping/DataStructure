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
    INVALID_ACCESS,
};

#define DEFAULT_SIZE 10

/* 静态函数前置声明*/
static int expandDynameicCapacity(dynameicArray *pArray);
static int shrinkDynameicCapacity(dynameicArray *pArray);

/* 动态数组的初始化*/
int dynameicArrayInit(dynameicArray *pArray, int capacity)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    /* 避免传入非法值*/
    if (capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }
    /* 分配空间*/
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据*/
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);

    /* 初始化动态数组的参数属性*/
    pArray->len = 0;
    pArray->capacity = capacity;
    return ON_SUCCESS;
}

/* 动态数组插入数据(默认插到数组的末尾)*/
int dynameicArrayInsertData(dynameicArray *pArray, ELEMENTTYPE val)
{
    dynameicArrayAppointPosInserData(pArray, pArray->len, val);
}

/* 动态数组扩容*/
static int expandDynameicCapacity(dynameicArray *pArray)
{
    int needexpandCapacity = pArray->capacity + (pArray->capacity >> 1);
    /* 备份指针*/
    ELEMENTTYPE *tmpPtr = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needexpandCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    /* 把之前的数据全部拷贝过来*/
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }

    /* 释放之前的内存*/
    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }

    /* 更新动态数组容量*/
    pArray->capacity = needexpandCapacity;

    return ON_SUCCESS;
}

/* 动态数组插入数据，在指定位置插入*/
int dynameicArrayAppointPosInserData(dynameicArray *pArray, int pos, ELEMENTTYPE val)
{
    /* 指针判空*/
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性*/
    if (pos < 0 || pos > pArray->len)
    {
        return INVALID_ACCESS;
    }

    /* 扩容:数组扩容的临界值是:数组的大小的1.5倍 >= 数组容量*/
    if (pArray->len + (pArray->len >> 1) >= pArray->capacity)
    {
        /* 开始扩容*/
        expandDynameicCapacity(pArray);
    }

    /* 数据后移，留出pos位置*/
    for (int idx = pArray->len; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }

    /* 找到对应的位置填入值*/
    pArray->data[pos] = val;

    /* 数组大小加一*/
    pArray->len++;
    return ON_SUCCESS;
}

/* 动态数组修改指定位置数据*/
int dynameicArrayModifyAppointPosData(dynameicArray *pArray, int pos, ELEMENTTYPE val)
{
    /* 指针判空*/
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性*/
    if (pos < 0 || pos >= pArray->len)
    {
        return INVALID_ACCESS;
    }

    /* 更新位置数据*/
    pArray->data[pos] = val;
}

/* 动态数组删除数据(默认删除数组末尾)*/
int dynameicArrayDeleteData(dynameicArray *pArray)
{
    dynameicArrayDeleteAppointPosData(pArray, pArray->len - 1);
}

static int shrinkDynameicCapacity(dynameicArray *pArray)
{
    /* 数组新容量*/
    int needshrinkDynameicCapacity = pArray->capacity - (pArray->capacity >> 1);
    /* 备份指针*/
    ELEMENTTYPE *tmpPtr = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needshrinkDynameicCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    /* 把之前的数据全部拷贝过来新的空间*/
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }

    /* 释放之前的内存*/
    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }

    /* 更新动态数组容量*/
    pArray->capacity = needshrinkDynameicCapacity;

    return ON_SUCCESS;
}

/* 动态数组删除数据，删除指定位置数据*/
int dynameicArrayDeleteAppointPosData(dynameicArray *pArray, int pos)
{
    /* 指针判空*/
    if (pArray = NULL)
    {
        return NULL_PTR;
    }
    /* 判断位置的合法性*/
    if (pos < 0 || pos >= pArray->len)
    {
        return INVALID_ACCESS;
    }

    /* 缩容:缩了一半*/
    if (pArray->capacity >> 1 > pArray->len)
    {
        shrinkDynameicCapacity(pArray);
    }

    /* 数据前移*/
    for (int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }
    /* 更新数组大小*/
    (pArray->len)--;
    return ON_SUCCESS;
}

/* 动态数组删除指定的元素*/
int dynameicArrayDeleteAppointData(dynameicArray *pArray, ELEMENTTYPE val)
{
    /* todo..*/
#if 0
    for (int idx = 0; idx < pArray->len; idx++)
    {
        if(val == pArray->data[idx])
        {
            dynameicArrayDeleteAppointPosData(pArray, idx);
            idx = 0;
        }
    }
#else
    for (int idx = pArray->len; idx >= 0; idx--)
    {
        if(val == pArray->data[idx])
        {
            dynameicArrayDeleteAppointPosData(pArray, idx);
        }
    }
#endif
    return ON_SUCCESS;
}

/* 动态数组销毁*/
int dynameicArrayDestroy(dynameicArray *pArray)
{
    /* todo..*/
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    if (pArray->data != NULL)
    {
        free(pArray->data);
        pArray->data = NULL;
    }
    return ON_SUCCESS;
}

/* 获取动态数组的大小*/
int dynameicArrayGetSize(dynameicArray *pArray, int *pSize)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 解引用*/
    if (pSize != NULL)
    {
        *pSize = pArray->len;
    }
    return ON_SUCCESS;
}

/* 获取动态数组的容量*/
int dynameicArrayGetCapacity(dynameicArray *pArray, int *pCapacity)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    if (pCapacity != NULL)
    {
        *pCapacity = pArray->capacity;
    }
    return ON_SUCCESS;
}

/* 获取指定位置的元素数据*/
int dynameicArrayDeleteAppointPosVal(dynameicArray *pArray, int pos, ELEMENTTYPE *pVal)
{
    if(pArray == NULL)
    {
        return NULL_PTR;
    }
    if(pos < 0 || pos >= pArray->len)
    {
        return INVALID_ACCESS;
    }

    if(pVal)
    {
        *pVal = pArray->data[pos];
    }
    return ON_SUCCESS;
}