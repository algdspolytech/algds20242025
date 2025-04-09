#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "rucksack.h"
#define _CRTDBG_MAP_ALLOC 

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

int knapsack(int U, int B, int K, const int* weights, const int* values) {
    int* dp = (int*)malloc((B + 1) * sizeof(int));
    if (!dp) return 0;

    for (int i = 1; i <= B; ++i) {
        dp[i] = -1; 
    }
    dp[0] = 0;

    for (int i = 0; i < U; ++i) {
        int w = weights[i];
        int v = values[i];
        for (int j = B; j >= w; --j) {
            if (dp[j - w] != -1) {
                if (dp[j] < dp[j - w] + v) {
                    dp[j] = dp[j - w] + v;
                }
            }
        }
    }

    for (int j = 0; j <= B; ++j) {
        if (dp[j] >= K) {
            free(dp);
            return 1;
        }
    }

    free(dp);
    return 0;
}
