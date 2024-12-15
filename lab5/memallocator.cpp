#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Узел для двухсвязного списка свободных блоков
typedef struct Block {
    size_t size;          // Размер блока
    int free;             // Свободен ли блок
    struct Block *prev;   // Указатель на предыдущий блок
    struct Block *next;   // Указатель на следующий блок
} Block;

#define BLOCK_SIZE sizeof(Block)

static void *memory_pool = NULL;
static Block *free_list = NULL; // Список свободных блоков
static size_t pool_total_size = 0;

int meminit(void *pMemory, int size) {
    if (!pMemory || size <= BLOCK_SIZE) return -1;

    memory_pool = pMemory;
    pool_total_size = size;

    free_list = (Block *)memory_pool;
    free_list->size = size - BLOCK_SIZE;
    free_list->free = 1;
    free_list->prev = NULL;
    free_list->next = NULL;

    return 0;
}

void memdone() {
    memory_pool = NULL;
    free_list = NULL;
    pool_total_size = 0;
}

void *memalloc(int size) {
    if (size <= 0) return NULL;

    Block *current = free_list;

    while (current) {
        if (current->free && current->size >= size) {
            if (current->size > size + BLOCK_SIZE) {
                Block *new_block = (Block *)((char *)current + BLOCK_SIZE + size);
                new_block->size = current->size - size - BLOCK_SIZE;
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
            return (char *)current + BLOCK_SIZE;
        }
        current = current->next;
    }

    return NULL;
}

void memfree(void *p) {
    if (!p || !memory_pool) return;

    Block *block = (Block *)((char *)p - BLOCK_SIZE);
    block->free = 1;

    if (block->prev && block->prev->free) {
        block->prev->size += block->size + BLOCK_SIZE;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
        block = block->prev;
    }

    if (block->next && block->next->free) {
        block->size += block->next->size + BLOCK_SIZE;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }
}

int memgetminimumsize() {
    return BLOCK_SIZE;
}

int memgetblocksize() {
    return BLOCK_SIZE;
}
