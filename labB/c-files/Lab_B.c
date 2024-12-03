#include <stdlib.h>
#include <stddef.h>
#include "memallocator.h"

typedef struct Block
{
    size_t size;
    char free;//0 - free, 1 - reserved
    struct Block*next;
    struct Block*prev;
}Block;

#define BLOCKSIZE sizeof(Block)

Block* head = NULL;
void * memory = NULL;
size_t mem_size = 0;

int meminit(void *pMemory, int size){//1 - error
    if(pMemory == NULL || size <= BLOCKSIZE){
        return 1;
    }

    memory = pMemory;
    mem_size = size;

    head = (Block*)pMemory;
    head->size = size - BLOCKSIZE;
    head->free = 0;
    head->prev = NULL;
    head->next = NULL;

    return 0;
}

void memdone(){
    memory = NULL;
    head = NULL;
    mem_size = 0;

    return;
}

void *memalloc(int size) {
    if (size <= 0 || !memory) {
        return NULL;
    }

    Block* best = NULL;
    Block* t = head;

    while (t) {
        if (!t->free && t->size >= size) {
            if (!best || best->size > t->size) {
                best = t;
            }
        }
        t = t->next;
    }

    if (!best) {
        return NULL;
    }

    if (best->size >= size + BLOCKSIZE) {
        Block* new_block = (Block*)((char*)best + BLOCKSIZE + size);
        new_block->size = best->size - size - BLOCKSIZE;
        new_block->free = 0;
        new_block->prev = best;
        new_block->next = best->next;

        if (best->next) {
            best->next->prev = new_block;
        }

        best->next = new_block;
        best->size = size;
    }

    best->free = 1;
    return (void*)((char*)best + BLOCKSIZE);
}

void memfree(void *p) {
    if (!p || !memory) {
        return;
    }

    Block* t = (Block*)((char*)p - BLOCKSIZE);

    if (!t->free) {
        return;
    }

    t->free = 0;

    if (t->prev && !t->prev->free) {
        t->prev->size += t->size + BLOCKSIZE;
        t->prev->next = t->next;
        if (t->next) {
            t->next->prev = t->prev;
        }
        t = t->prev;
    }

    if (t->next && !t->next->free) {
        t->size += t->next->size + BLOCKSIZE;
        t->next = t->next->next;
        if (t->next) {
            t->next->prev = t;
        }
    }
}

int memgetminimumsize(){
    return BLOCKSIZE;
}

int memgetblocksize(){
    return BLOCKSIZE;
}
