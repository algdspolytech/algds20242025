#include "ArrStack.h"
#include <stdlib.h>

ArrStack_t ArrStackCreate() {
    void **arr = malloc(sizeof(void *) * DEF_STACK_SIZE);
    ArrStack_t arrStack = {
            arr,
            0,
            DEF_STACK_SIZE,
            DEF_STACK_BLOCK_SIZE,
    };

    return arrStack;
}

void ArrStackDestroy(ArrStack_t *arrStack) { free(arrStack->arr); }

void *ArrStackPop(ArrStack_t *stack) {
    void *data = NULL;

    if (!ArrStackEmpty(stack)) {
        stack->currentSize--;
        data = stack->arr[stack->currentSize];

        if (stack->maxSize - stack->currentSize > 2 * stack->blockSize) {
            void **tmp_arr = realloc(stack->arr,
            sizeof(void*) * (stack->maxSize + stack->blockSize));

            if (tmp_arr == NULL) {
                exit(-1);
            }

            stack->arr = tmp_arr;
            stack->maxSize += stack->blockSize;
        }
    }

    return data;
}

void *ArrStackPeek(ArrStack_t *stack) {
    if (!ArrStackEmpty(stack)) {
        return stack->arr[stack->currentSize - 1];
    }
    return NULL;
}

void ArrStackPush(ArrStack_t *stack, void *data) {
    if (stack->currentSize >= stack->maxSize) {
        void **tmp_arr = realloc(stack->arr,
            sizeof(void*) * (stack->maxSize + stack->blockSize));

        if (tmp_arr == NULL) {
            exit(-1);
        }

        stack->arr = tmp_arr;
        stack->maxSize += stack->blockSize;
    }

    stack->arr[stack->currentSize] = data;
    stack->currentSize++;
}
char ArrStackEmpty(ArrStack_t *stack) {
    return stack->currentSize == 0;
}
