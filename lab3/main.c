#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC 
#pragma warning (disable:4996)

// ������ ������� ������
void read_input(const char* filename, int* U, int* B, int* K, int** weights, int** values) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d %d", U, B, K);

    *weights = (int*)malloc(*U * sizeof(int));
    *values = (int*)malloc(*U * sizeof(int));

    for (int i = 0; i < *U; i++) {
        fscanf(file, "%d", &(*weights)[i]);
    }

    for (int i = 0; i < *U; i++) {
        fscanf(file, "%d", &(*values)[i]);
    }

    fclose(file);
}

// ������ �����������
void write_output(const char* filename, int* selected_items, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    if (count == 0) {
        fprintf(file, "0\n");
    }
    else {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d ", selected_items[i]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int knapsack(int U, int B, int K, int* weights, int* values) {
    int** dp = (int**)malloc((B + 1) * sizeof(int*));
    for (int i = 0; i <= B; i++) {
        dp[i] = (int*)calloc(K + 1, sizeof(int));
    }

    // ���������� ������������ �������
    for (int i = 0; i < U; i++) {
        for (int j = B; j >= weights[i]; j--) {
            for (int k = K; k >= values[i]; k--) {
                dp[j][k] = dp[j][k] || dp[j - weights[i]][k - values[i]];
            }
        }
    }

    // ����� ����������� ������������
    int found = 0;
    for (int j = 0; j <= B; j++) {
        for (int k = K; k <= K; k++) {
            if (dp[j][k]) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    // ������������ ������
    for (int i = 0; i <= B; i++) {
        free(dp[i]);
    }
    free(dp);

    return found;
}

// ���� �������� �������, ������� �� ������ ���������, ���������� �� ���������� 
// ������������ ���������, �� � ��������������� ������� ���� ��������� ��� ������ � ����.
//��� ����� �������� ��������� �� ������ selected_items, ������� ����� ������� � �������
//  knapsack, ����� ��������� ������� ��������� ���������

//int knapsack(int U, int B, int K, int* weights, int* values, int** selected_items) {
//    int** dp = (int**)malloc((B + 1) * sizeof(int*));
//    for (int i = 0; i <= B; i++) {
//        dp[i] = (int*)calloc(K + 1, sizeof(int));
//    }
//
//    // ���������� ������������ �������
//    for (int i = 0; i < U; i++) {
//        for (int j = B; j >= weights[i]; j--) {
//            for (int k = K; k >= values[i]; k--) {
//                dp[j][k] = dp[j][k] || dp[j - weights[i]][k - values[i]];
//            }
//        }
//    }
//
//    // ����� ����������� ������������
//    int found = 0;
//    for (int j = 0; j <= B; j++) {
//        for (int k = K; k <= K; k++) {
//            if (dp[j][k]) {
//                found = 1;
//                break;
//            }
//        }
//        if (found) break;
//    }
//
//    // ���� ������� �������, ��������������� ��������� ��������
//    if (found) {
//        int count = 0;
//        *selected_items = (int*)malloc(U * sizeof(int));
//
//        int w = B, v = K;
//        for (int i = U - 1; i >= 0; i--) {
//            if (w >= weights[i] && v >= values[i] && dp[w][v] != dp[w - weights[i]][v - values[i]]) {
//                (*selected_items)[count++] = i + 1; // +1 ��� 1-����������
//                w -= weights[i];
//                v -= values[i];
//            }
//        }
//
//        // �������� ������� ��� ����������� ������
//        for (int i = 0; i < count / 2; i++) {
//            int temp = (*selected_items)[i];
//            (*selected_items)[i] = (*selected_items)[count - 1 - i];
//            (*selected_items)[count - 1 - i] = temp;
//        }
//
//        // ������������ ������
//        for (int i = 0; i <= B; i++) {
//            free(dp[i]);
//        }
//        free(dp);
//
//        return count; // ���������� ���������� ��������� ���������
//    }
//
//    // ������������ ������
//    for (int i = 0; i <= B; i++) {
//        free(dp[i]);
//    }
//    free(dp);
//
//    return 0; // ������ �� �������
//}

int main() {
    int U, B, K;
    int* weights, * values;

    read_input("input.txt", &U, &B, &K, &weights, &values);

    if (knapsack(U, B, K, weights, values)) {
        write_output("output.txt", NULL, 0);
    }
    else {
        write_output("output.txt", NULL, 0);
    }

    /*read_input("input.txt", &U, &B, &K, &weights, &values);

    int* selected_items = NULL;
    int count = knapsack(U, B, K, weights, values, &selected_items);

    write_output("output.txt", selected_items, count);*/

    free(weights);
    free(values);
    /*free(selected_items);*/
    return 0;
}
