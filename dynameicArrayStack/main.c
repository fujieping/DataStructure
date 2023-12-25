#include <stdio.h>
#include "dynameicArrayStack.h"

/* 怎么解决套壳问题*/

#define BUFFER_SIZE 5

int main()
{
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
        printf("val:%d\n", *val);
        dynameicArrayStackPop(&stack);
    }

    /* 栈的销毁*/
    dynameicArrayStackDestroy(&stack);
    
    
    return 0;
}