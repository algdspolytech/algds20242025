#include "memallocator.h"
#include <stdlib.h>
#include <string.h>

typedef struct Block {
    int size;                // Размер блока
    int is_free;             // Флаг, указывающий, свободен ли блок
    struct Block* next;      // Указатель на следующий блок
} Block;

static Block* free_list = NULL; // Список свободных блоков
static void* memory_pool = NULL;
static int total_memory = 0;

// Минимальный размер памяти для одного блока
int memgetminimumsize() {
    return sizeof(Block);
}

// Дополнительный размер данных на каждый блок
int memgetblocksize() {
    return sizeof(Block);
}

// Инициализация системы памяти
int meminit(void* pMemory, int size) {
    if (!pMemory || size < memgetminimumsize()) {
        return 0; // Недостаточный объем памяти
    }

    memory_pool = pMemory;
    total_memory = size;

    // Инициализация первого блока
    free_list = (Block*)pMemory;
    free_list->size = size - sizeof(Block);
    free_list->is_free = 1;
    free_list->next = NULL;

    return 1; // Успех
}

// Завершение работы с памятью
void memdone() {
    memory_pool = NULL;
    total_memory = 0;
    free_list = NULL;
}

// Выделение памяти
void* memalloc(int size) {
    if (size <= 0) {
        return NULL;
    }

    Block* current = free_list;
    Block* prev = NULL;

    while (current) {
        if (current->is_free && current->size >= size) {
            // Если блок подходит, разделяем его при необходимости
            if (current->size >= size + sizeof(Block) + 1) {
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->is_free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            current->is_free = 0; // Помечаем блок как занятый
            return (char*)current + sizeof(Block);
        }

        prev = current;
        current = current->next;
    }

    return NULL; // Нет подходящего блока
}

// Освобождение памяти
void memfree(void* p) {
    if (!p) {
        return;
    }

    Block* block = (Block*)((char*)p - sizeof(Block));
    block->is_free = 1;

    // Слияние с последующим блоком, если он свободен
    if (block->next && block->next->is_free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
    }

    // Слияние с предыдущим блоком, если он свободен
    Block* current = free_list;
    while (current && current->next != block) {
        current = current->next;
    }

    if (current && current->is_free) {
        current->size += block->size + sizeof(Block);
        current->next = block->next;
    }
}