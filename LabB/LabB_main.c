#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TEST_MEM_SIZE 1048576
#define NUM_OPERATIONS 1000
char test_memory[TEST_MEM_SIZE];

void test_custom_allocator() {
    LARGE_INTEGER frequency, start, end;
    double elapsedTime;
    meminit(test_memory, TEST_MEM_SIZE);
    void* allocations[NUM_OPERATIONS];

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        allocations[i] = memalloc(128);
    }

    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Custom Allocator (memalloc): %.5f seconds\n", elapsedTime);

    QueryPerformanceCounter(&start);

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        memfree(allocations[i]);
    }

    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Custom Allocator (memfree): %.5f seconds\n", elapsedTime);

    memdone();
}

void test_standard_allocator() {
    LARGE_INTEGER frequency, start, end;
    double elapsedTime;
    void* allocations[NUM_OPERATIONS];

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        allocations[i] = malloc(128);
    }

    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Standard Allocator (malloc): %.5f seconds\n", elapsedTime);

    QueryPerformanceCounter(&start);

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        free(allocations[i]);
    }

    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Standard Allocator (free): %.5f seconds\n", elapsedTime);
}

int main() {
    printf("Testing Custom Allocator:\n");
    test_custom_allocator();

    printf("\nTesting Standard Allocator:\n");
    test_standard_allocator();

    return 0;
}
