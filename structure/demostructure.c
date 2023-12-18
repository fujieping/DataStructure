#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 16
#define DEF_SIZE 2

#if 1 /* 结构体*/
/* 1,什么是结构体:
   2,怎么定义结构体:
   3，什么叫变长结构体：
*/
struct stuInfo//名字过长用typedef取别名
{
    int age;
    int height;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
    char *address;
};
typedef struct stuInfo stuInfo;
#endif
/* 4,结构体的大小:结构体会进行字节对齐，读取速度快（但是浪费空间）*/
/* 函数:结构体做函数，必须用地址传递*/
void printStruct(const stuInfo *stu)/* 传入参数:不要改变值*/
{
    /* 栈空间很小，不允许超过8MB。*/
    int ret = 0;
    int len = sizeof(stu);
    printf("len:%d\n", len);
    return;
}

int printStructBuffer(stuInfo * stu, int stuSize)
{
    for(int idx = 0; idx < stuSize; idx++)
    {
        printf("age:%d\t,height:%d\t,weight:%d\t,sex:%c\t,name:%s\n", 
        stu[idx].age, stu[idx].height, stu[idx].weight, stu[idx].sex, stu[idx].name);
    }
    return 0;
}
int main()
{
#if 0 /* 5,结构体的使用*/
    stuInfo stu;
    memset(&stu, 0, sizeof(stu));
    stu.age = 10;
    stu.height = 50;
    stu.sex = 'm';
    stu.weight = 170;
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);
    printf("age:%d\t,height:%d\t,weight:%d\t,sex:%c\t,name:%s\n", stu.age, stu.height, stu.weight, stu.sex, stu.name);

#endif

#if 0 /* 6,结构体数组,名字过长用typedef取别名 */
    stuInfo buffer[DEF_SIZE];
    buffer[0].age = 10;
    buffer[0].weight = 50;
    buffer[0].sex = 'm';
    buffer[0].height = 150;
    strncpy(buffer[0].name, "zhangsan", sizeof(buffer[0].name) - 1);

    buffer[1].age = 20;
    buffer[1].weight = 52;
    buffer[1].sex = 'f';
    buffer[1].height = 180;
    strncpy(buffer[1].name, "wangwu", sizeof(buffer[1].name) - 1);

    printStructBuffer(buffer, sizeof(buffer));
#endif

#if 0/* 7,结构体指针*/
    stuInfo stu;
    stu.age = 10;
    stu.height = 50;
    stu.sex = 'm';
    stu.weight = 170;
    strncpy(stu.name, "zhangsan", sizeof(stu.name));

    stuInfo * info = &stu;/* 结构体指针*/
    info->age = 30;
    //printStruct(&stu);
    // printf("info->age:%d\n", info->age);
    // printf("stu.age:%d\n", stu.age);
    printStructBuffer(&stu, sizeof(stu));
#endif

#if 1/* 结构体里面有指针必须分配空间malloc，*/
    stuInfo stu;
    memset(&stu, 0, sizeof(stu));
    stu.age = 10;
    stu.height = 50;
    stu.sex = 'm';
    stu.weight = 170;
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);
    stu.address = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (stu.address == NULL)
    {
        return 0;
    }
#endif
    return 0;
}