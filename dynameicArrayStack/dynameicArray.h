#ifndef __DYNAMEICARRAY_H_
#define __DYNAMEICARRAY_H_

#if 1
#define ELEMENTTYPE void*
#else
typedef int ELEMENTTYPE;
#endif
typedef struct DynamicArray
{
    ELEMENTTYPE *data;
    int len;
    int capacity;   /* 容量 */
} DynamicArray;


/* 状态码 */
enum STATUSCODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERR,
    INVAILD_ACCESS,
};


/* 动态数组初始化 */
int dynamicArrayInit(DynamicArray *pArray);

/* 动态数组插入 (默认插入到最后位置) */
int dynamicArrayInsert(DynamicArray *pArray, ELEMENTTYPE val);

/* 动态数组插入 在指定位置插入数据 */
int dynamicArrayAppointPosInsert(DynamicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组删除 在指定位置删除数据 */
int dynamicArrayDelAppointPos(DynamicArray *pArray, int pos);

/* 动态数组销毁 */
int dynamicArrayDestory(DynamicArray *pArray);

/* 动态数组获取指定位置的数据 */
int dynamicArrayGetAppointPosVal(DynamicArray *pArray, int pos, ELEMENTTYPE *pVal);

/* 获取动态数组的大小和容量 */
int dynamicArrayGetInfo(DynamicArray *pArray, int *pCap, int * pSize);

/* 获取动态数组的容量 */
int dynamicArrayGetCapacity(DynamicArray *pArray, int *pCap);

/* 获取动态数组的大小 */
int dynamicArrayGetSize(DynamicArray *pArray, int * pSize);

/* 修改动态数组指定位置的值 */
int dynamicArrayModifyAppointPosVal(DynamicArray *pArray, int pos, ELEMENTTYPE val);

#endif // __DYNAMICARRAY_H_