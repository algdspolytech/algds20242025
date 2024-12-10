#include <stdlib.h>
#include <string.h>
#include "memallocator.h" // Include if provided

typedef struct Block {
    int size;                // Block size
    int is_free;             // Free flag: 1 if free, 0 if allocated
    struct Block* next;      // Pointer to the next block
} Block;

static Block* free_list = NULL;
static void* memory_pool = NULL;
static int total_memory = 0;

int memgetminimumsize() {
    return sizeof(Block);
}

int memgetblocksize() {
    return sizeof(Block);
}

int meminit(void* pMemory, int size) {
    if (!pMemory || size < memgetminimumsize()) {
        return 0; // Failure due to insufficient memory
    }

    memory_pool = pMemory;
    total_memory = size;

    // Initialize the first free block
    free_list = (Block*)pMemory;
    free_list->size = size - sizeof(Block);
    free_list->is_free = 1;
    free_list->next = NULL;

    return 1; // Success
}

void memdone() {
    memory_pool = NULL;
    total_memory = 0;
    free_list = NULL;
}

void* memalloc(int size) {
    if (size <= 0 || !memory_pool) {
        return NULL;
    }

    Block* current = free_list;

    while (current) {
        if (current->is_free && current->size >= size) {
            if (current->size >= size + sizeof(Block)) {
                // Split the block
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->is_free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            current->is_free = 0; // Mark as allocated
            return (char*)current + sizeof(Block);
        }
        current = current->next;
    }

    return NULL; // No suitable block found
}

void memfree(void* p) {
    if (!p || !memory_pool) {
        return;
    }

    Block* block = (Block*)((char*)p - sizeof(Block));
    block->is_free = 1;

    // Coalesce with next block if free
    if (block->next && block->next->is_free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
    }

    // Coalesce with previous block if free
    Block* prev = NULL;
    Block* current = free_list;
    while (current && current != block) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        // Block not found; possible error
        return;
    }

    if (prev && prev->is_free) {
        // Coalesce with previous block
        prev->size += block->size + sizeof(Block);
        prev->next = block->next;
        block = prev; // Update 'block' to the coalesced block
    }
    else if (!prev) {
        // Block is the first block; nothing to do
    }
}