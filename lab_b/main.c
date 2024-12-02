#include <stdlib.h>
#include <string.h>
#include "memallocator.h" 

typedef struct Block {
    int size;                
    int is_free;             
    struct Block* next;      
    struct Block* prev;      
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
        return 0; 
    }

    memory_pool = pMemory;
    total_memory = size;

    free_list = (Block*)pMemory;
    free_list->size = size - sizeof(Block);
    free_list->is_free = 1;
    free_list->next = NULL;
    free_list->prev = NULL;

    return 1; 
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
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->is_free = 1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) {
                    current->next->prev = new_block; 
                }
                current->size = size;
                current->next = new_block;
            }

            current->is_free = 0; 
            return (char*)current + sizeof(Block);
        }
        current = current->next;
    }

    return NULL; 
}

void memfree(void* p) {
    if (!p || !memory_pool) {
        return;
    }

    Block* block = (Block*)((char*)p - sizeof(Block));
    block->is_free = 1;

    
    if (block->next && block->next->is_free) {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block; 
        }
    }

    
    if (block->prev && block->prev->is_free) {
        block->prev->size += block->size + sizeof(Block);
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev; 
        }
        block = block->prev; 
    }
}
