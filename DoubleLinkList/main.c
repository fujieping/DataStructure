#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "doubleLinkList.h"
#include <string.h>
#include <errno.h>
#define BUFFER_SIZE 20
#define FILENAMESIZE 100

struct Student
{
    char name[BUFFER_SIZE];
    char sex[BUFFER_SIZE];
    int age;
    char telephone[BUFFER_SIZE];
    char address[BUFFER_SIZE];
};
typedef struct Student Stu;

Stu stu[100] = {0};
int idx = 0;

enum FUNC
{
    EXIT,
    ADD,
    FIND,
    SHOW,
    UPDATE,
    REMOVE,
    FREE,
    SORT,
    // BLACK,
    SAVE,
};

void printDoubleLinkNode(ELEMENTTYPE data) // 打印联系人
{
    Stu *ptr = (Stu *)data;
    printf("%s  %s  %d   %s  %s\n", ptr->name, ptr->sex, ptr->age, ptr->telephone, ptr->address);
}

int showContacts(DoubleLinkList *list) // 显示联系人
{
    if (list == NULL)
    {
        printf("通讯录为空!");
        return -1;
    }
    int ret = 0;
    system("clear");
    if (list == NULL)
    {
        return -1;
    }

    DoubleLinkNode *travelNode = list->head->next;
    while (travelNode != NULL)
    {
        printDoubleLinkNode(travelNode->data);
        travelNode = travelNode->next;
    }

    return ret;
}

bool Strcmp(ELEMENTTYPE data, const char *pStr2) // 通过查找联系人姓名
{
    Stu *pStr1 = (Stu *)data;
    int ret = strcmp(pStr1->name, pStr2);
    if (ret == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Strcmp2(ELEMENTTYPE data, const char *pStr2) // 电话号码不能相同
{
    Stu *pStr1 = (Stu *)data;
    int ret = strcmp(pStr1->telephone, pStr2);
    if (ret == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

DoubleLinkNode *GetDoubleLinkNode(DoubleLinkList *list, const char *pStr, int *pos)
{
    DoubleLinkNode *travelNode = list->head->next;
    DoubleLinkNode *getDoubleLinkNode = NULL;
    int flag = 0;
    int count = 0;
    int size = 0;
    while (travelNode != NULL)
    {
        size++;
        if (Strcmp(travelNode->data, pStr))
        {
            flag = 1;
            count++;
            if (count == 1)
            {
                *pos = size;
                // printf("*pos = %d, size = %d\n", *pos, size);
            }
            getDoubleLinkNode = travelNode;
            printDoubleLinkNode(travelNode->data);
        }
        travelNode = travelNode->next;
    }
    if (flag == 0)
    {
        printf("你所搜索的用户名不在本通讯录!\n");
        return NULL;
    }
    if (count > 1)
    {
        size = 0;
        printf("请根据打印的名单的电话号码选择用户\n");
        printf("请输入电话号码:");
        char tephone[BUFFER_SIZE] = {0};
        scanf("%s", tephone);
        while (getchar() != '\n')
            ;
        DoubleLinkNode *travelNode2 = list->head->next;

        while (travelNode2 != NULL)
        {
            size++;
            if (Strcmp(travelNode2->data, tephone))
            {
                if (pos != NULL)
                {
                    *pos = size;
                }
                return travelNode2;
            }
            travelNode2 = travelNode2->next;
        }
        printf("所输入的电话号码不在通讯录中!\n");
        return NULL;
    }

    return getDoubleLinkNode;
}

void quicksort(Stu *array, int S, int E)
{
    if (array == NULL)
        return;
    // 递归必须有结束条件
    if (S >= E)
        return;
    int start = S;
    int end = E;
    Stu medium = array[S];
    while (start < end)
    {
        while (end > start && strcmp(array[end].name, medium.name) >= 0)
        {
            end--;
        }
        if (end > start)
        {
            array[start] = array[end];
        }
        while (start < end && strcmp(array[start].name, medium.name) <= 0)
        {
            start++;
        }
        if (start < end)
        {
            array[end] = array[start];
        }
        if (start >= end)
        {
            array[start] = medium;
        }
    }
    quicksort(array, S, start - 1);
    quicksort(array, start + 1, E);
}

void sortContacts(DoubleLinkList *list)
{
    if (list == NULL)
    {
        printf("通讯录为空,无法排序!");
        return;
    }
    quicksort(stu, 0, list->len - 1);

    printf("排序成功!");

    return;
}

void updateContacts(DoubleLinkList *list) // 修改联系人
{
    if (list == NULL)
    {
        return;
    }
    char contactname[BUFFER_SIZE];
    memset(contactname, 0, sizeof(contactname));
    printf("请输入你要修改的联系人姓名:");
    scanf("%s", contactname);
    while (getchar() != '\n')
        ;
    int ret = 0;
    DoubleLinkNode *travelNode = GetDoubleLinkNode(list, contactname, &ret);
    if (travelNode == NULL)
    {
        return;
    }
    Stu *stu = travelNode->data;
    printf("请输入你要修改的姓名:");
    scanf("%s", stu->name);
    while (getchar() != '\n')
        ;
    printf("\n");
    printf("请输入你要修改的性别:");
    scanf("%s", stu->sex);
    while (getchar() != '\n')
        ;
    printf("\n");
    printf("请输入你要修改的年龄:");
    scanf("%d", &stu->age);
    while (getchar() != '\n')
        ;
    printf("\n");
    printf("请输入你要修改的号码:");
    scanf("%s", stu->telephone);
    while (getchar() != '\n')
        ;
    DoubleLinkNode *travelNode1 = list->head->next;
    int flag = 0;
    while (travelNode1 != NULL && travelNode1 != travelNode)
    {
        if (Strcmp2(travelNode->data, stu->telephone))
        {
            printf("你所修改的电话号码与他人重复\n");
            return;
        }
        travelNode = travelNode->next;
    }
    printf("\n");
    printf("请输入你要修改的地址:");
    scanf("%s", stu->address);
    while (getchar() != '\n')
        ;
    printf("\n");
    return;
}

void removeContacts(DoubleLinkList *list)
{
    printf("请输入你要删除的人的姓名:");
    char contactname[BUFFER_SIZE] = {0};
    scanf("%s", contactname);
    int pos = 0;
    DoubleLinkNode *getDoubleLinkNode = GetDoubleLinkNode(list, contactname, &pos);
    if (getDoubleLinkNode == NULL)
    {
        printf("你要删除的用户不存在!");
        return;
    }

    // printf("pos = %d\n", pos);
    DoubleLinkListDelAppointPos(list, pos);
    printf("删除成功\n");
    return;
}

int freeContacts(DoubleLinkList **list) // 清空联系人
{
    int ret = 0;
    if (*list == NULL)
    {
        printf("通讯录已经为空,无需释放!");
        return -1;
    }

    DoubleLinkListDestroy(*list);
    *list = NULL;

    return ret;
}

int findcntacts(DoubleLinkList *list, bool (*Strcmp)(ELEMENTTYPE, const char *)) // 查找联系人
{
    int ret = 0;
    system("clear");

    printf("请输入你要查找的联系人姓名:");
    char contactname[BUFFER_SIZE];
    memset(contactname, 0, sizeof(contactname));
    scanf("%s", contactname);
    DoubleLinkNode *travelNode = list->head->next;
    int flag = 0;
    while (travelNode != NULL)
    {
        if (Strcmp(travelNode->data, contactname))
        {
            flag = 1;
            printDoubleLinkNode(travelNode->data);
        }
        travelNode = travelNode->next;
    }
    if (flag == 0)
        printf("你所搜索的用户名不在本通讯录!\n");

    return ret;
}

int addblacklist(DoubleLinkList *list) // 加入黑名单
{
    printf("请输入你要拉黑的用户姓名:");
    char contactname[BUFFER_SIZE] = {0};
    scanf("%s", contactname);
    while (getchar() != '\n')
        ;
    int pos = 0;
    DoubleLinkNode *getDoubleLinkNode = GetDoubleLinkNode(list, contactname, &pos);
    if (getDoubleLinkNode == NULL)
    {
        printf("你要拉黑的用户不存在!\n");
        return -1;
    }
    // DoubleLinkNode *travelNode = list->head->next;
    // while(travelNode != NULL)
    // {
    //     fprintf(fd, "%s  %s  %d  %")
    // }
}

void saveContacts(DoubleLinkList *list) // 保存联系人
{

    FILE *fp = fopen("./contacts.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败!\n");
        return;
    }

    if (list == NULL)
    {
        fclose(fp);
        return;
    }
    DoubleLinkNode *travelNode = list->head->next;
    while (travelNode != NULL)
    {
        Stu *stu = (Stu *)travelNode->data;

        fprintf(fp, "%s  %s  %d  %s  %s\n", stu->name, stu->sex, stu->age, stu->telephone, stu->address);

        travelNode = travelNode->next;
    }

    fclose(fp);
    printf("保存成功!");

    return;
}

int loadContacts(DoubleLinkList *list, int idx) // 加载
{
    FILE *fp = fopen("./contacts.txt", "r");
    if (fp == NULL)
    {
        printf("你要加载的文件路径不正确!");
        perror("open error");
        return -1;
    }

    int ret = 10;
    while (!feof(fp))
    {

        if (fscanf(fp, "%s  %s  %d  %s  %s\n", stu[idx].name, stu[idx].sex, &stu[idx].age, stu[idx].telephone, stu[idx].address) != EOF)
        {
            DoubleLinkListTailInsert(list, &stu[idx]);
            idx++;
        }
        else
        {
            return idx;
        }
    }
    fclose(fp);
    printf("加载成功!\n");
    return idx;
}

int addcontacts(DoubleLinkList *list, int idx) // 添加联系人
{
    system("clear");
    if (idx < 100)
    {
        printf("姓名:");
        scanf("%s", stu[idx].name);
        while (getchar() != '\n')
            ;
        printf("\n");
        printf("性别:");
        scanf("%s", stu[idx].sex);
        while (getchar() != '\n')
            ;
        printf("\n");
        printf("年龄:");
        scanf("%d", &stu[idx].age);
        while (getchar() != '\n')
            ;
        printf("\n");
        printf("号码:");
        scanf("%s", stu[idx].telephone);
        while (getchar() != '\n')
            ;
        DoubleLinkNode *travelNode = list->head->next;
        int flag = 0;
        while (travelNode != NULL)
        {
            if (Strcmp2(travelNode->data, stu[idx].telephone))
            {
                printf("你所填写的电话号码与他人重复\n");
                return idx;
            }
            travelNode = travelNode->next;
        }
        printf("\n");
        printf("地址:");
        scanf("%s", stu[idx].address);
        while (getchar() != '\n')
            ;
        printf("\n");
        DoubleLinkListTailInsert(list, (void *)&stu[idx]);
        idx++;
    }
    else
    {
        printf("通讯录已满");
    }
    return idx;
}

void menu()
{
    // system("clear");
    printf("************通讯录************\n");
    printf("*****************************\n");
    printf("         1: 添加联系人        \n");
    printf("         2: 查找联系人        \n");
    printf("         3: 显示联系人        \n");
    printf("         4: 修改联系人        \n");
    printf("         5: 删除联系人        \n");
    printf("         6: 清空联系人        \n");
    printf("         7: 排序联系人        \n");
    printf("         8: 保存联系人        \n");
    printf("         9: 加入黑名单        \n");
    printf("         0: 退出通讯录        \n");
}

int main()
{
    DoubleLinkList *phone = NULL;
    DoubleLinkList *blacklist = NULL;

    DoubleLinkListInit(&phone);

    idx = loadContacts(phone, idx);
    int select = 1;

    while (select)
    {
        menu();
        printf("请输入选项:");
        scanf("%d", &select);
        while (getchar() != '\n');
        switch (select)
        {
        case ADD:
            idx = addcontacts(phone, idx);
            break;
        case FIND:
            findcntacts(phone, Strcmp);
            break;
        case SHOW:
            showContacts(phone);
            break;
        case UPDATE:
            updateContacts(phone);
            break;
        case REMOVE:
            removeContacts(phone);
            break;
        case FREE:
            freeContacts(&phone);
            break;
        case SORT:
            sortContacts(phone);
            break;
        case SAVE:
            saveContacts(phone);

            break;
        default:
            break;
        }
    }

    return 0;
}
