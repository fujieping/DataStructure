#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"

#define BUFFER_SIZE 3
#define DEFAULT_NUM 3

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo;

int printStruct(void *arg)
{
   stuInfo *info = (stuInfo*)arg;
   printf("arg:%d\tsex:%c\n",info->age, info->sex);
}

int main()
{
    LinkList *list = NULL;
    /* 初始化链表*/
    LinkListInit(&list);
#if 0
    /* 插入数据*/
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListTailInsert(list, idx);
    }

    /* 获取链表长度*/
    int size = 0;
    LinkListDetLen(list, &size);
    printf("size:%d\n", size);

    /*  遍历指针*/
    LinkListForeach(list);

  
#endif
#if 1
stuInfo stu1, stu2, stu3;
    memset(&stu1, 0, sizeof(stu1));
    memset(&stu2, 0, sizeof(stu2));
    memset(&stu3, 0, sizeof(stu3));

    stu1.age = 10;
    stu1.sex = 'm';

    stu2.age = 20;
    stu2.sex = 'f';

    stu3.age = 30;
    stu3.sex = 'm';

    stuInfo buffer[DEFAULT_NUM] = {stu1, stu2, stu3};

    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListHeadInsert(list, (void*)&buffer[idx]);
    }

    /* 获取链表长度*/
    int size = 0;
    LinkListDetLen(list, &size);
    printf("size:%d\n", size);

    /*  遍历指针*/
    LinkListForeach(list, printStruct);
#endif
    return 0;
}