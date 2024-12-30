#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "memallocator.h"

#define MEMORY_SIZE 1024 
#define NUM_ITERATIONS 1000000

void compare() {
    void* memory = malloc(MEMORY_SIZE);
    meminit(memory, MEMORY_SIZE);

    clock_t start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        void* p = memalloc(64); 
        memfree(p);
    }
    clock_t end = clock();
    double result = (double)(end - start);
    printf("memalloc/memfree: %.9f секунд\n", result);

    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        void* p = malloc(64);
        free(p);
    }
    end = clock();
    result = (double)(end - start);
    printf("malloc/free: %.9f секунд\n", result);

    memdone(); 
    free(memory);
}

void check_working() {
    void* memory = malloc(MEMORY_SIZE);
    if (!memory) {
        printf("Ошибка при выделении памяти.\n");
        return;
    }
    meminit(memory, MEMORY_SIZE);
    void* ptr = memalloc(128);
    printf("Указатель: %p\n", ptr);
    memfree(ptr); 
    memdone(); 
    free(memory); 
}

int main() {
    setlocale(LC_ALL, "RUS");
    check_working();
    compare();
    return 0;
}
