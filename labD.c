#include "labD.h"
#include <stdio.h>
#include <stdlib.h>


// Функция для проверки возможности поставить ферзя
bool is_safe(int row, int col, int* solution) {
    for (int i = 0; i < row; i++) {
        if (solution[i] == col ||
            abs(solution[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// Рекурсивная функция для решения задачи N ферзей
bool solve(int row, int N, int* solution) {
    if (row == N) {
        return true;
    }
    for (int col = 0; col < N; col++) {
        if (is_safe(row, col, solution)) {
            solution[row] = col;
            if (solve(row + 1, N, solution)) {
                return true;
            }
        }
    }
    return false;
}

bool solve_n_queens(int N, int* solution) {
    if (N <= 0||N>=99999||(isalpha(N)==1)) {
        return false;
    }
    return solve(0, N, solution);
}

int read_input(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть input.txt");
        return -1;
    }
    int N;
    if (fscanf(file, "%d", &N) != 1) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return N;
}

bool write_output(const char* filename, int* solution, int N) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Не удалось открыть output.txt");
        return false;
    }
    for (int row = 0; row < N; row++) {
        fprintf(file, "%d %d\n", row, solution[row]);
    }
    fclose(file);
    return true;
}

