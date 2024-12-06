#include <stddef.h>
#include "memallocator.h"

typedef struct MemoryBlock {
    size_t blockSize; // Размер блока памяти
    char isAllocated; // Статус блока (выделен/свободен)
    struct MemoryBlock* nextBlock; // Указатель на следующий блок
    struct MemoryBlock* prevBlock; // Указатель на предыдущий блок
} MemoryBlock;

#define MEMORY_BLOCK_SIZE sizeof(MemoryBlock)

MemoryBlock* memoryHead = NULL; // Указатель на начало списка блоков
void* allocatedMemory = NULL; // Указатель на весь пул памяти
size_t totalMemSize = 0; // Общий размер пула памяти

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= MEMORY_BLOCK_SIZE) {
        return 1;
    }

    allocatedMemory = pMemory;
    totalMemSize = size;

    // Начальная инициализация первого блока в пуле памяти
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
        return NULL; // Неверный запрос
    }

    MemoryBlock* currentBlock = memoryHead;

    // Стратегия "первый подходящий" - найти первый свободный блок с достаточным размером
    while (currentBlock) {
        if (!currentBlock->isAllocated && currentBlock->blockSize >= size) {
            // Блок найден, проверяем, нужно ли разделить его
            if (currentBlock->blockSize >= size + MEMORY_BLOCK_SIZE) {
                // Разделяем блок, создавая новый пустой
                MemoryBlock* newBlock = (MemoryBlock*)((char*)currentBlock + MEMORY_BLOCK_SIZE + size);
                newBlock->blockSize = currentBlock->blockSize - size - MEMORY_BLOCK_SIZE;
                newBlock->isAllocated = 0;
                newBlock->prevBlock = currentBlock;
                newBlock->nextBlock = currentBlock->nextBlock;

                if (currentBlock->nextBlock) {
                    currentBlock->nextBlock->prevBlock = newBlock;
                }

                currentBlock->nextBlock = newBlock;
                currentBlock->blockSize = size;
            }

            // Помечаем текущий блок как занятый
            currentBlock->isAllocated = 1;
            return (void*)((char*)currentBlock + MEMORY_BLOCK_SIZE);
        }
        currentBlock = currentBlock->nextBlock;
    }

    return NULL; // Нет подходящего блока
}

void memfree(void* pointer) {
    if (!pointer || !allocatedMemory) {
        return;
    }

    // Получаем указатель на структуру блока через смещение
    MemoryBlock* blockToFree = (MemoryBlock*)((char*)pointer - MEMORY_BLOCK_SIZE);

    if (!blockToFree->isAllocated) {
        return; // Блок уже свободен, ничего делать не нужно
    }

    blockToFree->isAllocated = 0; // Помечаем его как свободный

    // Попытка объединить с предыдущим блоком, если он свободен
    if (blockToFree->prevBlock && !blockToFree->prevBlock->isAllocated) {
        blockToFree->prevBlock->blockSize += blockToFree->blockSize + MEMORY_BLOCK_SIZE;
        blockToFree->prevBlock->nextBlock = blockToFree->nextBlock;
        if (blockToFree->nextBlock) {
            blockToFree->nextBlock->prevBlock = blockToFree->prevBlock;
        }
        blockToFree = blockToFree->prevBlock;
    }

    // Попытка объединить с следующим блоком, если он свободен
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
