#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balanceBinarySearchTree.h"

enum STATUS_CODEH
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

#define true 1
#define false 0

static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
// static int printFunc(ELEMENTTYPE val);

/* 根据指定元素获取二叉搜索树的结点*/
static AVLTreeNode *baseAppointValGetAVLTreeNode(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 创建结点*/
static AVLTreeNode *createAVLTreeNode(ELEMENTTYPE val, AVLTreeNode *parentNode);

/* 判断二叉搜索树度为2*/
static int BalanceBinarySearchTreeNodeHasTwochildrens(AVLTreeNode *node);
/* 判断二叉搜索树度为1*/
static int BalanceBinarySearchTreeNodeHasOnechildrens(AVLTreeNode *node);
/* 判断二叉搜索树度为0*/
static int BalanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node);

/* 二叉搜索树的遍历顺序*/
static int preOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
static int inOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);
static int postOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 获取当前结点的前驱结点*/
static AVLTreeNode *AVLTreeNodepreDecessor(AVLTreeNode *node);
/* 获取当前结点的后继结点*/
static AVLTreeNode *AVLTreeNodepreSuccessor(AVLTreeNode *node);
/* 删除*/
static int BalanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 添加结点之后的操作，判断平衡*/
static int insertNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 计算结点的平衡因子*/
static int AVLTreeNodeBalanceFactor(AVLTreeNode *node);

/* 判断平衡因子*/
static int AVLTreeNodeIsBalanced(AVLTreeNode *node);

/* 更新结点高度*/
static int AVLTreeNodeUpdateHeight(AVLTreeNode *node);

/* 调整平衡*/
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 获取AVL结点较高的子结点*/
static AVLTreeNode * AVLTreeNodeGetChildIsTaller(AVLTreeNode *node);

/* 当前结点是父节点的左子树*/
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode *node);
/* 当前结点是父节点的右子树*/
static int AVLTreeCurrentNodeIsRight(AVLTreeNode *node);

/* 右旋*/
static int AVLTreeCurrentNodeRotateRight(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand);
/* 左旋*/
static int AVLTreeCurrentNodeRotateLeft(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand);

/* 二叉搜索树的初始化*/
int BalanceBinarySearchTreeInit(BalanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2),
                                int (*printFunc)(ELEMENTTYPE val))
{
    int ret = 0;
    BalanceBinarySearchTree *bstree = (BalanceBinarySearchTree *)malloc(sizeof(BalanceBinarySearchTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据*/
    memset(bstree, 0, sizeof(BalanceBinarySearchTree) * 1);
    /* 初始化树*/
    {
        bstree->root = NULL;
        bstree->size = 0;
        bstree->compareFunc = compareFunc;
        bstree->printFunc = printFunc;
    }
    /* 分配根节点*/
    bstree->root = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据*/
    memset(bstree->root, 0, sizeof(AVLTreeNode) * 1);
    /* 初始化根节点*/
    {
        bstree->root->data = 0;
        bstree->root->height = 0;
        bstree->root->left = NULL;
        bstree->root->right = NULL;
        bstree->root->parent = NULL;
    }

    doubleLinkListQueueInit(&bstree->pQueue);
    *pBstree = bstree;
    return ret;
}

/* 当前结点是父节点的左子树*/
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode *node)
{
    return (node->parent != NULL) && (node = node->parent->left);
}

/* 当前结点是父节点的左子树*/
static int AVLTreeCurrentNodeIsRight(AVLTreeNode *node)
{
    return (node->parent != NULL) && (node = node->parent->right);
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

/* 计算结点的平衡因子*/
static int AVLTreeNodeBalanceFactor(AVLTreeNode *node)
{
    /* 左子树高度*/
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树高度*/
    int rightHeight = node->right == NULL ? 0 : node->right->height;

    return leftHeight - rightHeight;
}

/* 判断平衡因子*/
static int AVLTreeNodeIsBalanced(AVLTreeNode *node)
{
    return abs(AVLTreeNodeBalanceFactor(node)) <= 1;
}

static int tmpMax(int val1, int val2)
{
    return val1 - val2 >= 0 ? val1 : val2;
}

/* 更新高度*/
static int AVLTreeNodeUpdateHeight(AVLTreeNode *node)
{
    int ret = 0;
#if 1
    /* 左子树高度*/
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    /* 右子树高度*/
    int rightHeight = node->right == NULL ? 0 : node->right->height;
    return 1 + tmpMax(leftHeight, rightHeight);
#else

#endif
    return ret;
}
/* 判断二叉搜索树度为2*/
static int BalanceBinarySearchTreeNodeHasTwochildrens(AVLTreeNode *node)
{
    return ((node->left != NULL) && (node->right != NULL));
}
/* 判断二叉搜索树度为1*/
static int BalanceBinarySearchTreeNodeHasOnechildrens(AVLTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL) || (node->left != NULL) && (node->right == NULL));
}
/* 判断二叉搜索树度为0*/
static int BalanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node)
{
    return ((node->left == NULL) && (node->right == NULL));
}

/* 获取当前结点的前驱结点，*/
static AVLTreeNode *AVLTreeNodepreDecessor(AVLTreeNode *node)
{
    /* 有左子树*/
    if (node->left != NULL)
    {
        AVLTreeNode *travelNode = node->left;
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
static AVLTreeNode *AVLTreeNodepreSuccessor(AVLTreeNode *node)
{
    /* 有右子树*/
    if (node->right != NULL)
    {
        /* 后继结点是在右子树的左子树的左子树*/
        AVLTreeNode *travelNode = node->right;
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
static AVLTreeNode *createAVLTreeNode(ELEMENTTYPE val, AVLTreeNode *parentNode)
{
    /* 分配新结点*/
    AVLTreeNode *newAVLNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    if (newAVLNode == NULL)
    {
        return NULL;
    }
    memset(newAVLNode, 0, sizeof(AVLTreeNode) * 1);
    {
        newAVLNode->data = 0;
        newAVLNode->height = 1;
        newAVLNode->left = NULL;
        newAVLNode->right = NULL;
        newAVLNode->parent = NULL;
    }

    /* 赋值*/
    newAVLNode->data = val;
    /* 新结点的paret指针赋值*/
    newAVLNode->parent = parentNode;
}

/* 二叉搜索树删除*/
static int BalanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

static AVLTreeNode * AVLTreeNodeGetChildIsTaller(AVLTreeNode *node)
{
    int leftHeight = node->left == NULL ? 0 : node->left;
    int rightHeight = node->right == NULL ? 0 : node->right;
    if (leftHeight > rightHeight)
    {
        return node->left;
    }
    else if (leftHeight < rightHeight)
    {
        return node->right;
    }
    else
    {
        /* leftHeight == rightHeight */
        if (node->parent != NULL && node == node->parent->left)
        {
            return node->left;
        }
        else
        {
            return node->right;
        }
    }
}

/* 右旋:LL*/
static int AVLTreeCurrentNodeRotateRight(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand)
{
    AVLTreeNode *parent = grand->left;
    AVLTreeNode *child = parent->right;

    grand->left = child;
    parent->right = grand;

    parent->parent = grand->parent;

    if (AVLTreeCurrentNodeIsLeft(grand))
    {
        grand->parent->left = parent;
    }
    else if (AVLTreeCurrentNodeIsRight(grand))
    {
        grand->parent->right = parent;
    }
    else
    {
        pBstree->root = parent;
    }
    grand->parent = parent;

    if (child != NULL)
    {
        child->parent = grand;
    }

    AVLTreeNodeUpdateHeight(grand);
    AVLTreeNodeUpdateHeight(parent);
}
/* 左旋:RR*/
static int AVLTreeCurrentNodeRotateLeft(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand)
{
    /* */
    AVLTreeNode *parent = grand->right;
    AVLTreeNode *child = parent->left;
    grand->right = child;
    parent->left = grand;

    /* parent 成为新的根结点*/
    parent->parent = grand->parent;
    /* grand 为父节点的左子结点*/
    if (AVLTreeCurrentNodeIsLeft(grand))
    {
        grand->parent->left = parent;
    }/* grand 为父节点的右子结点*/
    else if (AVLTreeCurrentNodeIsRight(grand))
    {
        grand->parent->right = parent;
    }/* grand 为树的根结点*/
    else
    {
        pBstree->root = parent;
    }

    if (child)
    {
        child->parent = grand;
    }
    /* 更新高度*/
    AVLTreeNodeUpdateHeight(grand);
    AVLTreeNodeUpdateHeight(parent);
}


/* 调整平衡*/
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    /* LL RR LR RL*/
    AVLTreeNode *parent = AVLTreeNodeGetChildIsTaller(node);
    AVLTreeNode *child = AVLTreeNodeGetChildIsTaller(parent);
    /* L*/
    if (AVLTreeCurrentNodeIsLeft(parent))
    {
        if (AVLTreeCurrentNodeIsLeft(child))
        {
            /* LL*/
            AVLTreeCurrentNodeRotateRight(pBstree, node);
        }
        else
        {
            /* LR*/
        }
    }
    else
    {
        /* R*/
        if (AVLTreeCurrentNodeIsLeft(child))
        {
            /* RL*/
        }
        else
        {
            /* RR*/
        }
    }
}

/* 添加结点之后的操作，判断平衡*/
static int insertNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    /* 更新结点，调整平衡*/
    while ((node = node->parent) != NULL)
    {
        if (AVLTreeNodeIsBalanced(node))
        {
            /* 结点平衡，就更新高度*/
            AVLTreeNodeUpdateHeight(node);
        }
        else
        {
            /* 开始调整*/
            AVLTreeNodeAdjustBalance(pBstree, node);

            /* 调整完最低的不平衡结点，上面的不平衡结点就已经平衡*/
            break;
        }
    }
    return ret;
}

/* 二叉搜索数的插入*/
int BalanceBinarySearchTreeInsert(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 空树*/
    if (pBstree->size == 0)
    {
        /* 更新树结点个数*/
        pBstree->size++;
        pBstree->root->data = val;

        insertNodeAfter(pBstree, pBstree->root);
        return ret;
    }

    /* travelNode 指向跟结点*/
    AVLTreeNode *travelNode = pBstree->root;
    AVLTreeNode *parentNode = pBstree->root;

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
    AVLTreeNode * newAVLNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    if(newAVLNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newAVLNode, 0, sizeof(AVLTreeNode) * 1);
    {
        newAVLNode->data = 0;
        newAVLNode->left = NULL;
        newAVLNode->right = NULL;
        newAVLNode->parent = NULL;
    }
    /* 新结点赋值*/
    newAVLNode->data = val;
#else
    AVLTreeNode *newAVLNode = createAVLTreeNode(val, parentNode);
#endif

    /* 判断插入左边还是右边*/
    if (cmp < 0)
    {
        /* 挂在左子树*/
        parentNode->left = newAVLNode;
    }
    else
    {
        parentNode->right = newAVLNode;
    }

    insertNodeAfter(pBstree, newAVLNode);

    pBstree->size++;

    return ret;
}

/* 先序:根-左-右*/
static int preOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
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
int BalanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    preOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 中序*/
static int inOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
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
int BalanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    inOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 后序*/
static int postOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
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
int BalanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    postOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 二叉搜索树的层序遍历*/
int BalanceBinarySearchTreeLeOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    /* 将跟结点入队*/
    doubleLinkListQueuePush(queue, pBstree->root);

    int size = 0;
    AVLTreeNode *nodeVal = NULL;
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
static AVLTreeNode *baseAppointValGetAVLTreeNode(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    AVLTreeNode *travelNode = pBstree->root;
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
int BalanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetAVLTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 获取二叉搜索树的结点个数*/
int BalanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree *pBstree, int *pSize)
{
    int ret = 0;
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    if (pSize)
    {
        *pSize = pBstree->size;
    }
    return ret;
}

/* 获取二叉搜索树的高度*/
int BalanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pBstree, int *height)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    if (pBstree->size == 0)
    {
        return 0;
    }
#if 0
    return *height = pBstree->root->height;
#else
    int ret = 0;
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }

    int queuSize = 0;
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    int height1 = 0;
    AVLTreeNode *travelNode = NULL;
    doubleLinkListQueuePush(pQueue, pBstree->root);

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
#endif
    
}

static int BalanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }

    AVLTreeNode *DecessorNode = NULL;
    if (BalanceBinarySearchTreeNodeHasTwochildrens(node))
    {
        /* 找到前驱结点*/
        DecessorNode = AVLTreeNodepreDecessor(node);
        node->data = DecessorNode->data;
        node = DecessorNode;
    }

    /* 程序到这里，要么度为1 或为0*/
    /* 假设是度为1 */
    AVLTreeNode *child = node->left != NULL ? node->left : node->right;

    AVLTreeNode *delNode = NULL;

    if (child)
    {
        /* 度为1 且是根结点*/
        child->parent = node->parent;
        if (node->parent == NULL)
        {
            pBstree->root = child;
            delNode = node;
            // if (node)
            // {
            //     free(node);
            //     node = NULL;
            // }
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
            delNode = node;
            // if (node)
            //     {
            //         free(node);
            //         node = NULL;
            // }
        }
    }
    else
    {
        if (node->parent == NULL)
        {
            /* 度为0 且是根结点 */
            delNode = node;
        }
        // if (node)
        // {
        //     free(node);
        //     node = NULL;
        // }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = NULL;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = NULL;
            }

            delNode = node;
        }
    }
    if (delNode)
    {
        free(delNode);
        delNode = NULL;
    }
    pBstree->size--;
    return ret;
}

/* 二叉搜索树的删除*/
int BalanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    BalanceBinarySearchTreeDeleteNode(pBstree, baseAppointValGetAVLTreeNode(pBstree, val));
    return ret;
}

/* 二叉搜索树的销毁*/
int BalanceBinarySearchTreeDertroy(BalanceBinarySearchTree *pBstree)
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
    AVLTreeNode *traveleNode = NULL;
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