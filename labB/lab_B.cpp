#include "memallocator.h"
#include <stddef.h>

typedef struct MemoryBlock {
    size_t blockSize;
    int isAllocated;
    struct MemoryBlock* next;
} MemoryBlock;

#define MEMORY_BLOCK_SIZE sizeof(MemoryBlock)

MemoryBlock* memoryHead = NULL;
void* memoryPoolStart = NULL;
int memoryPoolSize = 0;

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= MEMORY_BLOCK_SIZE) {
        return 1;
    }

    memoryPoolStart = pMemory;
    memoryPoolSize = size;

    memoryHead = (MemoryBlock*)pMemory;
    memoryHead->blockSize = size - MEMORY_BLOCK_SIZE;
    memoryHead->isAllocated = 0;
    memoryHead->next = NULL;

    return 0;
}

void memdone() {
    memoryHead = NULL;
    memoryPoolStart = NULL;
    memoryPoolSize = 0;
}

void* memalloc(int size) {
    if (size <= 0 || memoryHead == NULL) {
        return NULL;
    }

    MemoryBlock* current = memoryHead;
    MemoryBlock* bestFit = NULL;

    while (current) {
        if (!current->isAllocated && current->blockSize >= size) {
            if (!bestFit || current->blockSize < bestFit->blockSize) {
                bestFit = current;
            }
        }
        current = current->next;
    }

    if (!bestFit) {
        return NULL;
    }

    if (bestFit->blockSize > size + MEMORY_BLOCK_SIZE) {
        MemoryBlock* newBlock = (MemoryBlock*)((char*)bestFit + MEMORY_BLOCK_SIZE + size);
        newBlock->blockSize = bestFit->blockSize - size - MEMORY_BLOCK_SIZE;
        newBlock->isAllocated = 0;
        newBlock->next = bestFit->next;

        bestFit->blockSize = size;
        bestFit->next = newBlock;
    }

    bestFit->isAllocated = 1;
    return (void*)((char*)bestFit + MEMORY_BLOCK_SIZE);
}

void memfree(void* p) {
    if (!p || memoryHead == NULL) {
        return;
    }

    MemoryBlock* block = (MemoryBlock*)((char*)p - MEMORY_BLOCK_SIZE);
    block->isAllocated = 0;

    if (block->next && !block->next->isAllocated) {
        block->blockSize += block->next->blockSize + MEMORY_BLOCK_SIZE;
        block->next = block->next->next;
    }

    MemoryBlock* current = memoryHead;
    while (current && current->next != block) {
        current = current->next;
    }

    if (current && !current->isAllocated) {
        current->blockSize += block->blockSize + MEMORY_BLOCK_SIZE;
        current->next = block->next;
    }
}

int memgetminimumsize() {
    return MEMORY_BLOCK_SIZE;
}

int memgetblocksize() {
    return MEMORY_BLOCK_SIZE;
}
