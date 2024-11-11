#include <stdio.h>
#include "algos_4.h"

int readInput(const char* filename, int* B, int* arr, int* N) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл для чтения.\n");
        return 0;
    }

    fscanf(file, "%d", B);
    fscanf(file, "%d", N);
    for (int i = 0; i < *N; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
    return 1;
}

void writeOutput(const char* filename, int* result, int resultSize) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    if (resultSize > 0) {
        for (int i = 0; i < resultSize; i++) {
            fprintf(file, "%d ", result[i]);
        }
    }
    else {
        fprintf(file, "0");
    }

    fclose(file);
}

int subsetSum(int arr[], int n, int B, int result[], int* resultSize) {
    if (B == 0) {
        return 1;
    }
    if (n == 0 || B < 0) {
        return 0;
    }

    result[*resultSize] = arr[n - 1];
    (*resultSize)++;
    if (subsetSum(arr, n - 1, B - arr[n - 1], result, resultSize)) {
        return 1;
    }

    (*resultSize)--;
    if (subsetSum(arr, n - 1, B, result, resultSize)) {
        return 1;
    }

    return 0;
}
