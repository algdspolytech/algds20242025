#include "memallocator.h"

#include <stddef.h>
#include <stdbool.h>

// ��������� ��� �������� ���������� ����� ������
struct MemoryChunk {
    void* memoryPointer;
    int blockSize;

    bool isFree;

    struct MemoryChunk* nextChunk;
    struct MemoryChunk* prevChunk;
};
typedef struct MemoryChunk MemoryChunk;

MemoryChunk* _memoryPool;
int _poolSize;

// ������������� ������� ������ � ������ ������ memoryPointer.
int meminit(void* memoryPointer, int size) {
    if (!memoryPointer || size < sizeof(MemoryChunk))
        return 0;

    _memoryPool = (MemoryChunk*)memoryPointer;
    _poolSize = size;

    _memoryPool->memoryPointer = (void*)((char*)memoryPointer + sizeof(MemoryChunk));
    _memoryPool->blockSize = size - sizeof(MemoryChunk);
    _memoryPool->isFree = true;
    _memoryPool->nextChunk = NULL;
    _memoryPool->prevChunk = NULL;

    return 0;
}

// ����� ����� ����������� �������� ������ ������
void memdone() {
    _memoryPool = NULL;
    _poolSize = 0;
}

// ��������� ����� ������ �������� 'size'.
// ���������� ��������� �� ���� ������ � ������ ������, 0 � ��������� ������
void* memalloc(int size) {
    if (size <= 0 || !_memoryPool)
        return 0;

    MemoryChunk* currentChunk = _memoryPool;
    MemoryChunk* availableChunk = NULL; // ���� ��� ��������� ������
    int counter = 2;

    // ������ �� ���� ������ ������
    while (currentChunk != NULL) {
        if (currentChunk->blockSize >= size && currentChunk->isFree && counter > 0) {
            availableChunk = currentChunk;

            counter--;

            if (!counter) // ���� ����, ���� ������� �� ����� 0
                break;
        }

        currentChunk = currentChunk->nextChunk;
    }

    // ��������, ����� �� �� �������������� ���� ������
    if (availableChunk == NULL)
        return 0;

    // � ��������� ������ �������� ������ �� ����� �����
    currentChunk = availableChunk;
    currentChunk->isFree = false;

    // ���� ������������ ������ ��� �������� �������������� ������
    if (currentChunk->blockSize <= size + sizeof(MemoryChunk))
        return currentChunk->memoryPointer;

    // ���� ���������� ������ ��� �������� ������ ������
    // ������� ����� ����
    MemoryChunk* newChunk = (MemoryChunk*)((char*)currentChunk->memoryPointer + size);
    newChunk->memoryPointer = (void*)((char*)currentChunk->memoryPointer + size + sizeof(MemoryChunk));
    newChunk->blockSize = currentChunk->blockSize - size - sizeof(MemoryChunk);
    newChunk->isFree = true;
    newChunk->prevChunk = currentChunk;

    newChunk->nextChunk = currentChunk->nextChunk;
    if (currentChunk->nextChunk)
        currentChunk->nextChunk->prevChunk = newChunk;

    // ���������� ������ ����
    currentChunk->blockSize = size;
    currentChunk->nextChunk = newChunk;

    return currentChunk->memoryPointer;
}

// ������������ ������, ����� ���������� � ������� memalloc
void memfree(void* pointer) {
    if (!_memoryPool || pointer < _memoryPool->memoryPointer || pointer >((char*)_memoryPool->memoryPointer + _poolSize))
        return;

    MemoryChunk* currentChunk = (MemoryChunk*)((char*)pointer - sizeof(MemoryChunk));

    currentChunk->isFree = true;

    // ���������, �������� �� ��������� ��� ���������� ���� ������
    if (currentChunk->nextChunk) {
        if (currentChunk->nextChunk->isFree) {
            currentChunk->blockSize += currentChunk->nextChunk->blockSize + sizeof(MemoryChunk);
            currentChunk->nextChunk = currentChunk->nextChunk->nextChunk;

            if (currentChunk->nextChunk)
                currentChunk->nextChunk->prevChunk = currentChunk;
        }
    }

    if (currentChunk->prevChunk) {
        if (currentChunk->prevChunk->isFree) {
            currentChunk->prevChunk->blockSize += currentChunk->blockSize + sizeof(MemoryChunk);
            currentChunk->prevChunk->nextChunk = currentChunk->nextChunk;

            if(currentChunk->nextChunk)
                currentChunk->nextChunk->prevChunk = currentChunk->prevChunk;
        }
    }
}

// ���������� ����������� ������ � ������ ���� ������ ��� ��������� ����� �� 0 ����
// ������ �������������:
// void *p   = 0;
// void *ptr = malloc(memgetminimumsize() + 1);
// meminit(ptr, memgetminimumsize() + 1)
// p = memalloc(1); // �����!
// memfree(p);
// memdone();
// free(ptr);
int memgetminimumsize() {
    return (int)sizeof(MemoryChunk);
}

// ���������� ������ � ������ �������������� ���������� �� ������ ���������
// ������ �������������:
// void *p1 = 0, *p2 = 0;
// int  memsize= memgetminimumsize() + memgetblocksize() + 2;
// void *ptr= malloc(memsize);
// meminit(ptr, memsize)
// p1= memalloc(1); // �����!
// p2= memalloc(1); // �����!
// memfree(p2);
// memfree(p1);
// memdone();
// free(ptr);
int memgetblocksize() {
    return (int)sizeof(MemoryChunk);
}
