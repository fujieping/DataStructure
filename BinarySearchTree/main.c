#include <stdio.h>
#include "binarySearchTree.h"

#define BUFFER_SIZE 5

int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    int ret = 0;
    return *(int *)val1 > *(int *)val2 ? 1:-1;
    return ret;
}

int printFunc(ELEMENTTYPE val)
{
    int ret = 0;
    printf("data:%d  ", *(int *)val);
    return ret;
}

int main()
{
    BinarySearchTree * pBsTree = NULL;
    binarySearchTreeInit(&pBsTree, compareFunc, printFunc);

    int Array[BUFFER_SIZE] = {5, 2, 6, 4, 1};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        binarySearchTreeInsert(pBsTree, &Array[idx]);
    }
    /* 树的大小*/
    printf("size:%d\n", pBsTree->size);

    /* 层次遍历*/
    binarySearchTreeLeOrderTravel(pBsTree);
    printf("\n");

    /* 先序遍历*/
    binarySearchTreePreOrderTravel(pBsTree);
    printf("\n");
    
    /* 中序遍历*/
    binarySearchTreeInOrderTravel(pBsTree);
    printf("\n");

    /* 后序遍历*/
    binarySearchTreePostOrderTravel(pBsTree);
    printf("\n");

    int height = 0;
    binarySearchTreeGetHeight(pBsTree, &height);
    printf("height:%d\n", height);
    return 0;
}