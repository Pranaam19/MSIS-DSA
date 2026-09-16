#include <assert.h>
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

void test_capacity(uint32_t size)
{
    Stack *stk = stack_new(size);
    StackResult result = {0, RESULT_INVALID};

    assert(stk != NULL);

    /* Push until the stack is full */
    for (uint32_t i = 0; i < size; i++)
    {
        stack_push(stk, (float)i, &result);

        assert(result.status == STACK_OK);
    }

    /* Next push should fail */
    stack_push(stk, 999, &result);

    assert(result.status == STACK_FULL);

    /* Peek at the top element */
    result.status = RESULT_INVALID;

    stack_peek(stk, &result);

    assert(result.status == STACK_OK);
    assert(result.data == (float)(size - 1));

    /* Pop all elements */
    for (uint32_t i = 0; i < size; i++)
    {
        result.status = RESULT_INVALID;

        stack_pop(stk, &result);

        assert(result.status == STACK_OK);
        assert(result.data == (float)(size - i - 1));
    }

    /* Stack should now be empty */
    assert(stack_empty(stk));

    free(stk);
}

void test_arbitrary_stack(void)
{
    Stack *stk = stack_new(MAX_DEPTH);
    StackResult result = {0, RESULT_INVALID};

    assert(stk != NULL);

    /* Push values */
    for (uint32_t i = 0; i < MAX_DEPTH; i++)
    {
        stack_push(stk, (float)i, &result);

        assert(result.status == STACK_OK);
    }

    /* Stack should be full */
    assert(stack_full(stk));

    /* Push one more value */
    stack_push(stk, 100, &result);

    assert(result.status == STACK_FULL);

    /* Peek top value */
    result.status = RESULT_INVALID;

    stack_peek(stk, &result);

    assert(result.status == STACK_OK);
    assert(result.data == MAX_DEPTH - 1);

    /* Pop all values */
    for (uint32_t i = 0; i < MAX_DEPTH; i++)
    {
        result.status = RESULT_INVALID;

        stack_pop(stk, &result);

        assert(result.status == STACK_OK);
        assert(result.data == MAX_DEPTH - i - 1);
    }

    /* Stack should be empty */
    assert(stack_empty(stk));

    free(stk);
}

int main(void)
{
    test_capacity(5);
    test_arbitrary_stack();

    printf("All tests passed!\n");

    return 0;
}