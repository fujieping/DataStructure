#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_
#include <stdio.h>

#define ELEMENTTYPE void*
/* 树的结点 */
typedef struct BSTreeNode
{
    ELEMENTTYPE val;
    struct BSTreeNode * left;
    struct BSTreeNode * right;
    struct BSTreeNode * parent;
} BSTreeNode;

typedef struct BinarySearchTree
{
    int size;       /* 结点的个数 */
    int height;     /* 树的高度 */


    /* 钩子🪝函数放在树内部 */
    int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE);
    BSTreeNode * root;
} BinarySearchTree;

/* 二叉搜索树初始化 */
int binarySearchTreeInit(BinarySearchTree **pBSTree, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

/* 二叉搜索树新增元素 */
int binarySearchTreeInsert(BinarySearchTree *pBSTree, ELEMENTTYPE val);

/* 二叉搜索树删除元素 */
int binarySearchTreeRemove(BinarySearchTree *pBSTree, ELEMENTTYPE val);

/* 二叉搜索树中是否包含指定元素 */
int binarySearchTreeIsContainVal(BinarySearchTree *pBSTree, ELEMENTTYPE val);

/* 二叉搜索树是否为空树 */
int binarySearchTreeIsNull(BinarySearchTree *pBSTree);

/* 二叉搜索树元素的个数 */
int binarySearchTreeGetSize(BinarySearchTree *pBSTree, int *pSize);

/* 前序遍历 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *));

/* 中序遍历 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *));

/* 后序遍历 */
int binarySearchTreePostOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *));

/* 层序遍历 */
int binarySearchTreeLevelOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *));

/* 获取树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pBSTree, int *pHeight);

/* 二叉树的打印器 */
int binarySearchTreeFormatPrintOut(BinarySearchTree *pBSTree);

/* 判断树是否是完全二叉树 */
int binarySearchTreeIsComplete(BinarySearchTree *pBSTree);

/* 二叉搜索树的销毁 */
int binarySearchTreeDestroy(BinarySearchTree *pBSTree);

/* 二叉树的保存 */
int binarySearchTreeSave2File(BinarySearchTree *pBSTree, const char *pathname);
#endif  // __BINARY_SEARCH_TREE_H_