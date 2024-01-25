#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLinkListQueue.h"
#include "binarySearchTree.h"

#define true    1
#define false   0


/* 静态函数前置声明 */
/* 判断结点是否是度为2的结点 */
static int binarySearchTreeNodeHasTwoChildrens(BSTreeNode *node);
/* 判断结点是否是度为1的结点 */
static int binarySearchTreeNodeHasOneChildren(BSTreeNode *node);
/* 判断结点是否是度为0的结点 (叶子结点) */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node);
/* 创建新的树结点 */
static BSTreeNode *createBstTreeNode(ELEMENTTYPE val);
/* 释放树的结点 */

/* todo... 结点比较函数, 配置不同的类型进行比较 后续函数指针替代 */
static int nodeCompare(ELEMENTTYPE val1, ELEMENTTYPE val2);
/* 获取当前结点的前驱结点 */
static BSTreeNode * precursorNode(BSTreeNode *node);
/* 获取当前结点的后继结点 */
static BSTreeNode * successorNode(BSTreeNode *node);
/* 根据传递的元素获取到指定搜索树结点 */
static BSTreeNode * accordElementGetAppointNode(BinarySearchTree *pBSTree, ELEMENTTYPE val);


/* 二叉搜索树初始化 */
int binarySearchTreeInit(BinarySearchTree **pBSTree, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    int ret = 0;
    if (pBSTree == NULL)
    {
        return -1;
    }

    BinarySearchTree * pBst = (BinarySearchTree*)malloc(sizeof(BinarySearchTree) * 1);
    if (pBst == NULL)
    {
        return -1;
    }
    memset(pBst, 0, sizeof(BinarySearchTree));
    
    pBst->root = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (!(pBst->root))
    {
        return -1;
    }
    memset(pBst->root, 0, sizeof(BSTreeNode));
    /* 初始化树 */
    {    
        pBst->size = 0;
        pBst->compareFunc = compareFunc;
    }

    /* 初始化树的根结点 */
    {
        pBst->root->left = NULL;
        pBst->root->right = NULL;
        pBst->root->parent = NULL;
        pBst->root->val = 0;
    }

    *pBSTree = pBst;
    return ret;
}

#if 0
/* 结点比较函数, 配置不同的类型进行比较 */
/* todo... 后面把它做成包装器 */
static int nodeCompare(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    return val1 - val2;
}
#endif

/* 创建新的结点 */
static BSTreeNode *createBstTreeNode(ELEMENTTYPE val)
{
    BSTreeNode *newNode = (BSTreeNode*)malloc(sizeof(BSTreeNode) * 1);
    if (newNode == NULL)
    {
        return NULL;
    }
    memset(newNode, 0, sizeof(BSTreeNode) * 1);
    {
        /* 开辟的新结点赋值 */
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
    }
    return newNode;
}
/* 二叉搜索树新增元素 */
int binarySearchTreeInsert(BinarySearchTree *pBSTree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 空树 */
    #if 1
    if (pBSTree->size == 0)
    {
        pBSTree->root->val = val;
        /* 树的结点加一 */
        ++(pBSTree->size);
        return ret;
    }
    #else
    /* 如果初始化的时候不分配结点 判断空树就使用这种方式来做 */
    if (pBSTree->root == NULL)
    {
        /* 将新结点置为根结点 */
        pBSTree->root = createBstTreeNode(val);
        (pBSTree->size)++; 
        return ret;
    }
    #endif

    /* 找到要插入位置的父结点 */
    BSTreeNode *parentNode = pBSTree->root;
    BSTreeNode *travelNode = pBSTree->root;
    
    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 更新父结点位置 */
        parentNode = travelNode;
        #if 0
        cmp = nodeCompare(val, travelNode->val);
        #else
        cmp = pBSTree->compareFunc(val, travelNode->val);
        #endif
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
            return ret;
        }
    }

    /* 新增树结点并赋值 */
    BSTreeNode * newNode = createBstTreeNode(val);
    if (newNode == NULL)
    {
        /* todo... */
        return ret;
    }

    if (cmp < 0)
    {
        /* 新结点插入到左子树 */
        parentNode->left = newNode;
    }
    else
    {
        /* 新结点插入到右子树 */
        parentNode->right = newNode;
    }
    newNode->parent = parentNode;
    pBSTree->size++;
    return ret;
}

/* 前驱结点替换当前结点 */
static int binarySearchTreeRemovePrecursorNode(BinarySearchTree *pBSTree, BSTreeNode *node)
{   
    int ret = 0;
    return ret;
}

/* 后继结点替换当前结点 */
static int binarySearchTreeRemoveSuccessorNode(BinarySearchTree *pBSTree, BSTreeNode *node)
{   
    int ret = 0;
    return ret;
}

/* 删除指定结点 */
/* 
 * 删除度为0的结点: 要么是叶子结点,要么是只有唯一一个结点的树。这种情况下直接释放free结点即可
 * 删除度为1的结点: 
 *      当要删除的结点有父结点的时候,修改要删除结点的父结点和子结点的指向关系,再释放free结点.
 *      当要删除的结点没有父结点的时候, 直接改变根结点的指向即可。
 * 删除度为2的结点:
 *      找到前驱结点和后继结点,前驱结点或者后继结点的值替换掉当前要删除结点的值
 *      再删除前驱结点或者后继结点。(度为2结点的前驱结点或者后继结点的度一定是1或者0)
 *      再按照上面删除度为0还是度为1的逻辑操作即可.
 * */
static int binarySearchTreeRemoveAppointNode(BinarySearchTree *pBSTree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return 0;
    }
    
    /* 树的结点减一 */
    pBSTree->size--;

    #if 0
    /* 度为2 */
    if (binarySearchTreeNodeHasTwoChildrens(node))
    {
        /* 前驱结点替换当前结点 */
        BSTreeNode * preNode  = precursorNode(node);
        node->val = preNode->val;
        node = preNode;
    }
    #else
    /* 度为2 */
    /* 后继结点替换当前结点 */
    if (binarySearchTreeNodeHasTwoChildrens(node))
    {
        /* 后继结点替换当前结点 */
        BSTreeNode * nextNode = successorNode(node);
        node->val = nextNode->val;
        node = nextNode;
    }
    #endif
    /* 删除node结点 (node的度一定是0和1) 「度为2结点的前驱结点 和 后继结点一定是 度为1 和 度为0 的结点」*/
    /* 如果node结点的度为1: 要么是左子树 要么是右子树 */
    /* 如果node结点的度为0: replacement为NULL. */
    /* 主要向拿到要删除结点的子结点 */
    BSTreeNode * replaceNode = node->left != NULL ? node->left : node->right;

    BSTreeNode *tmpNode = NULL;
    if (replaceNode != NULL)
    {
        /* 度为1的结点 */
        if (node->parent == NULL)
        {
            /* node的度为1, 并且是根结点 */
            /* 做结点数据备份 */
            tmpNode = pBSTree->root;
            pBSTree->root = replaceNode;
        }
        else
        {
            /* 做结点数据备份 */
            tmpNode = node;
            if (node == node->parent->left)
            {
                node->parent->left = replaceNode;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = replaceNode;
            }
        }
        /* 更改parent结点 */
        replaceNode->parent = node->parent;
        
    }
    else
    {
        /* 度为0的结点 */
        if (node->parent == NULL)
        {
            /* node是根结点 */
            /* todo... 直接释放结点 */
            tmpNode = node;
        }
        else
        {
            /* node是叶子结点, 但不是根结点 */
            if (node == node->parent->left)
            {
                /* 直接释放结点 */
                node->parent->left = NULL;
            }
            else if (node == node->parent->right)
            {
                /* 直接释放结点 */
                node->parent->right = NULL;
            }
            /* 数据备份 */
            tmpNode = node;
        }
    }
    /* 释放结点 : 指针全部变动完之后再操作. */
    if (tmpNode != NULL)
    {
        free(tmpNode);
        tmpNode = NULL;
    }
    return ret;
}

/* 根据传递的元素获取到指定搜索树结点 */
/* very important: 回调函数的位置需要重新放置 */
static BSTreeNode * accordElementGetAppointNode(BinarySearchTree *pBSTree, ELEMENTTYPE val)
{
    BSTreeNode *travelNode = pBSTree->root;
    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = pBSTree->compareFunc(val, travelNode->val);
        if (cmp == 0)
        {
            return travelNode;
        }
        else if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else
        {
            /* cmp > 0 */
            travelNode = travelNode->right;
        }
    }
    return NULL;
}

/* 二叉搜索树删除元素 */
int binarySearchTreeRemove(BinarySearchTree *pBSTree, ELEMENTTYPE val)
{
    return binarySearchTreeRemoveAppointNode(pBSTree, accordElementGetAppointNode(pBSTree, val));
}

/* 二叉搜索树中是否包含指定元素 */
int binarySearchTreeIsContainVal(BinarySearchTree *pBSTree, ELEMENTTYPE val)
{
    #if 1
    return accordElementGetAppointNode(pBSTree, val) != NULL ? true : false;
    #else
    return accordElementGetAppointNode(pBSTree, val) != NULL;
    #endif
}

/* 二叉搜索树是否为空树 */
int binarySearchTreeIsNull(BinarySearchTree *pBSTree)
{
    if (pBSTree == NULL)
    {
        return 1;
    }
    return (pBSTree->size == 0) ? 1 : 0;
}

/* 二叉搜索树元素的个数 */
int binarySearchTreeGetSize(BinarySearchTree *pBSTree, int *pSize)
{
    if (!pBSTree)
    {
        return 0;
    }
    *pSize = pBSTree->size;
    return pBSTree->size;
}

static void binarySearchTreePreOrder(BSTreeNode *node, int (*printFunc)(void *))
{   
    /* 递归结束的条件 */
    if (node == NULL)
    {
        return;
    }
    /* 根结点 左子树 右子树 */
    #if 0
    printf("%d\n", node->val);
    #else
    printFunc(node->val);
    #endif
    binarySearchTreePreOrder(node->left, printFunc);
    binarySearchTreePreOrder(node->right, printFunc);
}

/* 前序遍历 */
/* 访问顺序: 根结点, 前序遍历左子树, 前序遍历右子树 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *))
{
    int ret = 0;
    if (pBSTree == NULL)
    {
        return ret;
    }
    binarySearchTreePreOrder(pBSTree->root, printFunc);
    return ret;
}

static void binarySearchTreeInOrder(BSTreeNode *node, int (*printFunc)(void *))
{
    /* 递归结束的条件 */
    if (node == NULL)
    {
        return;
    }
    /* 左子树 根结点 右子树 */
    binarySearchTreeInOrder(node->left, printFunc);
    #if 0
    printf("%d\n", node->val);
    #else
    printFunc(node->val);
    #endif
    binarySearchTreeInOrder(node->right, printFunc);
    
    return;
}

/* 中序遍历 */
/* 访问顺序: 遍历左子树, 根结点, 前序遍历右子树 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *))
{
    int ret = 0;
    binarySearchTreeInOrder(pBSTree->root, printFunc);
    return ret;
}


static void binarySearchTreePostOrder(BSTreeNode *node, int (*printFunc)(void *))
{
    if (node == NULL)
    {
        return;
    }
    binarySearchTreePostOrder(node->left, printFunc);
    binarySearchTreePostOrder(node->right, printFunc);
    #if 0    
    printf("%d\n", node->val);
    #else
    printFunc(node->val);
    #endif
}

/* 后序遍历 */
/* 访问顺序: 遍历左子树, 右子树, 根结点*/
int binarySearchTreePostOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *))
{
    int ret = 0;
    binarySearchTreePostOrder(pBSTree->root, printFunc);
    return ret;
}

/* 层序遍历 */
int binarySearchTreeLevelOrderTravel(BinarySearchTree *pBSTree, int (*printFunc)(void *))
{
    int ret = 0;
    /* 算法: 使用队列 
        1. 将根结点入队
        2. 循环执行以下操作, 直到队列为空
            2.1 将队头结点(A)出队,并访问
            2.2 将(A)的左子节点入队
            2.3 将(A)的右子节点入队
    */
    doubleLinkListQueue * queue = NULL;
    doublelinklistQueueInit(&queue);
    
    /* 将根结点入队 */
    doublelinklistQueuePush(queue, pBSTree->root);
    /* 队列的大小 */
    int queueSize = 0;
    BSTreeNode * BstVal = NULL;
    /* 当队列不为空的时候 */
    while (doublelinklistQueueSize(queue, &queueSize))
    {
        doublelinklistQueueTop(queue, (void *)&BstVal);
        #if 0
        printf ("BstVal:%d\n", BstVal->val);
        #else
        printFunc(BstVal->val);
        #endif
        doublelinklistQueuePop(queue);

        /* 当左子树存在的时候，将左子树添加到队列中 */
        if (BstVal->left != NULL)
        {
            doublelinklistQueuePush(queue, BstVal->left);
        }
        
        /* 当右子树存在的时候，将右子树添加到队列中 */
        if (BstVal->right != NULL)
        {
            doublelinklistQueuePush(queue, BstVal->right);
        }
    }
    doublelinklistQueueDestory(queue);
    return ret;
}

/* 获取树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pBSTree, int *pHeight)
{
    int ret = 0;
    if (!pBSTree)
    {   
        return 0;
    }
    /* 树的高度 */
    int height = 0;
    if (pBSTree->size == 0)
    {
        return height;
    }

    doubleLinkListQueue * queue = NULL;
    doublelinklistQueueInit(&queue);
    
    /* 将根结点入队 */
    doublelinklistQueuePush(queue, pBSTree->root);
    /* 队列的大小 */
    int levelSize = 1;
    BSTreeNode * BstVal = NULL;

    int queueSize = 0;

    while (doublelinklistQueueSize(queue, &queueSize))
    {
        doublelinklistQueueTop(queue, (void *)&BstVal);
        doublelinklistQueuePop(queue);
        levelSize--;

        if (BstVal->left != NULL)
        {
            doublelinklistQueuePush(queue, BstVal->left);
        }

        if (BstVal->right != NULL)
        {
            doublelinklistQueuePush(queue, BstVal->right);
        }

        if (levelSize == 0)
        {
            doublelinklistQueueSize(queue, &levelSize);
            height++; 
        }
    }
    /* 释放队列 */
    doublelinklistQueueDestory(queue);
    *pHeight = height;
    return ret;
}

/* 二叉树的打印器 */
int binarySearchTreeFormatPrintOut(BinarySearchTree *pBSTree)
{
    int ret = 0;

    return ret;
}

/* 判断结点是否是度为2的结点 */
static int binarySearchTreeNodeHasTwoChildrens(BSTreeNode *node)
{
    if (!node)
    {
        return false;
    }
#if 0
    if (node->left != NULL && node->right != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return node->left && node->right ? true : false;
#endif
}

/* 判断结点是否是叶子结点 */
static int binarySearchTreeNodeHasOneChildren(BSTreeNode *node)
{
    if (!node)
    {
        return false;
    }

    #if 0
    /* 左子树不为NULL && 右子树为NULL 或者 要么左子树为NULL && 右子树不为NULL */
    if ((node->left == NULL && node->right != NULL) || (node->left == NULL && node->right != NULL))
    {
        return true;
    }
    else
    {
        return false;
    }
    #else
    return (node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL) ? true : false;
    #endif
}

static int binarySearchTreeNodeIsLeaf(BSTreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
#if 0
    if ((node->left == NULL) || (node->right == NULL))
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return (node->left == NULL) && (node->right == NULL) ? true : false;
#endif
}
/* 获取当前结点的前驱结点 */
/* 
 * 中序遍历时的前一个结点 : 对于二叉搜索树而言,前驱结点就是前一个比它小的结点 
 * 1. node.left != NULL => precursorNode = node.left.right.right.right.right...,终止条件:right 为 NULL
 * 2. node.left == NULL && node.parent != NULL => precursorNode = node.parent.parent.parent...,终止条件:node在parent的右子树
 * 3. node.left == NULL && node.parent == NULL => 没有前驱结点
 */
static BSTreeNode * precursorNode(BSTreeNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->left != NULL)
    {
        BSTreeNode * travelNode = node->left;
        /* 一直向右查找结点 知道找到左子树的“最右边”结点 */
        while (travelNode->right != NULL)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }   // node->left == NULL.
    /* 跳出上面的if判断就说明:node.left == NULL. 从父结点和祖父结点寻找前驱结点 */
    while (node->parent != NULL && node == node->parent->left)
    {
        node = node->parent;
    }   // 如果在父结点或者祖父结点的右侧就跳出循环
    /* 跳出循环的条件是:node->parent == NULL || node == node.parent.right */
    return node->parent;
}

/* 获取当前结点的后继结点 */
/* 
 * 中序遍历时的后一个结点 : 对于二叉搜索树而言,后继结点就是前一个比它大的结点 
 * 1. node.right != NULL => successorNode = node.right.left.left.left.left.left...
 * 2. node.right == NULL && node.parent != NULL => successorNode.parent.parent.parent...,终止条件:node在parent的左子树
 * 3. node.right == NULL && node.parent == NULL => 没有后续结点
 */
static BSTreeNode * successorNode(BSTreeNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->right != NULL)
    {
        BSTreeNode *travelNode = node->right;
        while(travelNode->left != NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }   // node->right == NULL
    /* 跳出上面的判断一定是node->right == NULL */
    while (node->parent != NULL && node == node->parent->right)
    {
        node = node->parent;
    } // 如果在父结点或者祖父结点的左侧就跳出循环
    /* 跳出循环的条件是:node->parent == NULL || node == node->parent->right.*/
    return node->parent;
}



/* 判断树是否是完全二叉树 */
/* 算法: 
 *  1. 如果node.left != NULL && node.right != NULL. 将node.left和node.right入队
 *  2. 如果node.left == NULL && node.right != NULL. 那么返回false.
 *  3. 如果node.leaf != NULL && node.right == NULL. 或者 node.leaf == NULL && node.right == NULL
 *      那么后面遍历到的所有节点都应该是叶子结点，才是完全二叉树， 否则返回false.  
 * */
int binarySearchTreeIsComplete(BinarySearchTree *pBSTree)
{
    int ret = 0;
    
    /* 如果是空树 */
    #if 0
    if (pBSTree->root == NULL)
    {
        return false;
    }
    #else
    if (pBSTree->size == 0)
    {
        return false;
    }
    #endif

    /* 使用队列的方式来判断二叉树是否是完全二叉树 */
    doubleLinkListQueue *queue = NULL;
    doublelinklistQueueInit(&queue);
    /* 根结点入队 */
    doublelinklistQueuePush(queue, pBSTree->root);

    BSTreeNode * node = NULL;
    int leaf = false;       /* 叶子结点的标记 */
    while (!doublelinklistQueueIsEmpty(queue))
    {
        doublelinklistQueueTop(queue, (void *)&node);
        doublelinklistQueuePop(queue);
        if (leaf && !binarySearchTreeNodeIsLeaf(node))
        {
            return false;
        }

        if (node->left != NULL)
        {
            doublelinklistQueuePush(queue, node->left);
        } else if (node->right != NULL)
        {
            /* node->left == NULL && node->right != NULL */
            return false;
        }

        if (node->right != NULL)
        {
            doublelinklistQueuePush(queue, node->right);
        }
        else 
        {
            /* node->left == NULL && node->right == NULL */
            /* node->left != NULL && node->right == NULL */
            leaf = true;
        }
    }
    /* 释放队列 */
    doublelinklistQueueDestory(queue);
    return true;
}

/* 二叉树的保存 */
int binarySearchTreeSave2File(BinarySearchTree *pBSTree, const char *pathname)
{
    int ret = 0;

    return ret;
}

/* 中间遍历获取到所有的结点 & 释放结点的内存 */
static int binarySearchTreeInOrderDestroy(BinarySearchTree *pBSTree)
{
    int ret = 0;

    return ret;
}

/* 层序方式获取到所有的结点 & 释放结点的内存  */
static int binarySearchTreeLevelOrderDestroy(BinarySearchTree *pBSTree)
{
    int ret = 0;
    /* 算法: 使用队列 
        1. 将根结点入队
        2. 循环执行以下操作, 直到队列为空
            2.1 将队头结点(A)出队,并访问
            2.2 将(A)的左子节点入队
            2.3 将(A)的右子节点入队
    */
    doubleLinkListQueue * queue = NULL;
    doublelinklistQueueInit(&queue);
    
    /* 将根结点入队 */
    doublelinklistQueuePush(queue, pBSTree->root);
    /* 队列的大小 */
    int queueSize = 0;
    BSTreeNode * BstVal = NULL;
    /* 该遍历做数据备份 */
    BSTreeNode * tmpNode = NULL;
    /* 当队列不为空的时候 */
    while (doublelinklistQueueSize(queue, &queueSize))
    {
        doublelinklistQueueTop(queue, (void *)&BstVal);
        doublelinklistQueuePop(queue);

        /* 结点数据备份 */
        tmpNode = BstVal;
        /* 当左子树存在的时候，将左子树添加到队列中 */
        if (BstVal->left != NULL)
        {
            doublelinklistQueuePush(queue, BstVal->left);
        }
        
        /* 当右子树存在的时候，将右子树添加到队列中 */
        if (BstVal->right != NULL)
        {
            doublelinklistQueuePush(queue, BstVal->right);
        }

        /* 释放树的结点 */
        if (tmpNode)
        {
            free(tmpNode);
            tmpNode = NULL;
        }
    }
    /* 释放队列 */
    doublelinklistQueueDestory(queue);

    /* 释放树 */
    if (pBSTree)
    {
        free(pBSTree);
        pBSTree = NULL;
    }
    return ret;
}

/* 二叉搜索树的销毁 */
int binarySearchTreeDestroy(BinarySearchTree *pBSTree)
{
    int ret = 0;
    #if 0
    /* 使用中序遍历的方式销毁*/
    binarySearchTreeInOrderDestroy(pBSTree);
    #else
    /* 使用层序遍历的方式销毁 */
    binarySearchTreeLevelOrderDestroy(pBSTree);
    #endif
    return ret;
}