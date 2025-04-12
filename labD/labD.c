#include <stdio.h>
#include <stdlib.h>
#include "labD.h"

int isSafe(int* board, int row, int col, int N) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row) {
            return 0;  // не безопасно
        }
    }
    return 1;  // безопасно
}

int solveNQueensUtil(int* board, int row, int N) {
    if (row == N) {
        return 1;  // решение есть
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row] = col;  // расставляем ферзя
            if (solveNQueensUtil(board, row + 1, N)) {
                return 1;
            }
            board[row] = -1;  // отмена расстановки
        }
    }

    return 0;  // нет решения
}

void solveNQueens(int N, int* solution) {
    int* board = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        board[i] = -1;
    }

    if (solveNQueensUtil(board, 0, N)) {
        for (int i = 0; i < N; i++) {
            solution[i] = board[i]; // если решение есть, берем его себе
        }
    }

    free(board);
}

void solveNQueensFiles(const char* input_filename, const char* output_filename) {
    FILE* input = fopen(input_filename, "r");
    FILE* output = fopen(output_filename, "w");

    if (input == NULL || output == NULL) {
        printf("Error Opening files\n");
        return;
    }

    int N;
    fscanf_s(input, "%d", &N);
    fclose(input);
    int* solution = (int*)malloc(N * sizeof(int));
    if (solution == NULL) {
        printf("Error allocating memory to solution during solveNQueensFiles\n");
        fclose(output);
        return;
    }

    solveNQueens(N, solution);

    for (int i = 0; i < N; i++) {
        fprintf(output, "%d %d\n", i, solution[i]);
    }

    fclose(output);

    free(solution);
}
