#include "memallocator.h"
#include <stddef.h>

typedef struct MemoryBlock {
    size_t blockSize;
    int isAllocated;
    struct MemoryBlock* next;
} MemoryBlock;


MemoryBlock* memoryHead = NULL;
void* memoryPoolStart = NULL;
int memoryPoolSize = 0;

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= sizeof(MemoryBlock)) {
        return 1;
    }

    memoryPoolStart = pMemory;
    memoryPoolSize = size;

    memoryHead = (MemoryBlock*)pMemory;
    memoryHead->blockSize = size - sizeof(MemoryBlock);
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

    if (bestFit->blockSize > size + sizeof(MemoryBlock)) {
        MemoryBlock* newBlock = (MemoryBlock*)((char*)bestFit + sizeof(MemoryBlock) + size);
        newBlock->blockSize = bestFit->blockSize - size - sizeof(MemoryBlock);
        newBlock->isAllocated = 0;
        newBlock->next = bestFit->next;

        bestFit->blockSize = size;
        bestFit->next = newBlock;
    }

    bestFit->isAllocated = 1;
    return (void*)((char*)bestFit + sizeof(MemoryBlock));
}

void memfree(void* p) {
    if (!p || memoryHead == NULL) {
        return;
    }

    MemoryBlock* block = (MemoryBlock*)((char*)p - sizeof(MemoryBlock));
    block->isAllocated = 0;

    if (block->next && !block->next->isAllocated) {
        block->blockSize += block->next->blockSize + sizeof(MemoryBlock);
        block->next = block->next->next;
    }

    MemoryBlock* current = memoryHead;
    while (current && current->next != block) {
        current = current->next;
    }

    if (current && !current->isAllocated) {
        current->blockSize += block->blockSize + sizeof(MemoryBlock);
        current->next = block->next;
    }
}

int memgetminimumsize() {
    return sizeof(MemoryBlock);
}

int memgetblocksize() {
    return sizeof(MemoryBlock);
}