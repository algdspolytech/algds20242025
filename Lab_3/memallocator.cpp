#include "memallocator.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Макросы для отладки
#ifdef MY_DEBUG_PRINT
#include <stdio.h>
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif

// Структура блока памяти
typedef struct MemoryBlock {
    int size;                    // Размер блока
    int is_free;                 // Флаг, указывает, свободен ли блок
    struct MemoryBlock* next;    // Указатель на следующий блок
    struct MemoryBlock* prev;    // Указатель на предыдущий блок
} MemoryBlock;

// Указатель на начало памяти
static void* memory_pool = NULL;
static int memory_pool_size = 0;

// Указатель на первый блок (список свободных блоков)
static MemoryBlock* free_list = NULL;

// Минимальный размер памяти для работы аллокатора
int memgetminimumsize() {
    return sizeof(MemoryBlock);
}

// Размер служебной информации для каждого блока
int memgetblocksize() {
    return sizeof(MemoryBlock);
}

// Инициализация аллокатора памяти
int meminit(void* pMemory, int size) {
    if (!pMemory || size < memgetminimumsize()) {
        return 0; // Недостаточный объем памяти
    }

    memory_pool = pMemory;
    memory_pool_size = size;

    // Инициализируем первый блок
    free_list = (MemoryBlock*)pMemory;
    free_list->size = size - sizeof(MemoryBlock);
    free_list->is_free = 1;
    free_list->next = NULL;
    free_list->prev = NULL;

    return 1; // Успешная инициализация
}

// Освобождение ресурсов (если требуется)
void memdone() {
    memory_pool = NULL;
    memory_pool_size = 0;
    free_list = NULL;
}

// Выделение памяти
void* memalloc(int size) {
    if (size <= 0 || !memory_pool) {
        return NULL; // Неверный запрос
    }

    MemoryBlock* current = free_list;

    // Реализация стратегии "Следующий подходящий"
    while (current) {
        if (current->is_free && current->size >= size) {
            // Найден подходящий блок

            // Если текущий блок больше, чем требуется, разделяем его
            if (current->size >= size + sizeof(MemoryBlock)) {
                MemoryBlock* new_block = (MemoryBlock*)((uint8_t*)current + sizeof(MemoryBlock) + size);
                new_block->size = current->size - size - sizeof(MemoryBlock);
                new_block->is_free = 1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) {
                    current->next->prev = new_block;
                }

                current->next = new_block;
                current->size = size;
            }

            current->is_free = 0;
            return (void*)((uint8_t*)current + sizeof(MemoryBlock));
        }

        current = current->next;
    }

    return NULL; // Нет подходящего блока
}

// Освобождение памяти
void memfree(void* p) {
    if (!p || !memory_pool) {
        return; // Неверный указатель
    }

    MemoryBlock* block = (MemoryBlock*)((uint8_t*)p - sizeof(MemoryBlock));
    block->is_free = 1;

    // Слияние с соседними свободными блоками
    if (block->next && block->next->is_free) {
        block->size += sizeof(MemoryBlock) + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }

    if (block->prev && block->prev->is_free) {
        block->prev->size += sizeof(MemoryBlock) + block->size;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
    }
}