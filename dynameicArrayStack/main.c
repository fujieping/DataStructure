#include <stdio.h>
#include "dynameicArrayStack.h"

/* 怎么解决套壳问题*/

#define BUFFER_SIZE 5

int bracket(dynameicArrayStack *pStack, char *pArray, int len)
{
    int left = 0;
    int rigth = 0;
    char *val = NULL;
    for (int idx = 0; idx < len; idx++)
    {
        dynameicArrayStackTop(pStack, (void **)&val);
        if (*val == '[' && pArray[idx] == ']')
        {
            dynameicArrayStackPop(pStack);
        }
        else if (*val == '(' && pArray[idx] == ')')
        {
            dynameicArrayStackPop(pStack);
        }
        else if (*val == '{' && pArray[idx] == '}')
        {
            dynameicArrayStackPop(pStack);
        }       
        else
        {
            dynameicArrayStackPush(pStack, (void*)&pArray[idx]);
        }
    }
    if (dynameicArrayStackEmpty(pStack))
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int main()
{
    dynameicArrayStack stack;
    dynameicArrayStackInit(&stack);
    char array[] = "[{()}]";
    int length = sizeof(array) / sizeof(array[0]);
    
    int tmp = bracket(&stack, array, length - 1);
    if (tmp)
    {
        printf("符合!\n");
    }
    else
    {
        printf("不符合!\n");
    }


#if 0
    dynameicArrayStack stack;   
    dynameicArrayStackInit(&stack);

    int buffer[BUFFER_SIZE] = {5, 32, 21, 56, 87};
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        dynameicArrayStackPush(&stack, &buffer[idx]);
    }

    int size = 0;
    dynameicArrayStackGetSize(&stack, &size);
    printf("size:%d\n", size);

    int *val = NULL;
    while (!dynameicArrayStackEmpty(&stack))
    {
        dynameicArrayStackTop(&stack, (void **)&val);
        printf("val:%c\n", *val);
        dynameicArrayStackPop(&stack);
    }

    /* 栈的销毁*/
    //dynameicArrayStackDestroy(&stack);
#endif
    return 0;
}