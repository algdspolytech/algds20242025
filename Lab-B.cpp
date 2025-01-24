#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"

#define TEST_MEM_SIZE 1048576
#define NUM_OPERATIONS 1000
char test_memory[TEST_MEM_SIZE];

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void test_custom_allocator() {
    double start, end, elapsedTime;
    meminit(test_memory, TEST_MEM_SIZE);
    void* allocations[NUM_OPERATIONS];

    start = get_time_in_seconds();

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        allocations[i] = memalloc(128);
    }

    end = get_time_in_seconds();
    elapsedTime = end - start;
    printf("Custom Allocator (memalloc): %.5f seconds\n", elapsedTime);

    start = get_time_in_seconds();

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        memfree(allocations[i]);
    }

    end = get_time_in_seconds();
    elapsedTime = end - start;
    printf("Custom Allocator (memfree): %.5f seconds\n", elapsedTime);

    memdone();
}

void test_standard_allocator() {
    double start, end, elapsedTime;
    void* allocations[NUM_OPERATIONS];

    start = get_time_in_seconds();

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        allocations[i] = malloc(128);
    }

    end = get_time_in_seconds();
    elapsedTime = end - start;
    printf("Standard Allocator (malloc): %.5f seconds\n", elapsedTime);

    start = get_time_in_seconds();

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        free(allocations[i]);
    }

    end = get_time_in_seconds();
    elapsedTime = end - start;
    printf("Standard Allocator (free): %.5f seconds\n", elapsedTime);
}

int main() {
    printf("Testing Custom Allocator:\n");
    test_custom_allocator();

    printf("\nTesting Standard Allocator:\n");
    test_standard_allocator();

    return 0;
}
