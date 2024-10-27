#ifndef ARRSTACK_H
#define ARRSTACK_H
#include <stdint.h>
#define DEF_STACK_SIZE 1024
#define DEF_STACK_BLOCK_SIZE 1024

typedef struct ArrStack {
    void **arr;
    uint32_t currentSize;
    uint32_t maxSize;
    uint32_t blockSize;
} ArrStack_t;

ArrStack_t ArrStackCreate(void);
void ArrStackDestroy(ArrStack_t *arrStack);

void* ArrStackPop(ArrStack_t *stack);
void* ArrStackPeek(ArrStack_t *stack);
void ArrStackPush(ArrStack_t *stack, void *data);
char ArrStackEmpty(ArrStack_t *stack);

#endif //ARRSTACK_H
