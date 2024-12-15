#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "memallocator.h"

typedef struct Block {
    size_t size;
    bool is_free;
    struct Block* next;
    struct Block* prev;
} Block;

static Block* head = NULL;

int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= sizeof(Block)) {
        return 0;
    }

    head = (Block*)pMemory;
    head->size = size - sizeof(Block);
    head->is_free = true;
    head->next = NULL;
    head->prev = NULL;

    return 0;
}

void memdone() {
    head = NULL;
    return;
}

void* memalloc(int size) {
    if (size <= 0) {
        return NULL;
    }

    Block* current = head;

    while (current && !(current->is_free && current->size >= size)) {
        current = current->next;
    }

    if (!current) {
        return NULL;
    }

    if (current->size == size) {
        current->is_free = false;
        return (void*)((char*)current + sizeof(Block));
    }
    if (current->size > size) {
        Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
        new_block->size = current->size - size - sizeof(Block);
        new_block->is_free = true;
        new_block->next = current->next;
        new_block->prev = current;
        if (current->next) {
            current->next->prev = new_block;
        }
        current->next = new_block;
        current->size = size;
    }
    current->is_free = false;
    return (void*)((char*)current + sizeof(Block));
}

void memfree(void* ptr) {
    if (!ptr) {
        return;
    }
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    if (block->is_free) {
        return;
    }
    block->is_free = true;

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

int memgetminimumsize() {
    return sizeof(Block);
}

int memgetblocksize() {
    return sizeof(Block);
}
