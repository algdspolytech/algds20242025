#include "memallocator.h"
#include <stddef.h>
#include <string.h>


static Block* head = NULL; // Начало списка блоков
static void* memory_pool = NULL; // Указатель на память для работы
static int pool_size = 0; // Размер выделенной памяти

int memgetminimumsize() { 
    return (int)sizeof(Block); 
}

int memgetblocksize() { 
    return (int)sizeof(Block); 
}

int meminit(void* pMemory, int size) {
    if (!pMemory || size <= memgetminimumsize()) {
        return 0;
    }

    memory_pool = pMemory;
    pool_size = size;

    // Инициализация первого блока
    head = (Block*)pMemory;
    head->size = size - memgetminimumsize();
    head->free = 1;
    head->next = NULL;
    head->prev = NULL;

    return 1;
}

void memdone() {
    head = NULL;
    memory_pool = NULL;
    pool_size = 0;
}

void* memalloc(int size) {
    if (size <= 0) {
        return NULL;
    }

    Block* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            // "Первый подходящий" найден
            if (current->size > size + (int)memgetminimumsize()) {
                // Разделяем блок
                Block* new_block =
                    (Block*)((char*)current + memgetminimumsize() + size);
                new_block->size = current->size - size - memgetminimumsize();
                new_block->free = 1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) {
                    current->next->prev = new_block;
                }

                current->next = new_block;
                current->size = size;
            }

            current->free = 0;
            return (char*)current + memgetminimumsize();
        }

        current = current->next;
    }

    return NULL; // Нет подходящего блока
}

void memfree(void* p) {
    if (!p || p < memory_pool || p >= (char*)memory_pool + pool_size) {
        return;
    }

    Block* block = (Block*)((char*)p - memgetminimumsize());
    block->free = 1;

    // Слияние с соседними свободными блоками
    if (block->next && block->next->free) {
        block->size += memgetminimumsize() + block->next->size;
        block->next = block->next->next;

        if (block->next) {
            block->next->prev = block;
        }
    }

    if (block->prev && block->prev->free) {
        block->prev->size += memgetminimumsize() + block->size;
        block->prev->next = block->next;

        if (block->next) {
            block->next->prev = block->prev;
        }
    }
}

