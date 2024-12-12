#include <stddef.h>
#include "memallocator.h"

typedef struct MemoryBlock {
    size_t blockSize; // Memory block size
    char isAllocated;
    struct MemoryBlock* nextBlock;
    struct MemoryBlock* prevBlock;
} MemoryBlock;

#define MEMORY_BLOCK_SIZE sizeof(MemoryBlock)

MemoryBlock* memoryHead = NULL; // Pointer to the head of the block list
void* allocatedMemory = NULL; // A pointer to the allocated memory
size_t totalMemSize = 0; // The total size of the allocated memory

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= MEMORY_BLOCK_SIZE) {
        return 1;
    }

    allocatedMemory = pMemory;
    totalMemSize = size;

    memoryHead = (MemoryBlock*)pMemory;
    memoryHead->blockSize = size - MEMORY_BLOCK_SIZE;
    memoryHead->isAllocated = 0;
    memoryHead->prevBlock = NULL;
    memoryHead->nextBlock = NULL;

    return 0;
}

void memdone() {
    allocatedMemory = NULL;
    memoryHead = NULL;
    totalMemSize = 0;
    return;
}

void* memalloc(int size) {
    if (size <= 0 || !allocatedMemory) {
        return NULL;
    }

    MemoryBlock* selectedBlock = NULL;
    MemoryBlock* currentBlock = memoryHead;

    // Search for a suitable block
    while (currentBlock) {
        if (!currentBlock->isAllocated && currentBlock->blockSize >= size) {
            if (!selectedBlock || selectedBlock->blockSize > currentBlock->blockSize) {
                selectedBlock = currentBlock; // Saving the best block
            }
        }
        currentBlock = currentBlock->nextBlock;
    }

    if (!selectedBlock) {
        return NULL;
    }

    if (selectedBlock->blockSize >= size + MEMORY_BLOCK_SIZE) {
        MemoryBlock* newBlock = (MemoryBlock*)((char*)selectedBlock + MEMORY_BLOCK_SIZE + size);
        newBlock->blockSize = selectedBlock->blockSize - size - MEMORY_BLOCK_SIZE; // The size of the new block
        newBlock->isAllocated = 0;
        newBlock->prevBlock = selectedBlock;
        newBlock->nextBlock = selectedBlock->nextBlock;

        if (selectedBlock->nextBlock) {
            selectedBlock->nextBlock->prevBlock = newBlock;
        }

        selectedBlock->nextBlock = newBlock;
        selectedBlock->blockSize = size;
    }

    selectedBlock->isAllocated = 1;
    return (void*)((char*)selectedBlock + MEMORY_BLOCK_SIZE);
}

void memfree(void* pointer) {
    if (!pointer || !allocatedMemory) {
        return;
    }

    MemoryBlock* blockToFree = (MemoryBlock*)((char*)pointer - MEMORY_BLOCK_SIZE);

    if (!blockToFree->isAllocated) {
        return;
    }

    blockToFree->isAllocated = 0;

    // Combine with the previous block if it is free
    if (blockToFree->prevBlock && !blockToFree->prevBlock->isAllocated) {
        blockToFree->prevBlock->blockSize += blockToFree->blockSize + MEMORY_BLOCK_SIZE;
        blockToFree->prevBlock->nextBlock = blockToFree->nextBlock;
        if (blockToFree->nextBlock) {
            blockToFree->nextBlock->prevBlock = blockToFree->prevBlock;
        }
        blockToFree = blockToFree->prevBlock;
    }

    // Combine with the next block, if it is free
    if (blockToFree->nextBlock && !blockToFree->nextBlock->isAllocated) {
        blockToFree->blockSize += blockToFree->nextBlock->blockSize + MEMORY_BLOCK_SIZE;
        blockToFree->nextBlock = blockToFree->nextBlock->nextBlock;
        if (blockToFree->nextBlock) {
            blockToFree->nextBlock->prevBlock = blockToFree;
        }
    }
}

int memgetminimumsize() {
    return MEMORY_BLOCK_SIZE;
}

int memgetblocksize() {
    return MEMORY_BLOCK_SIZE;
}