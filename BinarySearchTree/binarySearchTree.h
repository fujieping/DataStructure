#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#define ELEMENTTYPE int

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
}BinarySearchTree;

/* 二叉搜索树的初始化*/
int binarySearchTreeInit(BinarySearchTree **pBstree);

/* 二叉搜索数的插入*/
int binarySearchTreeInsert(BinarySearchTree **pBstree, ELEMENTTYPE val);

#endif