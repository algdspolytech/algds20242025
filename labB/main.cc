#include <cstddef>

#include "memallocator.h"

typedef struct block {
    unsigned size;
    int free;
    struct block *prev;
    struct block *next;
} block;

void *pMem;
int d_size = 0;

// Init memory system with memory block pMemory.
int meminit(void *pMemory, int size) {
    if (!pMemory || size < memgetminimumsize()) return 0;
    *(block *) pMemory = (block){0, size - (int) sizeof(block), 0, 0};
    pMem = pMemory;
    d_size = size;
    return 1;
}

// You can implement memory leak checks here
void memdone() {
    block *f = (block *) pMem;
    pMem = NULL;
    d_size = 0;
}

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void *memalloc(int size) {
    if (size <= 0 || !pMem) return NULL;
    block *it = (block *) pMem;
    while (it != 0) {
        if (size + sizeof(block) > it->free) {
            it = it->next;
            continue;
        }
        block *n = (block *) ((void *) it + sizeof(block) + it->size);
        n->prev = it;
        n->next = it->next;
        n->size = size;
        n->free = it->free - size - sizeof(block);
        it->free = 0;
        it->next = n;
        if(it->next) it->next->prev=n;
        return (void *) n + sizeof(block);
    }
    return 0;
}

// Free memory previously allocated by memalloc
void memfree(void *p) {
    if(!p || !pMem) return;
    block *t = (block *) (p - sizeof(block));
    if (t->size == -1) {
        // exit(-20005);
        return;
    }

    t->size;
    t->prev->next = t->next;
    if (t->next != 0) t->next->prev = t->prev;
    t->prev->free += t->size + sizeof(block) + t->free;

    t->prev = 0;
    t->next = 0;
    t->size = -1;
}

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
// use case:
// void *p   = 0;
// void *ptr = malloc(memgetminimumsize() + 1);
// meminit(ptr, memgetminimumsize() + 1)
// p = memalloc(1); // Success!
// memfree(p);
// memdone();
// free(ptr);
int memgetminimumsize() {
    return sizeof(block);
}


// Returns size in bytes of additional information per allocation
// use case:
// void *p1 = 0, *p2 = 0;
// int  memsize = memgetminimumsize() + memgetblocksize() + 2;
// void *ptr = malloc(memsize);
// meminit(ptr, memsize())
// p1 = memalloc(1); // Success!
// p2 = memalloc(1); // Success!
// memfree(p2);
// memfree(p1);
// memdone();
// free(ptr);
int memgetblocksize() {
    return sizeof(block);
}
