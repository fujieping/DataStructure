#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#define ELEMENTTYPE void*

#include "doubleLinkListQueue.h"

typedef struct BSTreeNode
{
    ELEMENTTYPE data;
    /* 左子树*/
    struct BSTreeNode *left;
    /* 右子树*/
    struct BSTreeNode *right;

    #if 1
    /* 父结点*/
    struct BSTreeNode *parent;
    #endif
}BSTreeNode;

typedef struct BinarySearchTree
{
    /* 根结点*/
    BSTreeNode * root;
    /* 树的结点个数*/
    int size;

    /* 钩子函数比较器，*/
    int(*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 回调，实现自定义打印函数接口*/
    int (*printFunc)(ELEMENTTYPE val);

    /* 把队列放到树里*/
    DoubleLinkListQueue * pQueue;
}BinarySearchTree;

/* 二叉搜索树的初始化*/
int binarySearchTreeInit(BinarySearchTree **pBstree, int(*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int(*printFunc)(ELEMENTTYPE val));

/* 二叉搜索数的插入*/
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定元素*/
int binarySearchTreeIsContainAppointVal(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历*/
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历*/
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历*/
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历*/
int binarySearchTreeLeOrderTravel(BinarySearchTree *pBstree);

/* 获取二叉搜索树的高度*/
int binarySearchTreeGetHeight(BinarySearchTree *pBdtree, int *height);

/* 二叉搜索树的删除*/
int binarySearchTreeDelete(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁*/
int binarySearchTreeDertroy(BinarySearchTree *pBstree);

#endif