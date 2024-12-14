#include <stdlib.h>
#include <stddef.h>
#include "memallocator.h"

typedef struct block {
    struct block* next;
    int size;
    int free;
} block;

block* head = NULL;
block* last_alloc = NULL;
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
    head->next = NULL;

    last_alloc = head;
    return 0;
}

void memdone() {
    memory = NULL;
    head = NULL;
    last_alloc = NULL;
    mem_size = 0;
}

void* memalloc(int size) {
    if (size <= 0 || !memory) {
        return NULL;
    }

    block* tmp = last_alloc ? last_alloc->next : head;
    block* start = tmp;

    do {
        if (!tmp) {
            tmp = head;
        }
        if (!tmp->free && tmp->size >= size) {
            break;
        }
        tmp = tmp->next;
    } while (tmp != start);

    if (!tmp || tmp->free || tmp->size < size) {
        return NULL;
    }

    if (tmp->size >= size + sizeof(block)) {
        block* new_block = (block*)((char*)tmp + sizeof(block) + size);
        new_block->size = tmp->size - size - sizeof(block);
        new_block->free = 0;
        new_block->next = tmp->next;

        tmp->next = new_block;
        tmp->size = size;
    }

    tmp->free = 1;
    last_alloc = tmp;
    return (void*)((char*)tmp + sizeof(block));
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

    if (t->next && !t->next->free) {
        t->size += t->next->size + sizeof(block);
        t->next = t->next->next;
    }

    block* prev = head;
    while (prev && prev->next != t) {
        prev = prev->next;
    }

    if (prev && !prev->free) {
        prev->size += t->size + sizeof(block);
        prev->next = t->next;
    }
}

int memgetminimumsize() {
    return sizeof(block);
}

int memgetblocksize() {
    return sizeof(block);
}
