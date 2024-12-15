#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"

#define TEST_POOL_SIZE 1024 * 1024 // 1 MB
#define NUM_ALLOCATIONS 1000
#define BLOCK_SIZE 128

// Тест производительности пользовательского аллокатора
void test_custom_allocator() {
    printf("Testing custom allocator...\n");

    // Инициализация пула памяти
    void *pool = malloc(TEST_POOL_SIZE);
    if (!pool) {
        fprintf(stderr, "Failed to allocate memory for custom allocator pool.\n");
        return;
    }
    if (meminit(pool, TEST_POOL_SIZE) != 0) {
        fprintf(stderr, "Failed to initialize custom allocator.\n");
        free(pool);
        return;
    }

    // Измерение времени выделения и освобождения памяти
    clock_t start = clock();
    void *allocations[NUM_ALLOCATIONS];

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        allocations[i] = memalloc(BLOCK_SIZE);
        if (!allocations[i]) {
            fprintf(stderr, "Custom allocator failed at allocation %d.\n", i);
            break;
        }
    }

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        if (allocations[i]) {
            memfree(allocations[i]);
        }
    }

    clock_t end = clock();
    printf("Custom allocator time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    memdone();
    free(pool);
}

// Тест производительности стандартного malloc/free
void test_standard_allocator() {
    printf("Testing standard allocator...\n");

    // Измерение времени выделения и освобождения памяти
    clock_t start = clock();
    void *allocations[NUM_ALLOCATIONS];

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        allocations[i] = malloc(BLOCK_SIZE);
        if (!allocations[i]) {
            fprintf(stderr, "Standard allocator failed at allocation %d.\n", i);
            break;
        }
    }

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        if (allocations[i]) {
            free(allocations[i]);
        }
    }

    clock_t end = clock();
    printf("Standard allocator time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    printf("Allocator Comparison Test\n========================\n");

    // Сравнение пользовательского аллокатора и стандартного malloc/free
    test_custom_allocator();
    test_standard_allocator();

    return 0;
}
