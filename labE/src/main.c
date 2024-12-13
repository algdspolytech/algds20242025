#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 20

int queens[MAX_N]; 
int N; 

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (queens[i] == col || abs(queens[i] - col) == abs(i - row)) {
            return 0; 
        }
    }
    return 1; 
}

void solveNQueensUtil(int row) {
    if (row == N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (queens[i] == j) {
                    printf(" Q ");
                } else {
                    printf(" . ");
                }
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            queens[row] = col; 
            solveNQueensUtil(row + 1); 
        }
    }
}

void solveNQueens(int n) {
    N = n;
    for (int i = 0; i < N; i++) {
        queens[i] = -1; 
    }
    solveNQueensUtil(0); 
}

int main() {
    printf("Введите размер шахматной доски (N): ");
    scanf("%d", &N);
    if (N > MAX_N) {
        printf("Размер доски не должен превышать %d.\n", MAX_N);
        return 1;
    }
    solveNQueens(N);
    return 0;
}
