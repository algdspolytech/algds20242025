#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// Функция для нахождения минимального элемента в массиве
int findMinElement(int* arr, int N) {
    if (N <= 0) {
        // Если массив пустой, возвращаем INT_MAX или можно вызвать ошибку
        return INT_MAX;
    }

    int min = arr[0]; // Предположим, что первый элемент - минимальный
    for (int i = 1; i < N; i++) {
        if (arr[i] < min) {
            min = arr[i]; // Обновляем минимум
        }
    }
    return min; // Возвращаем минимальный элемент
}

bool findSubset(int* arr, int n, int target, Result* result) {

    if (n < findMinElement(arr, n)) return false;

    // Создаем массив для хранения состояния динамического программирования
    bool* dp = (bool*)calloc(target + 1, sizeof(bool));
    dp[0] = true; // Сумма 0 всегда возможна (пустое подмножество)

    // Массив для отслеживания выбора элементов
    int* chosen = (int*)malloc((target + 1) * sizeof(int));
    memset(chosen, -1, (target + 1) * sizeof(int)); // Инициализация массива

    // Заполняем массив dp
    for (int i = 0; i < n; i++) {
        for (int j = target; j >= arr[i]; j--) {
            if (dp[j - arr[i]] && !dp[j]) {
                dp[j] = true;
                chosen[j] = i; // Запоминаем индекс выбранного элемента
            }
        }
    }

    if (!dp[target]) {
        free(dp);
        free(chosen);
        return false; // Нет подмножества, которое дает нужную сумму
    }

    // Если сумма возможна, восстанавливаем использованные элементы
    result->count = 0;
    result->indices = (int*)malloc(n * sizeof(int));
    for (int t = target; t > 0; ) {
        int i = chosen[t];
        if (i == -1) { // Если нет такого элемента, выходим
            break;
        }
        result->indices[result->count++] = arr[i]; // Добавляем элемент
        t -= arr[i];
    }

    free(dp);
    free(chosen);

    return true; // Найдено подмножество
}

void execute_algorithm() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        perror("Ошибка открытия файла");
        return;
    }

    int B, N;
    fscanf(input, "%d", &B);
    fscanf(input, "%d", &N);

    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &arr[i]);
    }

    Result result;
    if (findSubset(arr, N, B, &result)) {
        for (int i = 0; i < result.count; i++) {
            fprintf(output, "%d ", result.indices[i]);
        }
        free(result.indices);
    }
    else {
        fprintf(output, "0");
    }

    free(arr);
    fclose(input);
    fclose(output);
}