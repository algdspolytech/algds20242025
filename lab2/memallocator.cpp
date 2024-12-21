#include "memallocator.h"

#include <stddef.h>
#include <stdbool.h>

// Структура для хранения метаданных блока памяти
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

// Инициализация системы памяти с блоком памяти memoryPointer.
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

// Здесь можно реализовать проверки утечек памяти
void memdone() {
    _memoryPool = NULL;
    _poolSize = 0;
}

// Выделение блока памяти размером 'size'.
// Возвращает указатель на блок памяти в случае успеха, 0 в противном случае
void* memalloc(int size) {
    if (size <= 0 || !_memoryPool)
        return 0;

    MemoryChunk* currentChunk = _memoryPool;
    MemoryChunk* availableChunk = NULL; // Блок для получения памяти
    int counter = 2;

    // Проход по всем блокам памяти
    while (currentChunk != NULL) {
        if (currentChunk->blockSize >= size && currentChunk->isFree && counter > 0) {
            availableChunk = currentChunk;

            counter--;

            if (!counter) // Ищем блок, пока счетчик не равен 0
                break;
        }

        currentChunk = currentChunk->nextChunk;
    }

    // Проверка, нашли ли мы действительный блок памяти
    if (availableChunk == NULL)
        return 0;

    // В противном случае выделяем память из этого блока
    currentChunk = availableChunk;
    currentChunk->isFree = false;

    // Если недостаточно памяти для создания дополнительных блоков
    if (currentChunk->blockSize <= size + sizeof(MemoryChunk))
        return currentChunk->memoryPointer;

    // Если достаточно памяти для создания других блоков
    // Создаем новый блок
    MemoryChunk* newChunk = (MemoryChunk*)((char*)currentChunk->memoryPointer + size);
    newChunk->memoryPointer = (void*)((char*)currentChunk->memoryPointer + size + sizeof(MemoryChunk));
    newChunk->blockSize = currentChunk->blockSize - size - sizeof(MemoryChunk);
    newChunk->isFree = true;
    newChunk->prevChunk = currentChunk;

    newChunk->nextChunk = currentChunk->nextChunk;
    if (currentChunk->nextChunk)
        currentChunk->nextChunk->prevChunk = newChunk;

    // Возвращаем старый блок
    currentChunk->blockSize = size;
    currentChunk->nextChunk = newChunk;

    return currentChunk->memoryPointer;
}

// Освобождение памяти, ранее выделенной с помощью memalloc
void memfree(void* pointer) {
    if (!_memoryPool || pointer < _memoryPool->memoryPointer || pointer >((char*)_memoryPool->memoryPointer + _poolSize))
        return;

    MemoryChunk* currentChunk = (MemoryChunk*)((char*)pointer - sizeof(MemoryChunk));

    currentChunk->isFree = true;

    // Проверяем, свободен ли следующий или предыдущий блок памяти
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

// Возвращает минимальный размер в байтах пула памяти для выделения блока на 0 байт
// пример использования:
// void *p   = 0;
// void *ptr = malloc(memgetminimumsize() + 1);
// meminit(ptr, memgetminimumsize() + 1)
// p = memalloc(1); // Успех!
// memfree(p);
// memdone();
// free(ptr);
int memgetminimumsize() {
    return (int)sizeof(MemoryChunk);
}

// Возвращает размер в байтах дополнительной информации на каждое выделение
// пример использования:
// void *p1 = 0, *p2 = 0;
// int  memsize= memgetminimumsize() + memgetblocksize() + 2;
// void *ptr= malloc(memsize);
// meminit(ptr, memsize)
// p1= memalloc(1); // Успех!
// p2= memalloc(1); // Успех!
// memfree(p2);
// memfree(p1);
// memdone();
// free(ptr);
int memgetblocksize() {
    return (int)sizeof(MemoryChunk);
}
