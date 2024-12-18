#include <stdlib.h>
#include <stddef.h>
#include "memallocator.h"

typedef struct MemoryBlock {
    struct MemoryBlock* next_block;
    struct MemoryBlock* prev_block;
    int block_size;
    int is_free;
} MemoryBlock;

MemoryBlock* block_list_head = NULL;
void* allocated_memory = NULL;
int total_memory_size = 0;

int meminit(void* block_memory, int size) {
    if (block_memory == NULL || size <= sizeof(MemoryBlock)) {
        return 1;
    }
    allocated_memory = block_memory;
    total_memory_size = size;
    block_list_head = (MemoryBlock*)block_memory;
    block_list_head->block_size = size - sizeof(MemoryBlock);
    block_list_head->is_free = 0;
    block_list_head->prev_block = NULL;
    block_list_head->next_block = NULL;

    return 0;
}

void memdone() {
    allocated_memory = NULL;
    block_list_head = NULL;
    total_memory_size = 0;
}

void* memalloc(int size) {
    if (size <= 0 || !allocated_memory) {
        return NULL;
    }
    MemoryBlock* best_fit = NULL;
    MemoryBlock* current_block = block_list_head;
    while (current_block) {
        if (!current_block->is_free && current_block->block_size >= size) {
            if (!best_fit || best_fit->block_size > current_block->block_size) {
                best_fit = current_block;
            }
        }
        current_block = current_block->next_block;
    }
    if (!best_fit) {
        return NULL;
    }
    if (best_fit->block_size >= size + sizeof(MemoryBlock)) {
        MemoryBlock* new_block = (MemoryBlock*)((char*)best_fit + sizeof(MemoryBlock) + size);
        new_block->block_size = best_fit->block_size - size - sizeof(MemoryBlock);
        new_block->is_free = 0;
        new_block->prev_block = best_fit;
        new_block->next_block = best_fit->next_block;

        if (best_fit->next_block) {
            best_fit->next_block->prev_block = new_block;
        }

        best_fit->next_block = new_block;
        best_fit->block_size = size;
    }
    best_fit->is_free = 1;
    return (void*)((char*)best_fit + sizeof(MemoryBlock));
}

void memfree(void* ptr) {
    if (!ptr || !allocated_memory) {
        return;
    }
    MemoryBlock* block_to_free = (MemoryBlock*)((char*)ptr - sizeof(MemoryBlock));
    if (!block_to_free->is_free) {
        return;
    }
    block_to_free->is_free = 0;
    if (block_to_free->prev_block && !block_to_free->prev_block->is_free) {
        block_to_free->prev_block->block_size += block_to_free->block_size + sizeof(MemoryBlock);
        block_to_free->prev_block->next_block = block_to_free->next_block;
        if (block_to_free->next_block) {
            block_to_free->next_block->prev_block = block_to_free->prev_block;
        }
        block_to_free = block_to_free->prev_block;
    }
    if (block_to_free->next_block && !block_to_free->next_block->is_free) {
        block_to_free->block_size += block_to_free->next_block->block_size + sizeof(MemoryBlock);
        block_to_free->next_block = block_to_free->next_block->next_block;
        if (block_to_free->next_block) {
            block_to_free->next_block->prev_block = block_to_free;
        }
    }
}
int memgetminimumsize() {
    return sizeof(MemoryBlock);
}

int memgetblocksize() {
    return sizeof(MemoryBlock);
}
