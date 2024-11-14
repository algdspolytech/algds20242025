#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "main.h"

// ������� ��� �������� � ������������� ����������� ������
void createTestData(int** arr, int* N, int** B, int testCase) {
    switch (testCase) {
    case 1: // ������ ���������
        *B = (int*)malloc(sizeof(int));
        **B = 5;
        *N = 0;
        *arr = NULL;
        break;
    case 2: // ������������ ������� � ����� ���������
        *B = (int*)malloc(sizeof(int));
        **B = 10;
        *N = 1;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 10;
        break;
    case 3: // ��� �������� ��������� � ����� �� ������ �������� �������
        *B = (int*)malloc(sizeof(int));
        **B = 6; 
        *N = 5;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 5; (*arr)[1] = 5; (*arr)[2] = 5; (*arr)[3] = 5; (*arr)[4] = 5;
        break;
    case 4: // ������������� ��������, �� ����� ���������� 
        *B = (int*)malloc(sizeof(int));
        **B = 15;
        *N = 5;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 1; (*arr)[1] = 2; (*arr)[2] = 3; (*arr)[3] = 4; (*arr)[4] = 5;
        break;
    case 5: // ������������ ����� � ����������� ������������
        *B = (int*)malloc(sizeof(int));
        **B = 8;
        *N = 6;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 1; (*arr)[1] = 2; (*arr)[2] = 3; (*arr)[3] = 5; (*arr)[4] = 6; (*arr)[5] = 7;
        break;
    case 6: // ������������� ���� ���������
        *B = (int*)malloc(sizeof(int));
        **B = 9;
        *N = 3;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 1; (*arr)[1] = 3; (*arr)[2] = 5;
        break;
    case 7: // ������� ������ � ������������� ���������� 
        *B = (int*)malloc(sizeof(int));
        **B = INT_MAX;
        *N = 2;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = INT_MAX; (*arr)[1] = INT_MAX - 1;
        break;
    case 8: // ����������� ��������
        *B = (int*)malloc(sizeof(int));
        **B = 1;
        *N = 1;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 1;
        break;
    case 9: // ����� ������, ��� ����������� �������
        *B = (int*)malloc(sizeof(int));
        **B = 3;
        *N = 3;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 5; (*arr)[1] = 6; (*arr)[2] = 7;
        break;
    case 10: // ������� � �������
        *B = (int*)malloc(sizeof(int));
        **B = 10;
        *N = 6;
        *arr = (int*)malloc(*N * sizeof(int));
        (*arr)[0] = 5; (*arr)[1] = 5; (*arr)[2] = 1; (*arr)[3] = 3; (*arr)[4] = 2; (*arr)[5] = 2;
        break;
    }
}

int sumElements(int* arr, int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }
    return sum;
}

// ������� ��� ���������� �����
void runTest(int* arr, int N, int B, int testCase) {
    Result result;

    // ��������� file input.txt ������������� �������
    FILE* input = fopen("input.txt", "w");
    fprintf(input, "%d\n%d\n", B, N);
    for (int i = 0; i < N; i++) {
        fprintf(input, "%d ", arr[i]);
    }
    fclose(input);

    // ��������� ��������
    execute_algorithm();

    // ������ ����� ��������� �������� ������ �� output.txt
    FILE* output = fopen("output.txt", "r");
    char buffer[512];
    fscanf(output, "%s", buffer);

    if (strcmp(buffer, "0") == 1) {
        printf("Test %d = %s\n", testCase, (N == 0 || (N > 0 && B <= sumElements(arr, N))) ? "PASSED" : "FAILED");
    }
    else {
        printf("Test %d = PASSED\n", testCase);
    }
    fclose(output);
}

int main() {
    int* arr;
    int N;
    int* B;

    for (int i = 1; i <= 10; i++) {
        createTestData(&arr, &N, &B, i);
        runTest(arr, N, *B, i);
        free(arr);
        free(B);
    }

    return 0;
}
