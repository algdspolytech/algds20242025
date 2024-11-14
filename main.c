#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// ������� ��� ���������� ������������ �������� � �������
int findMinElement(int* arr, int N) {
    if (N <= 0) {
        // ���� ������ ������, ���������� INT_MAX ��� ����� ������� ������
        return INT_MAX;
    }

    int min = arr[0]; // �����������, ��� ������ ������� - �����������
    for (int i = 1; i < N; i++) {
        if (arr[i] < min) {
            min = arr[i]; // ��������� �������
        }
    }
    return min; // ���������� ����������� �������
}

bool findSubset(int* arr, int n, int target, Result* result) {

    if (n < findMinElement(arr, n)) return false;

    // ������� ������ ��� �������� ��������� ������������� ����������������
    bool* dp = (bool*)calloc(target + 1, sizeof(bool));
    dp[0] = true; // ����� 0 ������ �������� (������ ������������)

    // ������ ��� ������������ ������ ���������
    int* chosen = (int*)malloc((target + 1) * sizeof(int));
    memset(chosen, -1, (target + 1) * sizeof(int)); // ������������� �������

    // ��������� ������ dp
    for (int i = 0; i < n; i++) {
        for (int j = target; j >= arr[i]; j--) {
            if (dp[j - arr[i]] && !dp[j]) {
                dp[j] = true;
                chosen[j] = i; // ���������� ������ ���������� ��������
            }
        }
    }

    if (!dp[target]) {
        free(dp);
        free(chosen);
        return false; // ��� ������������, ������� ���� ������ �����
    }

    // ���� ����� ��������, ��������������� �������������� ��������
    result->count = 0;
    result->indices = (int*)malloc(n * sizeof(int));
    for (int t = target; t > 0; ) {
        int i = chosen[t];
        if (i == -1) { // ���� ��� ������ ��������, �������
            break;
        }
        result->indices[result->count++] = arr[i]; // ��������� �������
        t -= arr[i];
    }

    free(dp);
    free(chosen);

    return true; // ������� ������������
}

void execute_algorithm() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        perror("������ �������� �����");
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