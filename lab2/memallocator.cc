#include <stddef.h>
#include <stdio.h>
#include "memallocator.h"

typedef struct MemoryBlock {
    unsigned long long blockSize;            // Размер блока памяти
    char isAllocated;            // Признак занятости блока
    struct MemoryBlock* nextBlock; // Указатель на следующий блок
} MemoryBlock;

#define MEMORY_BLOCK_SIZE sizeof(MemoryBlock)

MemoryBlock* memoryHead = NULL;  // Указатель на первый блок памяти
void* allocatedMemory = NULL;   // Указатель на область памяти
unsigned long long totalMemSize = 0;        // Общий размер выделенной памяти

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= MEMORY_BLOCK_SIZE) {
        return 1; // Ошибка инициализации
    }

    allocatedMemory = pMemory;
    totalMemSize = size;

    // Инициализация первого блока
    memoryHead = (MemoryBlock*)pMemory;
    memoryHead->blockSize = size - MEMORY_BLOCK_SIZE;
    memoryHead->isAllocated = 0;
    memoryHead->nextBlock = NULL;

    return 0;
}

void memdone() {
    allocatedMemory = NULL;
    memoryHead = NULL;
    totalMemSize = 0;
}

void* memalloc(int size) {
    if (size <= 0 || allocatedMemory == NULL) {
        return NULL; // Невозможно выделить память
    }

    MemoryBlock* currentBlock = memoryHead;

    // Поиск первого подходящего свободного блока
    while (currentBlock) {
        if (!currentBlock->isAllocated && currentBlock->blockSize >= size) {
            // Разделение блока, если остаётся достаточно места
            if (currentBlock->blockSize >= size + MEMORY_BLOCK_SIZE) {
                MemoryBlock* newBlock = (MemoryBlock*)((char*)currentBlock + MEMORY_BLOCK_SIZE + size);
                newBlock->blockSize = currentBlock->blockSize - size - MEMORY_BLOCK_SIZE;
                newBlock->isAllocated = 0;
                newBlock->nextBlock = currentBlock->nextBlock;

                currentBlock->nextBlock = newBlock;
                currentBlock->blockSize = size;
            }

            currentBlock->isAllocated = 1;
            return (void*)((char*)currentBlock + MEMORY_BLOCK_SIZE);
        }

        currentBlock = currentBlock->nextBlock;
    }

    return NULL; // Нет подходящего блока
}

void memfree(void* pointer) {
    if (pointer == NULL || allocatedMemory == NULL) {
        return; // Невалидный указатель
    }

    MemoryBlock* blockToFree = (MemoryBlock*)((char*)pointer - MEMORY_BLOCK_SIZE);

    if (!blockToFree->isAllocated) {
        return; // Блок уже свободен
    }

    blockToFree->isAllocated = 0;

    // Слияние с предыдущим блоком, если он свободен
    MemoryBlock* currentBlock = memoryHead;
    while (currentBlock && currentBlock->nextBlock != blockToFree) {
        currentBlock = currentBlock->nextBlock;
    }
    if (currentBlock && !currentBlock->isAllocated) {
        currentBlock->blockSize += blockToFree->blockSize + MEMORY_BLOCK_SIZE;
        currentBlock->nextBlock = blockToFree->nextBlock;
        blockToFree = currentBlock;
    }

    // Слияние с последующим блоком, если он свободен
    if (blockToFree->nextBlock && !blockToFree->nextBlock->isAllocated) {
        blockToFree->blockSize += blockToFree->nextBlock->blockSize + MEMORY_BLOCK_SIZE;
        blockToFree->nextBlock = blockToFree->nextBlock->nextBlock;
    }
}

int memgetminimumsize() {
    return MEMORY_BLOCK_SIZE;
}

int memgetblocksize() {
    return MEMORY_BLOCK_SIZE;
}
