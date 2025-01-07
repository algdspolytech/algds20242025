#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"

#define MEMORY_POOL_SIZE 1024 * 1024  

void test_memory_allocator() {
    void* memory_pool = malloc(MEMORY_POOL_SIZE);

    if (meminit(memory_pool, MEMORY_POOL_SIZE) != 0) {
        fprintf(stderr, "Memory initialization error\n");
        free(memory_pool);
        return;
    }

    clock_t start, end;

    
    start = clock();

    void* ptrs[1000];

    for (int i = 0; i < 1000; i++) {
        ptrs[i] = memalloc(100);  
    }

    for (int i = 0; i < 1000; i++) {
        memfree(ptrs[i]);  
    }

    end = clock();

    printf("Memalloc/memfree execution time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    memdone();
    free(memory_pool);
}

void test_standard_allocator() {
    clock_t start, end;

    start = clock();

    void* ptrs[1000];

    for (int i = 0; i < 1000; i++) {
        ptrs[i] = malloc(100);  
    }

    for (int i = 0; i < 1000; i++) {
        free(ptrs[i]);  
    }

    end = clock();

    printf("Malloc/free execution time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    printf("Testing a custom allocator:\n");
    test_memory_allocator();

    printf("\nTesting a standard allocator:\n");
    test_standard_allocator();

    return 0;
}
