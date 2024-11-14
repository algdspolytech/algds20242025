#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

// Структура для хранения индексов выбранных элементов
typedef struct {
    int* indices;
    int count;
} Result;

bool findSubset(int* arr, int n, int target, Result* result);
void execute_algorithm();

#endif // MAIN_H