#include "binarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum STATUS_CODEH
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 二叉搜索树的初始化*/
int binarySearchTreeInit(BinarySearchTree **pBstree)
{
    int ret = 0;
    BinarySearchTree *bstree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据*/
    memset(bstree, 0, sizeof(BinarySearchTree) * 1);
    /* 初始化树*/
    {
        bstree->root = NULL;
        bstree->size = 0;
    }
    /* 分配根节点*/
    bstree->root = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据*/
    memset(bstree->root, 0, sizeof(BSTreeNode) * 1);
    /* 初始化根节点*/
    {
        bstree->root->data = 0;
        bstree->root->left = NULL;
        bstree->root->right = NULL;
        bstree->root->parent = NULL;
    }

    *pBstree = bstree;
    return ret;
}

static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    #if 0
    if(val1 < val2)
    {
        return -1;
    }
    else if (val1 > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    #else
    return val1 > val2 ? 1:-1;
    #endif
}

/* 二叉搜索数的插入*/
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 空树*/
    if (pBstree->size == 0)
    {
        /* 更新树结点个数*/
        pBstree->size++;
        pBstree->root->data = val;
        return ret;
    }

    /* travelNode 指向跟结点*/
    BSTreeNode *travelNode = pBstree->root;
    BSTreeNode *parentNode = pBstree->root;

    /* 确定符号：到底放到左边还是右边*/
    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 标记父结点*/
        parentNode = travelNode;
        cmp = compareFunc(val, travelNode->data);
        /* 插入元素 < 遍历到跟结点 */
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 插入元素 = 遍历到的结点*/
            return ret;
        }
    }

    /* 分配跟结点*/
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if(newBstNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode) * 1);
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }
    /* 新结点赋值*/
    newBstNode->data = val;

    /* 判断插入左边还是右边*/
    if (cmp < 0)
    {
        /* 挂在左子树*/
        parentNode->left = newBstNode;
    }
    else
    {
        parentNode->right = newBstNode;
    }

    pBstree->size++;

    return ret;
}