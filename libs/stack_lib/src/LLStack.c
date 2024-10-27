#include "LLStack.h"

#include <stddef.h>
#include <stdlib.h>

LLStack_t LLStackCreate() {
    LLStack_t stack = { NULL };
    return stack;
}

void *LLStackPop(LLStack_t *stack) {
    void *data = NULL;

    if (!LLStackEmpty(stack)) {
        data = stack->top->data;

        LLNode_t *toFree = stack->top;
        stack->top = stack->top->prev;

        free(toFree);
    }

    return data;
}

void *LLStackPeek(LLStack_t *stack) {
    if(!LLStackEmpty(stack)) {
        return stack->top->data;
    }
    return NULL;
}

void LLStackPush(LLStack_t *stack, void *data) {
    LLNode_t *node = malloc(sizeof(LLNode_t));

    node->data = data;
    node->prev = stack->top;
    stack->top = node;
}

char LLStackEmpty(LLStack_t *stack) {
    return stack->top == NULL;
}
