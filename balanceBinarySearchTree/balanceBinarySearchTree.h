#ifndef __BALANCE_BINARY_SEARCH_TREE_H_
#define __BALANCE_BINARY_SEARCH_TREE_H_

#include "doubleLinkListQueue.h"

typedef struct AVLTreeNode
{
    ELEMENTTYPE data;
    int height;
    /* 左子树*/
    struct AVLTreeNode *left;
    /* 右子树*/
    struct AVLTreeNode *right;

#if 1
    /* 父结点*/
    struct AVLTreeNode *parent;
#endif
} AVLTreeNode;

typedef struct BalanceBinarySearchTree
{
    /* 根结点*/
    AVLTreeNode *root;
    /* 树的结点个数*/
    int size;

    /* 钩子函数比较器，*/
    int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 回调，实现自定义打印函数接口*/
    int (*printFunc)(ELEMENTTYPE val);

    /* 把队列放到树里*/
    DoubleLinkListQueue *pQueue;
} BalanceBinarySearchTree;

/* 二叉搜索树的初始化*/
int BalanceBinarySearchTreeInit(BalanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val));

/* 二叉搜索数的插入*/
int BalanceBinarySearchTreeInsert(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定元素*/
int BalanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历*/
int BalanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历*/
int BalanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历*/
int BalanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历*/
int BalanceBinarySearchTreeLeOrderTravel(BalanceBinarySearchTree *pBstree);

/* 获取二叉搜索树的结点个数*/
int BalanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree *pBstree, int *pSize);

/* 获取二叉搜索树的高度*/
int BalanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pBstree, int *height);

/* 二叉搜索树的删除*/
int BalanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁*/
int BalanceBinarySearchTreeDertroy(BalanceBinarySearchTree *pBstree);

#endif