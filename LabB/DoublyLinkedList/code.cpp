#include "memallocator.h"
#include <stddef.h>
#include <stdint.h>


typedef struct BlockHeader {
    int size; 
    int is_free; 
    struct BlockHeader* next;
    struct BlockHeader* prev; 
} BlockHeader;


static void* memory_pool = NULL;
static int memory_pool_size = 0;
static BlockHeader* free_list_head = NULL;

#define HEADER_SIZE ((int)sizeof(BlockHeader))

int meminit(void* pMemory, int size) {
    if (!pMemory || size <= HEADER_SIZE) {
        return 0; 
    }

    memory_pool = pMemory;
    memory_pool_size = size;

    
    free_list_head = (BlockHeader*)pMemory;
    free_list_head->size = size - HEADER_SIZE;
    free_list_head->is_free = 1;
    free_list_head->next = NULL;
    free_list_head->prev = NULL;

    return 1;
}

void memdone() {
    
    memory_pool = NULL;
    memory_pool_size = 0;
    free_list_head = NULL;
}

void* memalloc(int size) {
    if (size <= 0 || !free_list_head) {
        return NULL;
    }

    
    size = (size + 7) & ~7;

    
    BlockHeader* current = free_list_head;
    while (current) {
        if (current->is_free && current->size >= size) {
            
            if (current->size >= size + HEADER_SIZE + 8) {
                BlockHeader* new_block = (BlockHeader*)((uint8_t*)current + HEADER_SIZE + size);
                new_block->size = current->size - size - HEADER_SIZE;
                new_block->is_free = 1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) {
                    current->next->prev = new_block;
                }

                current->next = new_block;
                current->size = size;
            }

            current->is_free = 0;
            return (void*)((uint8_t*)current + HEADER_SIZE);
        }

        current = current->next;
    }

    return NULL; 
}

void memfree(void* p) {
    if (!p || p < memory_pool || p >= (uint8_t*)memory_pool + memory_pool_size) {
        return; 
    }

    BlockHeader* block = (BlockHeader*)((uint8_t*)p - HEADER_SIZE);
    block->is_free = 1;

    
    if (block->next && block->next->is_free) {
        block->size += HEADER_SIZE + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }

    
    if (block->prev && block->prev->is_free) {
        block->prev->size += HEADER_SIZE + block->size;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
    }
}

int memgetminimumsize() {
    
    return HEADER_SIZE + 8;
}

int memgetblocksize() {
    
    return HEADER_SIZE;
}
