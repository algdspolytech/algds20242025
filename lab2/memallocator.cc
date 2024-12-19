#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "memallocator.h"


typedef struct Block {
    size_t size;      
    struct Block *prev;  
    struct Block *next;  
    bool free;         
} Block;

Block *head = NULL;
void *memory_start = NULL; 
size_t total_size = 0; 

int meminit(void *pMemory, int size) {
    if (size < sizeof(Block)) {
        return -1;
    }

    memory_start = pMemory;
    total_size = size;

    head = (Block *)memory_start;
    head->size = size - sizeof(Block);
    head->prev = NULL;
    head->next = NULL;
    head->free = true;

    return 0;
}

void memdone() {
    head = NULL;
    memory_start = NULL;
    total_size = 0;
}

void *memalloc(int size) {
    if (size <= 0) {
        return NULL;
    }
    size += sizeof(Block); 
    Block *current = head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size + sizeof(Block)) {
                Block *new_block = (Block *)((char *)current + size);
                new_block->size = current->size - size;
                new_block->prev = current;
                new_block->next = current->next;
                new_block->free = true;
                if (current->next != NULL) {
                    current->next->prev = new_block;
                }
                current->next = new_block;
                current->size = size - sizeof(Block);
            }
            current->free = false; 
            return (char *)current + sizeof(Block); 
        }
        current = current->next; 
    }
    return NULL;
}

void memfree(void *p) {
    if (p == NULL) {
        return; 
    }

    Block *current = (Block *)((char *)p - sizeof(Block));
    current->free = true;

    if (current->next != NULL && current->next->free) {
        current->size += sizeof(Block) + current->next->size;
        current->next = current->next->next;
        if (current->next != NULL) {
            current->next->prev = current;
        }
    }
    if (current->prev != NULL && current->prev->free) {
        current->prev->size += sizeof(Block) + current->size;
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        current = current->prev;
    }
}

int memgetminimumsize() {
    return sizeof(Block);
}

int memgetblocksize() {
    return sizeof(Block);
}