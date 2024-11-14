#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "tests.h"

int main() {
    TESTS();

    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Openning error input.txt\n");
        return 1;
    }

    int N;
    fscanf(inputFile, "%d", &N);
    fclose(inputFile);

    if (N <= 0 || N >= 1000000) {
        fprintf(stderr, "Invalid N\n");
        return 1;
    }

    int* positions = (int*)malloc(N * sizeof(int));
    if (positions == NULL) {
        fprintf(stderr, "Memory error\n");
        return 1;
    }

    if (solve_n_queens(N, positions) == 0) {
        fprintf(stderr, "No solution for %d woman\n", N);
        free(positions);
        return 1;
    }

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Openning error output.txt\n");
        free(positions);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fprintf(outputFile, "%d %d\n", i, positions[i]);
    }

    fclose(outputFile);
    free(positions);

    return 0;
}