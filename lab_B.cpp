#include "memallocator.h"
#include <stddef.h>
#include <stdio.h>

typedef struct Block {
    struct Block* next;   
    struct Block* prev;   
    int size;             
    int free;             
} Block;

static Block* freeList = NULL;  
static void* memoryPool = NULL; 
static int poolSize = 0;        


int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= 0) {
        return -1; 
    }

    memoryPool = pMemory;
    poolSize = size;

    
    freeList = (Block*)pMemory;
    freeList->next = NULL;
    freeList->prev = NULL;
    freeList->size = size - sizeof(Block); 
    freeList->free = 1;  

    return 0;  
}


void memdone() {
    memoryPool = NULL;
    freeList = NULL;
    poolSize = 0;
}


void* memalloc(int size) {
    if (size <= 0) {
        return NULL;  
    }

    
    Block* current = freeList;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            
            if (current->size > size + sizeof(Block)) {
                
                Block* newBlock = (Block*)((char*)current + sizeof(Block) + size);
                newBlock->size = current->size - size - sizeof(Block);
                newBlock->free = 1;
                newBlock->next = current->next;
                newBlock->prev = current;

                if (current->next) {
                    current->next->prev = newBlock;
                }

                current->next = newBlock;
                current->size = size;
            }

            current->free = 0;  
            return (char*)current + sizeof(Block); 
        }
        current = current->next;
    }

    return NULL; 
}


void memfree(void* p) {
    if (p == NULL) {
        return;  
    }

    
    Block* current = (Block*)((char*)p - sizeof(Block));
    current->free = 1;  

    
    if (current->prev && current->prev->free) {
        current->prev->size += current->size + sizeof(Block);
        current->prev->next = current->next;
        if (current->next) {
            current->next->prev = current->prev;
        }
        current = current->prev;
    }

    if (current->next && current->next->free) {
        current->size += current->next->size + sizeof(Block);
        current->next = current->next->next;
        if (current->next) {
            current->next->prev = current;
        }
    }
}


int memgetminimumsize() {
    return sizeof(Block);  
}

int memgetblocksize() {
    return sizeof(Block);  
}

