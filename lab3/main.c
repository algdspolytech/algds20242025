#include <stdio.h>
#include <stdlib.h>

int is_safe(int row, int col, int *columns) {
    for (int i = 0; i < row; i++) {
        if (columns[i] == col ||
            i == row ||
            columns[i] - i == col - row ||
            columns[i] + i == col + row) {
            return 0;
        }
    }
    return 1;
}

int solve_n_queens(int n, int *columns) {
    for (int i = 0; i < n; i++) columns[i] = -1;

    int row = 0;
    int cur_row = 0;
    int backtrack_depth = 0;

    while (1 == 1) {
        printf("%d %d\n", row, cur_row);
        int found = 0;
        for (int col = columns[row] + 1; col < n; col++) {
            if (is_safe(row, col, columns)) {
                columns[row] = col;
                found = 1;
                if (row == cur_row) {
                    backtrack_depth = 0;
                    cur_row++;
                }
                break;
            }
        }

        if (found) {
            if (cur_row == n) {
                return 0;
            }
            row++;
        } else {
            columns[row] = -1;
            backtrack_depth++;
            if (row - backtrack_depth < 0) row = 0;
            else row -= backtrack_depth;
        }
    }
    return 0;
}

void solve() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input && output) {
        int n;
        if (fscanf(input, "%d", &n) && n > 0 && n < 1000000) {
            if (n == 2 || n == 3) fprintf(output, "no solution\n");
            else {
                int* queen_positions = (int*)malloc(sizeof(int) * n);
                solve_n_queens(n, queen_positions);

                for (int i = 0; i < n; ++i) fprintf(output, "%d %d\n", i, queen_positions[i]);
                free(queen_positions);
            }
        }
        else {
            fprintf(output, "invalid input\n");
        }
        fclose(input);
        fclose(output);
    }
    else {
        printf("Failed to open files");
    }
}