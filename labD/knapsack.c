#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"




void read_input(const char* filename, int* U, int* B, int* K, int** weights, int** values) {
    FILE* file = fopen(filename, "r");
    if (!file) {
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
        exit(EXIT_FAILURE);
    }

    if (count == 0) {
        fprintf(file, "0\n");
    }
    else {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d ", selected_items[i] + 1); // items count from 0, but should count starting from 1, so +1
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void find_solution(Cell** memo, int U, int B, const int* weights, const int* values,
    int* solution, int* solution_count) {
    int current_size = B;
    *solution_count = 0;

    for (int i = U - 1; i >= 0; i--) {
        if (current_size >= weights[i] && memo[i][current_size].taken) {
            solution[(*solution_count)++] = i;
            current_size -= weights[i];
        }
    }
}

int knapsack_memoization(int U, int B, int K, const int* weights, const int* values,
    int* solution, int* solution_count) {
    // memoization table
    Cell** memo = (Cell**)malloc(U * sizeof(Cell*));
    for (int i = 0; i < U; i++) {
        memo[i] = (Cell*)malloc((B + 1) * sizeof(Cell));
        memset(memo[i], 0, (B + 1) * sizeof(Cell));
    }

    // initialize for first item
    for (int s = 0; s <= B; s++) {
        if (weights[0] <= s) {
            memo[0][s].value = values[0];
            memo[0][s].taken = 1;
        }
    }

    // fill tble
    for (int i = 1; i < U; i++) {
        for (int s = 0; s <= B; s++) {
            // option 1
            memo[i][s].value = memo[i - 1][s].value;
            memo[i][s].taken = 0;

            // option 2
            if (weights[i] <= s) {
                int new_value = memo[i - 1][s - weights[i]].value + values[i];
                if (new_value > memo[i][s].value) {
                    memo[i][s].value = new_value;
                    memo[i][s].taken = 1;
                }
            }
        }
    }

    // check if there is solution with value >= K
    int found = 0;
    for (int s = 0; s <= B; s++) {
        if (memo[U - 1][s].value >= K) {
            found = 1;
            find_solution(memo, U, s, weights, values, solution, solution_count);
            break;
        }
    }

    for (int i = 0; i < U; i++) {
        free(memo[i]);
    }
    free(memo);

    return found;
}


/*
int main() {
    int U, B, K;
    int* weights, * values;

    read_input("input.txt", &U, &B, &K, &weights, &values);

    int* solution = (int*)malloc(U * sizeof(int));
    int solution_count = 0;

    int found = knapsack_memoization(U, B, K, weights, values, solution, &solution_count);

    write_output("output.txt", found ? solution : NULL, found ? solution_count : 0);

    free(weights);
    free(values);
    free(solution);

    return 0;
}*/