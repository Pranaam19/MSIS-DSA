#include <assert.h>
#include <stdlib.h>
#include "stack.h"

Stack *stack_new(uint32_t size)
{
    Stack *stk;

    assert(size <= MAX_DEPTH);

    stk = (Stack *)malloc(sizeof(Stack));

    if (stk != NULL)
    {
        stk->size = size;
        stk->top = -1;
    }

    return stk;
}

uint32_t stack_full(const Stack *stk)
{
    assert(stk != NULL);

    return (stk->top == (int32_t)(stk->size - 1));
}

uint32_t stack_empty(const Stack *stk)
{
    assert(stk != NULL);

    return (stk->top == -1);
}

Stack *stack_push(Stack *stk, float data, StackResult *result)
{
    assert(stk != NULL);
    assert(result != NULL);

    if (stack_full(stk))
    {
        result->status = STACK_FULL;
    }
    else
    {
        stk->top++;
        stk->data[stk->top] = data;

        result->data = data;
        result->status = STACK_OK;
    }

    return stk;
}

Stack *stack_pop(Stack *stk, StackResult *result)
{
    assert(stk != NULL);
    assert(result != NULL);

    if (stack_empty(stk))
    {
        result->status = STACK_EMPTY;
    }
    else
    {
        result->data = stk->data[stk->top];
        stk->top--;

        result->status = STACK_OK;
    }

    return stk;
}

Stack *stack_peek(const Stack *stk, StackResult *result)
{
    assert(stk != NULL);
    assert(result != NULL);

    if (stack_empty(stk))
    {
        result->status = STACK_EMPTY;
    }
    else
    {
        result->data = stk->data[stk->top];
        result->status = STACK_OK;
    }

    return (Stack *)stk;
}