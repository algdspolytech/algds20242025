#ifndef LLSTACK_H
#define LLSTACK_H

typedef struct LLNode {
    void *data;
    struct LLNode *prev;
} LLNode_t;

typedef struct LLStack {
    LLNode_t *top;
} LLStack_t;

LLStack_t LLStackCreate(void);

void* LLStackPop(LLStack_t *stack);
void* LLStackPeek(LLStack_t *stack);
void LLStackPush(LLStack_t *stack, void *data);
char LLStackEmpty(LLStack_t *stack);

#endif //LLSTACK_H
