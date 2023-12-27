#include <stdio.h>
#include "dynameicArray.h"
#include <string.h>

#define BUFFER_SIZE 20
#define DEFAULT_NUM 3

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo;

int main()
{
    dynameicArray array;
    /* 初始化*/
    dynameicArrayInit(&array, BUFFER_SIZE);
#if 1
    
        /* 插入数据*/
        int a = 3;
        dynameicArrayInsertData(&array, a);
        for(int idx = 0; idx < DEFAULT_NUM; idx++)
        {
            dynameicArrayInsertData(&array, idx);
        }

        /* 修改数据*/
        //dynameicArrayModifyAppointPosData(&array, 1, (void*)5);

        /* 删除指定位置数据 */
        //dynameicArrayDeleteAppointPosData(&array, 2);

        /* 删除指定元素数据*/
        int tmp = 0;
        //dynameicArrayDeleteAppointData(&array, tmp, c);

    {
        // int size = 0;
        // /* 获取动态数组大小*/
        // dynameicArrayGetSize(&array, &size);
        
    }

    {
        int size = 0;
        /* 获取动态数组大小*/
        dynameicArrayGetSize(&array, &size);
        printf("size:%d\n", size);

        int val = 0;
        for(int idx = 0; idx < size; idx++)
        {
            dynameicArrayDeleteAppointPosVal(&array, idx, &val);
            printf("array[%d]  val:%d\n", idx, val);
        }
    }

    
#elif 0
    int buffer[DEFAULT_NUM] = {1, 2, 3};
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynameicArrayInsertData(&array, (void*)&buffer[idx]);
    }

    int size = 0;
    dynameicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    int *val = NULL;
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynameicArrayDeleteAppointPosVal(&array, idx, (void*)&val);
        printf("val:%d\n", *val);
    }
    
#elif 1
    stuInfo stu1, stu2, stu3;
    memset(&stu1, 0, sizeof(stu1));
    memset(&stu2, 0, sizeof(stu2));
    memset(&stu3, 0, sizeof(stu3));

    stu1.age = 10;
    stu1.sex = 'm';

    stu2.age = 10;
    stu2.sex = 'f';

    stu3.age = 30;
    stu3.sex = 'm';

    stuInfo buffer[DEFAULT_NUM] = {stu1, stu2, stu3};
    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynameicArrayInsertData(&array, (void*)&buffer[idx]);
    }
    
    int size = 0;
    dynameicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    stuInfo *info = NULL;
    //memser(&info, 0, sizeof(info));
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynameicArrayDeleteAppointPosVal(&array, idx, (void*)&info);
        printf("info.age:%d\tinfo.sex:%c\n", info->age, info->sex);
    }

#else

#endif
    return 0;
}