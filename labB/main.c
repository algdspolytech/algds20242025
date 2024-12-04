#include <stdlib.h>
#include <stddef.h>
#include "memallocator.h"

typedef struct block
{
    struct block* next;
    struct block* prev;
    int size;
    int free;
    
}block;


block* head = NULL;
void* memory = NULL;
int mem_size = 0;

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= sizeof(block)) {
        return 1;
    }

    memory = pMemory;
    mem_size = size;

    head = (block*)pMemory;
    head->size = size - sizeof(block);
    head->free = 0;
    head->prev = NULL;
    head->next = NULL;

    return 0;
}

void memdone() {
    memory = NULL;
    head = NULL;
    mem_size = 0;

    return;
}

void* memalloc(int size) {
    if (size <= 0 || !memory) {
        return NULL;
    }

    block* best = NULL;
    block* tmp = head;

    while (tmp) {
        if (!tmp->free && tmp->size >= size) {
            if (!best || best->size > tmp->size) {
                best = tmp;
            }
        }
        tmp = tmp->next;
    }

    if (!best) {
        return NULL;
    }

    if (best->size >= size + sizeof(block)) {
        block* new_block = (block*)((char*)best + sizeof(block) + size);
        new_block->size = best->size - size - sizeof(block);
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
    return (void*)((char*)best + sizeof(block));
}

void memfree(void* p) {
    if (!p || !memory) {
        return;
    }

    block* t = (block*)((char*)p - sizeof(block));

    if (!t->free) {
        return;
    }

    t->free = 0;

    if (t->prev && !t->prev->free) {
        t->prev->size += t->size + sizeof(block);
        t->prev->next = t->next;
        if (t->next) {
            t->next->prev = t->prev;
        }
        t = t->prev;
    }

    if (t->next && !t->next->free) {
        t->size += t->next->size + sizeof(block);
        t->next = t->next->next;
        if (t->next) {
            t->next->prev = t;
        }
    }
}

int memgetminimumsize() {
    return sizeof(block);
}

int memgetblocksize() {
    return sizeof(block);
}