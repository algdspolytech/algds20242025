#include <stdlib.h>
#include <stddef.h>
#include "memallocator.h"

typedef struct Block {
    struct Block* next;
    int size;
    int is_free;
} Block;

Block* free_list = NULL;    // Односвязный список свободных блоков
void* memory_pool = NULL;   // Указатель на начало памяти
int memory_pool_size = 0;   // Размер всей памяти
Block* last_allocated = NULL; // Последний выделенный блок (для Next Fit)

#define BLOCK_SIZE sizeof(Block)   // Размер структуры блока

// Инициализация памяти
int meminit(void* pMemory, int size) 
{
    if (pMemory == NULL || size <= BLOCK_SIZE) 
    {
        return 1;  // Память не была инициализирована из-за недостаточного размера
    }

    memory_pool = pMemory;
    memory_pool_size = size;

    // Инициализируем первый свободный блок
    free_list = (Block*)pMemory;
    free_list->size = size - BLOCK_SIZE;
    free_list->next = NULL;
    free_list->is_free = 1;

    last_allocated = free_list;
    return 0;
}

// Завершаем работу с памятью
void memdone() 
{
    // Очистка структуры, если нужно
    free_list = NULL;
    memory_pool = NULL;
    last_allocated = NULL;
    memory_pool_size = 0;
}

void* memalloc(int size) 
{
    if (size <= 0 || !memory_pool) 
    {
        return NULL;
    }

    Block* current = last_allocated ? last_allocated->next : free_list;
    Block* start = current;

    do 
    {
        if (current == NULL) 
        {
            current = free_list;
        }
        if (current->is_free == 1 && current->size >= size) 
        {
            break;
        }
        current = current->next;
    } while (current != start);

    if (current == NULL || current->is_free == 0 || current->size < size) 
    {
        return NULL;
    }

    int remaining_size = current->size - size;
    if (remaining_size >= BLOCK_SIZE)
    {
        Block* new_block = (Block*)((char*)current + BLOCK_SIZE + size);
        new_block->size = remaining_size - BLOCK_SIZE;
        new_block->is_free = 1;
        new_block->next = current->next;

        current->size = size;
        current->next = new_block;
    }

    current->is_free = 0;
    last_allocated = current;

    return (void*)((char*)current + BLOCK_SIZE);
}


void memfree(void* p) 
{
    if (!p || !memory_pool) 
    {
        return;
    }

    Block* b = (Block*)((char*)p - BLOCK_SIZE);
    if (b->is_free == 1) 
    {
        return;
    }

    b->is_free = 1;

    if (b->next && b->next->is_free == 1) 
    {
        b->size += b->next->size + BLOCK_SIZE;
        b->next = b->next->next;
    }

    Block* prev = free_list;
    while (prev && prev->next != b) 
    {
        prev = prev->next;
    }

    if (prev && prev->is_free == 1) 
    {
        prev->size += b->size + BLOCK_SIZE;
        prev->next = b->next;
    }
}

int memgetminimumsize() 
{
    return BLOCK_SIZE;
}

int memgetblocksize() 
{
    return BLOCK_SIZE;
}

