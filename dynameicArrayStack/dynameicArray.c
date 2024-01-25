#include "dynameicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_CAPACITY    10

#define CHECK_PTR(ptr)      \
    do                      \
    {                       \
        if (ptr == NULL)    \
        {                   \
            exit(0);        \
        }                   \
    }while(0);

/* 函数前置声明 */
/* 扩容 */
static int expandArrayCapacity(DynamicArray *pArray);
/* 缩容 */
static int reduceArrayCapacity(DynamicArray *pArray);

/* 动态数组初始化 */
int dynamicArrayInit(DynamicArray *pArray)
{
    int ret = 0;
    if (pArray == NULL)
    {
        return ret;
    }
    /* 分配空间 */
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * DEFAULT_CAPACITY);
    if (!(pArray->data))
    {
        return -1;
    }
    /* 清空脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * DEFAULT_CAPACITY);
    /* initialization */
    pArray->len = 0;
    pArray->capacity = DEFAULT_CAPACITY;
    return ret;
}

/* 扩容 */
static int expandArrayCapacity(DynamicArray *pArray)
{
    CHECK_PTR(pArray);
    int ret = 0;
    /* 需要扩展的新容量 */
    int expandNum = pArray->capacity + (pArray->capacity >> 1);
    ELEMENTTYPE * tmpArray = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * expandNum);
    if (!(pArray->data))
    {
        return -1;
    }
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * expandNum);

    /* 把之前的数据赋值到新的地址空间 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpArray[idx];
    }
    pArray->capacity = expandNum;

    /* 释放堆空间内存 */
    if (tmpArray)
    {
        free(tmpArray);
        tmpArray = NULL;
    }

    return ret;
}

/* 缩容 */
static int reduceArrayCapacity(DynamicArray *pArray)
{
    CHECK_PTR(pArray);
    int ret = 0;

    int needReduceNum = pArray->capacity >> 1;
    ELEMENTTYPE * tmpArray = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needReduceNum);
    if (!(pArray->data))
    {
        return -1;
    }
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * needReduceNum);

    for(int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpArray[idx];
    }

    if (tmpArray)
    {   
        free(tmpArray);
        tmpArray = NULL;
    }
    /* 更新动态数组capacity的大小 */
    pArray->capacity = needReduceNum;
    return ret;
}


/* 动态数组插入 (默认插入到最后位置) */
int dynamicArrayInsert(DynamicArray *pArray, ELEMENTTYPE val)
{
    return dynamicArrayAppointPosInsert(pArray, pArray->len, val);
}

/* 动态数组插入 在指定位置插入数据 */
int dynamicArrayAppointPosInsert(DynamicArray *pArray, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    CHECK_PTR(pArray);

    if (pos < 0 || pos > pArray->len)
    {
        return INVAILD_ACCESS;
    }
    /* 扩容 */
    if (pArray->len >= (pArray->capacity >> 1))
    {
        expandArrayCapacity(pArray);
    }

    /* 将pos后面的位置 进行后移 腾出pos位置给当前原元素使用 */
    for (int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx + 1] = pArray->data[idx];
    }
    pArray->data[pos] = val;

    pArray->len++;
    return ret;
}

/* 动态数组删除 在指定位置删除数据 */
int dynamicArrayDelAppointPos(DynamicArray *pArray, int pos)
{
    int ret = 0;
    CHECK_PTR(pArray);

    /* 判断pos的位置 : 删除失败 */
    if (pos < 0 || pos > pArray->len)
    {
        return INVAILD_ACCESS;
    }
    
    /* 缩容 */
    if(pArray->len <= pArray->capacity >> 1)
    {
        reduceArrayCapacity(pArray);
    }

    /* 将pos位置后的数据前移 */
    for(int idx = pos; idx <= pArray->len; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }

    pArray->len--;
    return ret;
}

/* 动态数组销毁 */
int dynamicArrayDestory(DynamicArray *pArray)
{
    int ret = 0;
    if (pArray->data)
    {
        free(pArray->data);
        pArray->data = NULL;
    }
    return ret;
}

/* 动态数组获取指定位置的数据 */
int dynamicArrayGetAppointPosVal(DynamicArray *pArray, int pos, ELEMENTTYPE *pVal)
{
    int ret = 0;
    CHECK_PTR(pArray);
    /* 判断位置是否合法 */
    if (pos < 0 || pos > pArray->len)
    {   
        return -1;
    }
    
    /* 判空 */
    if (pVal)
    {
        *pVal = pArray->data[pos];
    }
    return ret;
}

/* 获取动态数组的大小和容量 */
int dynamicArrayGetInfo(DynamicArray *pArray, int *pCap, int * pSize)
{
    int ret;
    CHECK_PTR(pArray);
    CHECK_PTR(pCap);
    CHECK_PTR(pSize);

    *pCap = pArray->capacity;
    *pSize = pArray->len;
    return ret;
}

/* 修改动态数组指定位置的值 */
int dynamicArrayModifyAppointPosVal(DynamicArray *pArray, int pos, ELEMENTTYPE val)
{
    int ret;
    CHECK_PTR(pArray);
    if (pos < 0 || pos > pArray->len - 1)
    {
        return INVAILD_ACCESS;
    }
    pArray->data[pos] = val;
    return ret;
}

/* 获取动态数组的容量 */
int dynamicArrayGetCapacity(DynamicArray *pArray, int *pCap)
{
    int ret;
    CHECK_PTR(pArray);
    CHECK_PTR(pCap);

    *pCap = pArray->capacity;
    return ret;
}

/* 获取动态数组的大小 */
int dynamicArrayGetSize(DynamicArray *pArray, int * pSize)
{
    int ret;
    CHECK_PTR(pArray);
    CHECK_PTR(pSize);

    *pSize = pArray->len;
    return ret;
}