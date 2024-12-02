#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"
#include <locale.h>
#include <windows.h>

// Сравнение с malloc/free
double test_malloc_free() {
    void *p1 = 0, *p2 = 0;

    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    // Используем стандартные malloc/free
    p1 = malloc(1000); // Выделяем первый блок
    p2 = malloc(1000); // Выделяем второй блок

    free(p2); // Освобождаем второй блок
    free(p1); // Освобождаем первый блок

    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
}

double test_memallocator() {
    
    void *p1 = 0, *p2 = 0;
    int memsize = 1e3 * memgetblocksize();

    // Выделяем достаточно памяти для двух блоков
    void* ptr = malloc(memsize); // Базовый блок для нашей системы

    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    // Инициализация и использование нашей системы памяти
    meminit(ptr, memsize);

    p1 = memalloc(100); // Выделяем первый блок
    p2 = memalloc(100); // Выделяем второй блок

    memfree(p2); // Освобождаем второй блок
    memfree(p1); // Освобождаем первый блок

    memdone(); // Завершаем работу с памятью

    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    // Сравниваем базовый malloc/free и нашу реализацию
    double time1 = 0, time2 = 0;
    for (int i = 0; i < 10000; i++) {
        time1 += test_malloc_free();
        time2 += test_memallocator();
    }

    printf("Базовые функции быстрее моих на %.3f процентов", ((time1 - time2)/time1) * 100);

    return 0;
}
