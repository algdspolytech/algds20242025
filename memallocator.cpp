#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memallocator.h"

// ��������� ��� �������� ���������� � ������ ������
typedef struct MemoryBlock {
    int size;                       // ������ �����
    int is_free;                    // 1, ���� ���� ��������, ����� 0
    struct MemoryBlock* next;       // ��������� �� ��������� ����
    struct MemoryBlock* prev;       // ��������� �� ���������� ����
} MemoryBlock;

static void* memory_pool = NULL;    // ��������� �� ������ ������
static int memory_pool_size = 0;   // ������ ������
static MemoryBlock* head = NULL;   // ������ ������ ������

int meminit(void* pMemory, int size) {
    if (pMemory == NULL  size < memgetminimumsize()) {
        return 0;
    }

    memory_pool = pMemory;
    memory_pool_size = size;

    // ������������� ������� �����
    head = (MemoryBlock*)pMemory;
    head->size = size - sizeof(MemoryBlock);
    head->is_free = 1;
    head->next = NULL;
    head->prev = NULL;

    return 1;
}

void memdone() {
    memory_pool = NULL;
    memory_pool_size = 0;
    head = NULL;
}

void* memalloc(int size) {
    if (size <= 0  size > memory_pool_size - sizeof(MemoryBlock)) {
        return NULL;
    }

    MemoryBlock* current = head;
    int direction = 1; // 1 - ������ ������, 0 - �������� ������

    while (current) {
        if (current->is_free && current->size >= size) {
            // ���� ���� ����������, �������� ������
            if (current->size >= size + sizeof(MemoryBlock) + 1) {
                // ���������� �����
                MemoryBlock* new_block = (MemoryBlock*)((char*)current + sizeof(MemoryBlock) + size);
                new_block->size = current->size - size - sizeof(MemoryBlock);
                new_block->is_free = 1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) {
                    current->next->prev = new_block;
                }
                current->next = new_block;
            }

            current->size = size;
            current->is_free = 0;
            return (char*)current + sizeof(MemoryBlock);
        }

        current = direction ? current->next : current->prev;

        // ���� ����� �� �����, ������ �����������
        if (!current && direction) {
            current = head;
            while (current && current->next) {
                current = current->next;
            }
            direction = 0;
        }
    }

    return NULL;
}

void memfree(void* p) {
    if (p == NULL  p < memory_pool  p >= (char*)memory_pool + memory_pool_size) {
        return;
    }

    MemoryBlock* block = (MemoryBlock*)((char*)p - sizeof(MemoryBlock));
    block->is_free = 1;

    // ������� � ��������� ���������� �������
    if (block->next && block->next->is_free) {
        block->size += sizeof(MemoryBlock) + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }

    if (block->prev && block->prev->is_free) {
        block->prev->size += sizeof(MemoryBlock) + block->size;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
    }
}

int memgetminimumsize() {
    return sizeof(MemoryBlock) + 1;
}

int memgetblocksize() {
    return sizeof(MemoryBlock);
}