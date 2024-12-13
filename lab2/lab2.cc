#include <stdlib.h>
#include <string.h>
#include "memallocator.h"

typedef struct block_t {
    int size;          // size of the memory block
    int free;          // is the block free
    struct block_t* next;
    struct block_t* prev;
} block_t;

static block_t* ListOfBlocks = NULL;
static void* MemoryPool = NULL;
static int TotalMemory = 0;

int meminit(void* pMemory, int size) {
    if (!pMemory || size < memgetminimumsize())
        return 0;

    MemoryPool = pMemory;
    TotalMemory = size;

    ListOfBlocks = (block_t*)pMemory;
    ListOfBlocks->size = size - sizeof(block_t);
    ListOfBlocks->free = 1;
    ListOfBlocks->next = NULL;
    ListOfBlocks->prev = NULL;
    return 1;
}

void memdone() {
    ListOfBlocks = NULL;
    MemoryPool = NULL;
    TotalMemory = 0;
}

void* memalloc(int size) {
    if (size <= 0 || !MemoryPool)
        return NULL;

    block_t* t = ListOfBlocks;
    while (t) {
        if (t->free && t->size >= size) {
            if (t->size >= size + sizeof(block_t)) {
                block_t* NewBlock = (block_t*)((char*)t + sizeof(block_t) + size);
                NewBlock->size = t->size - size - sizeof(block_t);
                NewBlock->free = 1;
                NewBlock->next = t->next;
                NewBlock->prev = t;

                if (t->next) t->next->prev = NewBlock;
                t->size = size;
                t->next = NewBlock;
            }

            t->free = 0;
            return (char*)t + sizeof(block_t);
        }
        t = t->next;
    }

    return NULL;
}

void memfree(void* p) {
    if (!p || !MemoryPool)
        return;

    block_t* block = (block_t*)((char*)p - sizeof(block_t));
    block->free = 1;

    if (block->next && block->next->free) {
        block->size += block->next->size + sizeof(block_t);
        block->next = block->next->next;
        if (block->next) block->next->prev = block;
    }

    if (block->prev && block->prev->free) {
        block->prev->size += block->size + sizeof(block_t);
        block->prev->next = block->next;
        if (block->next) block->next->prev = block->prev;
        block = block->prev;
    }
}

int memgetminimumsize() {
    return sizeof(block_t);
}

int memgetblocksize() {
    return sizeof(block_t);
}