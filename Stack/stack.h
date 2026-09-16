#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>

#define MAX_DEPTH 32

typedef struct _stack_ {
    uint32_t size;          // requested stack depth
    int32_t top;            // index of top element
    float data[MAX_DEPTH];  // actual stack data
} Stack;

typedef enum {
    RESULT_INVALID = 0,
    STACK_OK = 1,
    STACK_FULL = 2,
    STACK_EMPTY = 4
} StackStatus;

typedef struct _stack_result {
    float data;
    uint32_t status;
} StackResult;

/* Stack ADT interface */

Stack *stack_new(uint32_t size);

uint32_t stack_full(const Stack *stk);

uint32_t stack_empty(const Stack *stk);

Stack *stack_push(Stack *stk, float data, StackResult *result);

Stack *stack_pop(Stack *stk, StackResult *result);

Stack *stack_peek(const Stack *stk, StackResult *result);

#endif