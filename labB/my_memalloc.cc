#include <stddef.h>
#include <stdlib.h>
#include "memallocator.h"

typedef struct Block {
    size_t size;
    char status;// 0 - free , 1 - reserved
    struct Block *next;
    struct Block *prev;
} Block;

#define BLOCK_SIZE sizeof(Block)

Block *first_block = NULL;
void *memory = NULL;
size_t mem_size = 0;

int meminit(void *pMemory, int size) {
    if(pMemory == NULL || size <= BLOCK_SIZE){
        return 1;
    }

    memory = pMemory;
    mem_size = size;

    first_block = (Block*)pMemory;
    first_block->size = size - BLOCK_SIZE;
    first_block->status = 0;
    first_block->prev = NULL;
    first_block->next = NULL;

    return 0;
}

void memdone() {
    first_block = NULL;
    mem_size = 0;
    memory = NULL;
    
    return;
}

void *memalloc(int size) {
        if (size <= 0 || !memory) {
        return NULL;
    }

    Block* best = NULL;
    Block* t = first_block;

    while (t) {
        if (!t->status && t->size >= size) {
            if (!best || best->size > t->size) {
                best = t;
            }
        }
        t = t->next;
    }

    if (!best) {
        return NULL;
    }

    if (best->size > size + BLOCK_SIZE) {
        Block* new_block = (Block*)((char*)best + BLOCK_SIZE + size);
        new_block->size = best->size - size - BLOCK_SIZE;
        new_block->status = 0;
        new_block->prev = best;
        new_block->next = best->next;

        if (best->next) {
            best->next->prev = new_block;
        }

        best->next = new_block;
        best->size = size;
    }

    best->status = 1;
    return (void*)((char*)best + BLOCK_SIZE);
}

void memfree(void *p) {
    if(!memory || !p) {
        return;
    }

    Block *temp = (Block*)((char*)p - BLOCK_SIZE);

    if(!temp->status) {
        return;
    }

    temp->status = 0;

    if(temp->prev && !temp->prev->status) {
        temp->prev->size += temp->size + BLOCK_SIZE;
        temp->prev->next = temp->next;
        if(temp->next) {
            temp->next->prev = temp->prev;
        }
        temp = temp->prev;
    }

    if(temp->next && !temp->next->status) {
        temp->size += temp->next->size + BLOCK_SIZE;
        temp->next = temp->next->next;
        if(temp->next) {
            temp->next->prev = temp;
        }
    }
}


int memgetminimumsize(){
    return BLOCK_SIZE;
}

int memgetblocksize(){
    return BLOCK_SIZE;
}
