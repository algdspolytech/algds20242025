#include <stddef.h>
#include "memallocator.h"

typedef struct MemoryBlock {
    size_t blockSize; // ������ ����� ������
    char isAllocated; // ������ ����� (�������/��������)
    struct MemoryBlock* nextBlock; // ��������� �� ��������� ����
    struct MemoryBlock* prevBlock; // ��������� �� ���������� ����
} MemoryBlock;

#define MEMORY_BLOCK_SIZE sizeof(MemoryBlock)

MemoryBlock* memoryHead = NULL; // ��������� �� ������ ������ ������
void* allocatedMemory = NULL; // ��������� �� ���� ��� ������
size_t totalMemSize = 0; // ����� ������ ���� ������

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= MEMORY_BLOCK_SIZE) {
        return 1;
    }

    allocatedMemory = pMemory;
    totalMemSize = size;

    // ��������� ������������� ������� ����� � ���� ������
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
        return NULL; // �������� ������
    }

    MemoryBlock* currentBlock = memoryHead;

    // ��������� "������ ����������" - ����� ������ ��������� ���� � ����������� ��������
    while (currentBlock) {
        if (!currentBlock->isAllocated && currentBlock->blockSize >= size) {
            // ���� ������, ���������, ����� �� ��������� ���
            if (currentBlock->blockSize >= size + MEMORY_BLOCK_SIZE) {
                // ��������� ����, �������� ����� ������
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

            // �������� ������� ���� ��� �������
            currentBlock->isAllocated = 1;
            return (void*)((char*)currentBlock + MEMORY_BLOCK_SIZE);
        }
        currentBlock = currentBlock->nextBlock;
    }

    return NULL; // ��� ����������� �����
}

void memfree(void* pointer) {
    if (!pointer || !allocatedMemory) {
        return;
    }

    // �������� ��������� �� ��������� ����� ����� ��������
    MemoryBlock* blockToFree = (MemoryBlock*)((char*)pointer - MEMORY_BLOCK_SIZE);

    if (!blockToFree->isAllocated) {
        return; // ���� ��� ��������, ������ ������ �� �����
    }

    blockToFree->isAllocated = 0; // �������� ��� ��� ���������

    // ������� ���������� � ���������� ������, ���� �� ��������
    if (blockToFree->prevBlock && !blockToFree->prevBlock->isAllocated) {
        blockToFree->prevBlock->blockSize += blockToFree->blockSize + MEMORY_BLOCK_SIZE;
        blockToFree->prevBlock->nextBlock = blockToFree->nextBlock;
        if (blockToFree->nextBlock) {
            blockToFree->nextBlock->prevBlock = blockToFree->prevBlock;
        }
        blockToFree = blockToFree->prevBlock;
    }

    // ������� ���������� � ��������� ������, ���� �� ��������
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
