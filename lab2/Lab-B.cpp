#include "memallocator.h"

typedef struct MemoryBlock {
    int size;
    int is_free;
    struct MemoryBlock* next;
    struct MemoryBlock* prev;
} MemoryBlock;

static void* memory_start = 0;
static MemoryBlock* first_block = 0;

int initialize_memory(void* memory_area, int memory_size) {
    if (!memory_area || memory_size < sizeof(MemoryBlock)) {
        return 0;
    }

    memory_start = memory_area;
    first_block = (MemoryBlock*)memory_area;
    first_block->size = memory_size - sizeof(MemoryBlock);
    first_block->is_free = 1;
    first_block->next = 0;
    first_block->prev = 0;

    return 1;
}

void cleanup_memory() {
    memory_start = 0;
    first_block = 0;
}

void* allocate_memory(int request_size) {
    if (request_size <= 0 || !first_block) {
        return 0;
    }

    MemoryBlock* current = first_block;

    while (current) {
        if (current->is_free && current->size >= request_size) {
            if (current->size > request_size + sizeof(MemoryBlock)) {
                MemoryBlock* new_block = (MemoryBlock*)((char*)current + sizeof(MemoryBlock) + request_size);
                new_block->size = current->size - request_size - sizeof(MemoryBlock);
                new_block->is_free = 1;
                new_block->next = current->next;
                new_block->prev = current;
                if (current->next) {
                    current->next->prev = new_block;
                }
                current->next = new_block;
                current->size = request_size;
            }

            current->is_free = 0;
            return (char*)current + sizeof(MemoryBlock);
        }
        current = current->next;
    }

    return 0;
}

void free_memory(void* pointer) {
    if (!pointer) {
        return;
    }

    MemoryBlock* block_to_free = (MemoryBlock*)((char*)pointer - sizeof(MemoryBlock));
    block_to_free->is_free = 1;

    if (block_to_free->next && block_to_free->next->is_free) {
        block_to_free->size += sizeof(MemoryBlock) + block_to_free->next->size;
        block_to_free->next = block_to_free->next->next;
        if (block_to_free->next) {
            block_to_free->next->prev = block_to_free;
        }
    }

    if (block_to_free->prev && block_to_free->prev->is_free) {
        block_to_free->prev->size += sizeof(MemoryBlock) + block_to_free->size;
        block_to_free->prev->next = block_to_free->next;
        if (block_to_free->next) {
            block_to_free->next->prev = block_to_free->prev;
        }
    }
}

int get_minimum_memory_size() {
    return sizeof(MemoryBlock);
}

int get_block_metadata_size() {
    return sizeof(MemoryBlock);
}
