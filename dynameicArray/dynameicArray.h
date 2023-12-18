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

/* API:application program interface.*/

/* 动态数组的初始化*/
int dynameicArrayInit();

/* 动态数组插入数据(默认插到数组的末尾)*/
int dynameicArrayInsertData();

/* 动态数组插入数据，在指定位置插入*/
int dynameicArrayAppointPosInserData();

/* 动态数组修改指定位置数据*/
int dynameicArrayModifyAppointPosData();

/* 动态数组删除数据(默认删除数组末尾)*/
int dynameicArrayDeleteData();

/* 动态数组删除数据，删除指定数据*/
int dynameicArrayDeleteAppointPosData();

/* 动态数组销毁*/
int dynameicArrayDestroy();

/* 获取动态数组的大小*/
int dynameicArrayGetSize();

/* 获取动态数组的容量*/
int dynameicArrayGetCapacity();
#endif