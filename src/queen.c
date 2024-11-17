#include "queen.h"

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

void solveNQueensUtil(char* res, int row) {
     if (row == N) {
        // Все N ферзей расставлены, выводим решение
        for (int i = 0; i < N; i++) {
            res[i * 4] = i + '0';
            res[i * 4 + 1] = ' ';
            res[i * 4 + 2] = queens[i] + '0';            
            res[i * 4 + 3] = '\n';
        }
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            queens[row] = col; // Ставим ферзя
            solveNQueensUtil(res, row + 1); 
            queens[row] = -1;
        }
    }
}

char* solveNQueens(int n) {
    if(n <= 0 || n >= MAX_N) return NULL;
    N = n;
    char* str = malloc(N * 4 + 1);
    str[0] = 'g';
    str[N * 4] = '\0';
    for (int i = 0; i < n; i++) {
        queens[i] = -1; 
    }
    solveNQueensUtil(str, 0); 
    return str;
}
