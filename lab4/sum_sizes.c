#include <stdio.h>
#include "sum_sizes.h"

int readInput(const char* filename, int* B, int* arr, int* N) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("�� ������� ������� ���� ��� ������.\n");
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

void writeOutput(const char* filename, int* res, int resSize) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("�� ������� ������� ���� ��� ������.\n");
        return;
    }

    if (resSize > 0) {
        for (int i = 0; i < resSize; i++) {
            fprintf(file, "%d ", res[i]);
        }
    }
    else {
        fprintf(file, "0");
    }

    fclose(file);
}

int sumSizes(int arr[], int n, int B, int res[], int* resSize) {
    if (B == 0) {
        return 1;
    }
    if (n == 0 || B < 0) {
        return 0;
    }

    res[*resSize] = arr[n - 1];
    (*resSize)++;
    if (sumSizes(arr, n - 1, B - arr[n - 1], res, resSize)) {
        return 1;
    }

    (*resSize)--;
    if (sumSizes(arr, n - 1, B, res, resSize)) {
        return 1;
    }

    return 0;
}
