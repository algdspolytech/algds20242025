#include <stdlib.h>
#include <string.h>
#include "memallocator.h"

typedef struct Block {
    int size;
    int free;
    struct Block* next;
    struct Block* prev;
} Block;

static Block* list_of_blocks = NULL;
static void* memory_pool = NULL;
static int total_memory = 0;

int meminit(void* pMemory, int size) {
    if (!pMemory || size < memgetminimumsize())
        return 0;

    memory_pool = pMemory;
    total_memory = size;

    list_of_blocks = (Block*)pMemory;
    list_of_blocks->size = size - sizeof(Block);
    list_of_blocks->free = 1;
    list_of_blocks->next = NULL;
    list_of_blocks->prev = NULL;
    return 1;
}

void memdone() {
    list_of_blocks = NULL;
    memory_pool = NULL;
    total_memory = 0;
}

void* memalloc(int size) {
    if (size <= 0 || !memory_pool)
        return NULL;

    Block* tmp = list_of_blocks;
    while (tmp) {
        if (tmp->free && tmp->size >= size) {
            if (tmp->size >= size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)tmp + sizeof(Block) + size);
                new_block->size = tmp->size - size - sizeof(Block);
                new_block->free = 1;
                new_block->next = tmp->next;
                new_block->prev = tmp;

                if (tmp->next) tmp->next->prev = new_block;
                tmp->size = size;
                tmp->next = new_block;
            }

            tmp->free = 0;
            return (char*)tmp + sizeof(Block);
        }
        tmp = tmp->next;
    }

    return NULL;
}

void memfree(void* p) {
    if (!p || !memory_pool)
        return;

    Block* block = (Block*)((char*)p - sizeof(Block));
    block->free = 1;

    if (block->next && block->next->free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
        if (block->next) block->next->prev = block;
    }

    if (block->prev && block->prev->free) {
        block->prev->size += block->size + sizeof(Block);
        block->prev->next = block->next;
        if (block->next) block->next->prev = block->prev;
        block = block->prev;
    }
}

int memgetminimumsize() {
    return sizeof(Block);
}

int memgetblocksize() {
    return sizeof(Block);
}
