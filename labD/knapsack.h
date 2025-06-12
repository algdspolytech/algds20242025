#pragma once

typedef struct {
    int value;
    int taken;
} Cell;

void read_input(const char* filename, int* U, int* B, int* K, int** weights, int** values);
void write_output(const char* filename, int* selected_items, int count);

void find_solution(Cell** memo, int U, int B, const int* weights, const int* values,
    int* solution, int* solution_count);

int knapsack_memoization(int U, int B, int K, const int* weights, const int* values,
    int* solution, int* solution_count);