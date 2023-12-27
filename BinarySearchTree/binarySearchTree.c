#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarySearchTree.h"

enum STATUS_CODEH
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
// static int printFunc(ELEMENTTYPE val);

/* 根据指定元素获取二叉搜索树的结点*/
static BSTreeNode *baseAppointValGetBSTreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 创建结点*/
static BSTreeNode *createBSTreeNode(ELEMENTTYPE val, BSTreeNode *parentNode);

/* 判断二叉搜索树度为2*/
static int binarySearchTreeNodeHasTwochildrens(BSTreeNode *node);
/* 判断二叉搜索树度为1*/
static int binarySearchTreeNodeHasOnechildrens(BSTreeNode *node);
/* 判断二叉搜索树度为0*/
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node);

/* 二叉搜索树的遍历顺序*/
static int preOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
static int inOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
static int postOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);

/* 获取当前结点的前驱结点*/
static BSTreeNode *bstreeNodepreDecessor(BSTreeNode *node);
/* 获取当前结点的后继结点*/
static BSTreeNode *bstreeNodepreSuccessor(BSTreeNode *node);

/* 二叉搜索树的初始化*/
int binarySearchTreeInit(BinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2),
                         int (*printFunc)(ELEMENTTYPE val))
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
        bstree->compareFunc = compareFunc;
        bstree->printFunc = printFunc;
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

    doubleLinkListQueueInit(bstree->pQueue);
    *pBstree = bstree;
    return ret;
}

/* 比较结点*/
#if 0
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
    return *(int *)val1 > *(int *)val2 ? 1:-1;
#endif
    return 0;
}
#endif
/* 打印结点*/
#if 0
static int printFunc(ELEMENTTYPE val)
{
    int ret = 0;
    printf("data:%d\n", *(int *)val);
    return ret;
}
#endif

/* 判断二叉搜索树度为2*/
static int binarySearchTreeNodeHasTwochildrens(BSTreeNode *node)
{
    return ((node->left != NULL) && (node->right != NULL));
}
/* 判断二叉搜索树度为1*/
static int binarySearchTreeNodeHasOnechildrens(BSTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL) || (node->left != NULL) && (node->right == NULL));
}
/* 判断二叉搜索树度为0*/
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node)
{
    return ((node->left == NULL) && (node->right == NULL));
}

/* 获取当前结点的前驱结点，*/
static BSTreeNode *bstreeNodepreDecessor(BSTreeNode *node)
{
    /* 有左子树*/
    if (node->left != NULL)
    {
        BSTreeNode *travelNode = node->left;
        while (travelNode->right != NULL)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }

    /* 程序到这里node一定没有左子树，那就需要向父节点找 */
    while (node->parent != NULL && node == node->parent->left)
    {
        node = node->right;
    }
    /*node->parent = NULL*/
    /* node == node->parent->left*/
    return node->parent;
}

/* 获取当前结点的后继结点*/
static BSTreeNode *bstreeNodepreSuccessor(BSTreeNode *node)
{
    /* 有右子树*/
    if (node->right != NULL)
    {
        /* 后继结点是在右子树的左子树的左子树*/
        BSTreeNode *travelNode = node->right;
        while (travelNode->left != NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }

    /* 程序到这里node一定没有右子树，那就需要向父节点找 */
    while (node->parent != NULL && node == node->parent->right)
    {
        node = node->right;
    }
    /*node->parent = NULL*/
    /* node == node->parent->left*/
    return node->parent;
}

/* 创建一个新结点*/
static BSTreeNode *createBSTreeNode(ELEMENTTYPE val, BSTreeNode *parentNode)
{
    /* 分配新结点*/
    BSTreeNode *newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return NULL;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode) * 1);
    {
        newBstNode->data = 0;
        newBstNode->left = NULL;
        newBstNode->right = NULL;
        newBstNode->parent = NULL;
    }

    /* 赋值*/
    newBstNode->data = val;
    /* 新结点的paret指针赋值*/
    newBstNode->parent = parentNode;
}

/* 二叉搜索树删除*/
static int binarySearchTreeDeleteNode(BinarySearchTree *pBstree, BSTreeNode *node);
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
        cmp = pBstree->compareFunc(val, travelNode->data);
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
#if 0
    /* 分配新结点*/
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
#else
    BSTreeNode *newBstNode = createBSTreeNode(val, parentNode);
#endif

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

/* 先序:根-左-右*/
static int preOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    pBstree->printFunc(node->data);
    preOrderTravel(pBstree, node->left);

    preOrderTravel(pBstree, node->right);
}
/* 二叉搜索树的前序遍历*/
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    preOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 中序*/
static int inOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    inOrderTravel(pBstree, node->left);
    pBstree->printFunc(node->data);
    inOrderTravel(pBstree, node->right);
}
/* 二叉搜索树的中序遍历*/
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    inOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 后序*/
static int postOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    postOrderTravel(pBstree, node->left);

    postOrderTravel(pBstree, node->right);
    pBstree->printFunc(node->data);
}
/* 二叉搜索树的后序遍历*/
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    postOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 二叉搜索树的层序遍历*/
int binarySearchTreeLeOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    /* 将跟结点入队*/
    doubleLinkListQueuePush(queue, pBstree->root);

    int size = 0;
    BSTreeNode *nodeVal = NULL;
    /* 判断队列是否为空*/
    while (doubleLinkListQueueGetSize(queue, &size))
    {
        doubleLinkListQueueTop(queue, (void *)&nodeVal);
#if 0
        printf ("data:%d\n", nodeVal->data);
#else
        pBstree->printFunc(nodeVal->data);
#endif
        doubleLinkListQueuePop(queue);

        /* 左子树入队*/
        if (nodeVal->left != NULL)
        {
            doubleLinkListQueuePush(queue, nodeVal->left);
        }
        /* 右子树入队*/
        if (nodeVal->right != NULL)
        {
            doubleLinkListQueuePush(queue, nodeVal->right);
        }
    }
    /* 队列释放*/
    doubleLinkListQueueDestroy(queue);
    return ret;
}

/* 根据指定元素获取二叉搜索树的结点*/
static BSTreeNode *baseAppointValGetBSTreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    BSTreeNode *travelNode = pBstree->root;
    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = pBstree->compareFunc(val, travelNode->data);
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
            /* 找到了*/
            return travelNode;
        }
    }
    return NULL;
}

/* 二叉搜索树是否包含指定元素*/
int binarySearchTreeIsContainAppointVal(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetBSTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 获取二叉搜索树的高度*/
int binarySearchTreeGetHeight(BinarySearchTree *pBdtree, int *height)
{
    if (pBdtree == NULL)
    {
        return NULL_PTR;
    }
    int ret = 0;
    if (pBdtree == NULL)
    {
        return NULL_PTR;
    }

    int queuSize = 0;
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    int height1 = 0;
    BSTreeNode *travelNode = NULL;
    doubleLinkListQueuePush(pQueue, pBdtree->root);

    /* 树每一层结点的个数*/
    int travelSize = 1;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void *)&travelNode);
        doubleLinkListQueuePop(pQueue);
        travelSize--;

        /* 左子树不为空*/
        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }
        /* 右子树不为空*/
        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }
        /* 树的当前层结点遍历结束*/
        if (travelSize == 0)
        {
            doubleLinkListQueueGetSize(pQueue, &travelSize);
            height1++;
        }
    }
    /* 释放代码*/
    doubleLinkListQueueDestroy(pQueue);
    /* 解引用*/
    *height = height1;
    return ret;
}

static int binarySearchTreeDeleteNode(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }

    BSTreeNode *DecessorNode = NULL;
    if (binarySearchTreeNodeHasTwochildrens(node))
    {
        /* 找到前驱结点*/
        DecessorNode = bstreeNodepreDecessor(node);
        node->data = DecessorNode->data;
        node = DecessorNode;
        
    }

    /* 程序到这里，要么度为1 或为0*/

    /* 假设是度为1 */
    BSTreeNode * child = node->left != NULL ? node->left : node->right;

    if (child)
    {
        /* 度为1 且是根结点*/
        child->parent = node->parent;
        if (node->parent == NULL)
        {
            pBstree->root = child;
            if (node)
            {
                free(node);
                node = NULL;
            }
        }
        else
        {
            /* 度为1 且不是根结点*/
            if (node == node->parent->left)
            {
                node->parent->left = child;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = child;
            }
            if (node)
                {
                    free(node);
                    node = NULL;
            }
        }
        
    }
    else
    {
        /* 度为0*/
        if (node)
        {
            free(node);
            node = NULL;
        }
    }
}
/* 二叉搜索树的删除*/
int binarySearchTreeDelete(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    return binarySearchTreeDeleteNode(pBstree, baseAppointValGetBSTreeNode(pBstree, val));
    return ret;
}

/* 二叉搜索树的销毁*/
int binarySearchTreeDertroy(BinarySearchTree *pBstree)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }

    int ret = 0;
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 跟结点入队*/
    doubleLinkListQueuePush(pQueue, pBstree->root);
    BSTreeNode *traveleNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {

        doubleLinkListQueueTop(pQueue, (void *)&traveleNode);
        doubleLinkListQueuePop(pQueue);

        if (traveleNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, traveleNode->left);
        }
        if (traveleNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, traveleNode->right);
        }

        /* 最后释放*/
        if (traveleNode)
        {
            free(traveleNode);
            traveleNode = NULL;
        }
    }
    /* 释放队列*/
    doubleLinkListQueueDestroy(pQueue);
    /* 释放树*/
    if (pBstree)
    {
        free(pBstree);
        pBstree = NULL;
    }
}