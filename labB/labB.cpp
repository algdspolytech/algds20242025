#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Block {
    size_t size;              // ������ �����
    struct Block* prev;      // ��������� �� ���������� ����
    struct Block* next;      // ��������� �� ��������� ����
    int free;                // ����, �������� �� ����
} Block;

Block* head = NULL; // ������ ������ ��������� ������


#include "memallocator.h"

int meminit(void* pMemory, int size) {
    if (!pMemory || size <= sizeof(Block)) {
        return -1; // ������: �������� ���������
    }

    head = (Block*)pMemory;
    head->size = size - sizeof(Block);
    head->prev = NULL;
    head->next = NULL;
    head->free = 1;

    return 0; // �����
}

void memdone() {
    head = NULL; // ����������� ������ (������ ���������)
}

void* memalloc(int size) {
    if (size <= 0) return NULL;

    Block* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            // ���� ������ ����� ������ ������������, ��������� ���
            if (current->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->prev = current;
                new_block->next = current->next;
                new_block->free = 1;

                if (current->next) {
                    current->next->prev = new_block;
                }
                current->next = new_block;
                current->size = size;
            }
            current->free = 0; // ���� ������ �����
            return (char*)current + sizeof(Block); // ���������� ��������� �� ������
        }
        current = current->next;
    }
    return NULL; // �� ������� �������� ������
}

void memfree(void* p) {
    if (!p) return;

    Block* block = (Block*)((char*)p - sizeof(Block));
    block->free = 1; // �������� ���� ��� ���������

    // ������� � ���������� ������, ���� �� ��������
    if (block->prev && block->prev->free) {
        block->prev->size += sizeof(Block) + block->size;
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
        block = block->prev; // ��������� ��������� �� ������� ����
    }

    // ������� � ��������� ������, ���� �� ��������
    if (block->next && block->next->free) {
        block->size += sizeof(Block) + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }
    }
}

int memgetminimumsize() {
    return sizeof(Block);
}

int memgetblocksize() {
    return sizeof(Block);
}

// ������� ��� ������������ ������������������
void performance_test(int num_allocations, int allocation_size) {
    void* pool = malloc(memgetminimumsize() + num_allocations * allocation_size);
    meminit(pool, memgetminimumsize() + num_allocations * allocation_size);

    clock_t start_time = clock();

    void** allocations = (void**)malloc(num_allocations * sizeof(void*)); // ���������� ����

    for (int i = 0; i < num_allocations; i++) {
        allocations[i] = memalloc(allocation_size);
    }

    for (int i = 0; i < num_allocations; i++) {
        memfree(allocations[i]);
    }

    clock_t end_time = clock();

    printf("Custom allocator: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    free(allocations);
    memdone();
    free(pool);
}

// ������� ��� ������������ ������������ malloc/free
void standard_performance_test(int num_allocations, int allocation_size) {
    clock_t start_time = clock();

    void** allocations = (void**)malloc(num_allocations * sizeof(void*)); // ���������� ����

    for (int i = 0; i < num_allocations; i++) {
        allocations[i] = malloc(allocation_size);
    }

    for (int i = 0; i < num_allocations; i++) {
        free(allocations[i]);
    }

    clock_t end_time = clock();

    printf("Standard malloc/free: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    free(allocations);
}


// ������� ������� ��� ������� ������
/*int main() {
    const int num_allocations = 10000; // ���������� ���������
    const int allocation_size = 64;     // ������ ���������� ������

    printf("Performance test results:\n");

    performance_test(num_allocations, allocation_size);
    standard_performance_test(num_allocations, allocation_size);

    return 0;
}*/
