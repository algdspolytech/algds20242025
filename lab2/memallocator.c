#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Block {
    struct Block* prev;
    struct Block* next;
    size_t size;         
    bool is_free;             
} Block;

static Block* block = NULL;
static size_t size_of_pool = 0;
static void* pool = NULL;

int meminit(void* pMemory, int size) {
    if (!pMemory || size <= sizeof(Block)) { 
        return -1; 
    }

    pool = pMemory;
    size_of_pool = size;
    block = (Block*)pool;
    
    block->prev = NULL;
    block->next = NULL;
    block->size = size - sizeof(Block);
    block->is_free = true;

    return 0;
}

void memdone() {
    pool = NULL;
    block = NULL;
    size_of_pool = 0;
}

void* memalloc(int size) {
    if (size <= 0) {
        return NULL;
    }

    Block* current = block;
    int direction = 1;
    while (current) {
        if (current->is_free && current->size >= size) {
            if (current->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;
                new_block->prev = current;
                new_block->is_free = true;

                if (current->next) {
                    current->next->prev = new_block;
                }
                current->next = new_block;
                current->size = size;
            }

            current->is_free = false;
            return (char*)current + sizeof(Block);
        }
        if (direction == 1) {
            current = current->next;
        }
        else {
            current = current->prev;
        }
        if (!current && direction==1) {
            current = block;
            while (current && current->next) {
                current = current->next;
            }
            direction = 0;
        }
    }

    return NULL;
}

void memfree(void* p) {
    if (!p || !pool) {
        return;
    }

    Block* block = (Block*)((char*)p - sizeof(Block));
    block->is_free = true;

    if (block->prev && block->prev->is_free) {
        block->prev->size += block->size + sizeof(Block);
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
        block = block->prev;
    }

    if (block->next && block->next->is_free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }
}

int memgetminimumsize() {
    return sizeof(Block);
}

int memgetblocksize() {
    return sizeof(Block);
}
