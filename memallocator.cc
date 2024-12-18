#include "memallocator.h"
#include <stddef.h>

typedef struct BlockHeader {
    int size;
    int free;
    struct BlockHeader* next;
} BlockHeader;
static void* memoryPool = NULL;
static int memoryPoolSize = 0;
static BlockHeader* blockListHead = NULL;
int memgetminimumsize() {
    return sizeof(BlockHeader);
}
int memgetblocksize() {
    return sizeof(BlockHeader);
}
int meminit(void* pMemory, int size) {
    if (!pMemory || size < memgetminimumsize()) {
        return 0;
    }
    memoryPool = pMemory;
    memoryPoolSize = size;
    BlockHeader* initialBlock = (BlockHeader*)pMemory;
    initialBlock->size = size - memgetblocksize();
    initialBlock->free = 1;
    initialBlock->next = NULL;
    blockListHead = initialBlock;
    return 1;
}
void memdone() {
    memoryPool = NULL;
    memoryPoolSize = 0;
    blockListHead = NULL;
}
void* memalloc(int size) {
    if (!memoryPool || size <= 0) {
        return NULL;
    }
    BlockHeader* current = blockListHead;
    BlockHeader* bestFit = NULL;
    BlockHeader* bestFitPrev = NULL;
    BlockHeader* prev = NULL;
    while (current) {
        if (current->free && current->size >= size) {
            if (!bestFit || current->size < bestFit->size) {
                bestFit = current;
                bestFitPrev = prev;
            }
        }
        prev = current;
        current = current->next;
    }
    if (!bestFit) {
        return NULL;
    }
    if (bestFit->size >= size + memgetblocksize() + 1) {
        BlockHeader* newBlock = (BlockHeader*)((char*)bestFit + memgetblocksize() + size);
        newBlock->size = bestFit->size - size - memgetblocksize();
        newBlock->free = 1;
        newBlock->next = bestFit->next;

        bestFit->size = size;
        bestFit->free = 0;
        bestFit->next = newBlock;
    }
    else {
        bestFit->free = 0;
    }
    return (char*)bestFit + memgetblocksize();
}
void memfree(void* p) {
    if (!p || !memoryPool) {
        return;
    }
    BlockHeader* block = (BlockHeader*)((char*)p - memgetblocksize());
    block->free = 1;
    if (block->next && block->next->free) {
        block->size += memgetblocksize() + block->next->size;
        block->next = block->next->next;
    }
    BlockHeader* current = blockListHead;
    BlockHeader* prev = NULL;
    while (current && current != block) {
        prev = current;
        current = current->next;
    }
    if (prev && prev->free) {
        prev->size += memgetblocksize() + block->size;
        prev->next = block->next;
    }
}