#include "memallocator.h"
#include <stddef.h>
#include <string.h>

typedef struct Block {
    size_t size;          // ������ �����
    int free;             // ������� �����������
    struct Block* next;   // ��������� �� ��������� ����
} Block;

static Block* head = NULL;       // ��������� �� ������ ������ ��������� ������
static void* memory_pool = NULL; // ��������� �� ���������� ������� ������
static int pool_size = 0;        // ����� ������ ������� ������

// ���������� ����������� ������, ����������� ��� ������������� ������
int memgetminimumsize() {
    return (int)sizeof(Block);
}

// ���������� ������ ��������� ���������� ��� ������ �����
int memgetblocksize() {
    return (int)sizeof(Block);
}

// ������������� ������� ������
int meminit(void* pMemory, int size) {
    if (!pMemory || size <= memgetminimumsize()) {
        return 0;
    }

    memory_pool = pMemory;
    pool_size = size;

    // ������������� ������� ���������� �����
    head = (Block*)pMemory;
    head->size = size - memgetminimumsize();
    head->free = 1;
    head->next = NULL;

    return 1;
}

// ���������� ������ � �������� ������
void memdone() {
    head = NULL;
    memory_pool = NULL;
    pool_size = 0;
}

// ��������� ������
void* memalloc(int size) {
    if (size <= 0) {
        return NULL;
    }

    Block* prev = NULL;
    Block* current = head;
    Block* best_fit = NULL;
    Block* best_fit_prev = NULL;

    // ����� ����� � ����������� ���������� ��������
    while (current) {
        if (current->free && current->size >= size) {
            if (!best_fit || current->size < best_fit->size) {
                best_fit = current;
                best_fit_prev = prev;
            }
        }
        prev = current;
        current = current->next;
    }

    if (!best_fit) {
        return NULL; // ��� ����������� �����
    }

    // ���������� �����, ���� �� ������ ������������ �������
    if (best_fit->size > size + memgetminimumsize()) {
        Block* new_block = (Block*)((char*)best_fit + memgetminimumsize() + size);
        new_block->size = best_fit->size - size - memgetminimumsize();
        new_block->free = 1;
        new_block->next = best_fit->next;

        best_fit->next = new_block;
        best_fit->size = size;
    }

    best_fit->free = 0; // ������� ����� ��� ��������

    return (char*)best_fit + memgetminimumsize();
}

// ������������ ������
void memfree(void* p) {
    if (!p || p < memory_pool || p >= (char*)memory_pool + pool_size) {
        return;
    }

    Block* block = (Block*)((char*)p - memgetminimumsize());
    block->free = 1;

    // ����������� �������� ��������� ������
    Block* current = head;
    while (current && current->next) {
        if (current->free && current->next->free &&
            (char*)current + memgetminimumsize() + current->size == (char*)current->next) {
            current->size += memgetminimumsize() + current->next->size;
            current->next = current->next->next;
        }
        else {
            current = current->next;
        }
    }
}
