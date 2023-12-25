#ifndef __DYNAMEIC_ARRAY_H_
#define __DYNAMEIC_ARRAY_H_

#include "common.h"

/* API:application program interface.*/

/* 动态数组的初始化*/
int dynameicArrayInit(dynameicArray *pArray, int capacity);

/* 指针判空*/

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
int dynameicArrayDeleteAppointData(dynameicArray *pArray, ELEMENTTYPE val, int(*Deletefunc)(ELEMENTTYPE val1, ELEMENTTYPE val2));

/* 动态数组销毁*/
int dynameicArrayDestroy(dynameicArray *pArray);

/* 获取动态数组的大小*/
int dynameicArrayGetSize(dynameicArray *pArray, int *pSize);

/* 获取动态数组的容量*/
int dynameicArrayGetCapacity(dynameicArray *pArray, int *pCapacity);

/* 获取指定位置的元素数据*/
int dynameicArrayDeleteAppointPosVal(dynameicArray *pArray, int pos, ELEMENTTYPE *pVal);
#endif