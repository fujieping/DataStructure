#include <stdio.h>
#include "binarySearchTree.h"

#define BUFFER_SIZE 10

/* 比较基础数据*/
int compareBasicDataFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    int ret = 0;
    int num1 = *(int *)val1;
    int num2 = *(int *)val2;
    return num1 - num2;
}
/* 打印基础数据*/
int printBasicDataFunc(ELEMENTTYPE val)
{
    int ret = 0;
    printf("data:%d  ", *(int *)val);
    return ret;
}

/* 测试*/
int main()
{
    BinarySearchTree *pBsTree = NULL;
    binarySearchTreeInit(&pBsTree, compareBasicDataFunc, printBasicDataFunc);

    int Array[BUFFER_SIZE] = {56, 28, 75, 73, 77, 13, 7, 26, 100, 12};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        binarySearchTreeInsert(pBsTree, (void *)&Array[idx]);
    }
    /* 二叉搜索树的结点个数*/
    int size = 0;
    binarySearchTreeGetNodeSize(pBsTree, &size);
    printf("size:%d\n", size);

    int height = 0;
    /* 二叉搜索树的高度*/
    binarySearchTreeGetHeight(pBsTree, &height);
    printf("height:%d\n", height);

    /* 层次遍历*/
    binarySearchTreeLeOrderTravel(pBsTree);
    printf("\n");

    /* 先序遍历*/
    // binarySearchTreePreOrderTravel(pBsTree);
    // printf("\n");

    /* 中序遍历*/
    binarySearchTreeInOrderTravel(pBsTree);
    printf("\n");

    /* 后序遍历*/
    // binarySearchTreePostOrderTravel(pBsTree);
    // printf("\n");

    /* 删除度为2的结点*/
    int delVal = 56;
    binarySearchTreeDelete(pBsTree, (void *)&delVal);

    /* 二叉搜索树的结点个数*/
    size = 0;
    binarySearchTreeGetNodeSize(pBsTree, &size);
    printf("size:%d\n", size);

    height = 0;
    /* 二叉搜索树的高度*/
    binarySearchTreeGetHeight(pBsTree, &height);
    printf("height:%d\n", height);

    binarySearchTreeInOrderTravel(pBsTree);
    printf("\n");


    /* 删除度为1的结点*/
    delVal = 7;
    binarySearchTreeDelete(pBsTree, (void *)&delVal);

    /* 二叉搜索树的结点个数*/
    size = 0;
    binarySearchTreeGetNodeSize(pBsTree, &size);
    printf("size:%d\n", size);

    height = 0;
    /* 二叉搜索树的高度*/
    binarySearchTreeGetHeight(pBsTree, &height);
    printf("height:%d\n", height);

    binarySearchTreeInOrderTravel(pBsTree);
    printf("\n");



    /* 删除度为0的结点*/
    delVal = 12;
    binarySearchTreeDelete(pBsTree, (void *)&delVal);

    /* 二叉搜索树的结点个数*/
    size = 0;
    binarySearchTreeGetNodeSize(pBsTree, &size);
    printf("size:%d\n", size);

    height = 0;
    /* 二叉搜索树的高度*/
    binarySearchTreeGetHeight(pBsTree, &height);
    printf("height:%d\n", height);

    binarySearchTreeInOrderTravel(pBsTree);
    printf("\n");


    return 0;
}
