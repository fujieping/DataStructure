#ifndef __COMMON_H_
#define __COMMON_H_

#if 1
#define ELEMENTTYPE void*
#else
typedef int ELEMENTTYPE;
#endif
typedef struct DynamicArray
{
    ELEMENTTYPE *data;
    int len;
    int capacity;   /* 容量 */
} DynamicArray;

#endif  // __COMMON_H_