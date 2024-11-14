#include <stdbool.h>

bool is_safe(int row, int col, int* positions) {
    for (int i = 0; i < row; i++) {
        int other_col = positions[i];
        if (other_col == col || other_col - col == i - row || other_col - col == row - i) {
            return false;
        }
    }
    return true;
}

int solve_n_queens(int N, int* positions) {
    if (N <= 0 || N >= 1000000) {
        return 0;
    }

    if (N == 2 || N == 3) return 0;

    int row = 0, col = 0;
    while (row >= 0) {
        while (col < N && !is_safe(row, col, positions)) {
            col++;
        }
        if (col < N) {
            positions[row] = col;
            if (row == N - 1) return 1;
            row++;
            col = 0;
        }
        else {
            row--;
            if (row >= 0) col = positions[row] + 1;
        }
    }
    return 0;
}