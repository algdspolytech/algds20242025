#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "test.h"


bool isSafe(Flag_t** board, int row, int col, int size) {
 
    for (int i = 0; i < size; i++) {
        if (board[row][i] == YES) return false;
    }

    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == YES) return false;
    }

    
    for (int i = row, j = col; i < size && j >= 0; i++, j--) {
        if (board[i][j] == YES) return false;
    }

    return true;
}

bool findSolution(Flag_t** board, int n, int m) {
    if (m == n) return true; 

    for (int i = 0; i < n; i++) {
        if (isSafe(board, m, i, n)) {
            board[m][i] = YES; 
            if (findSolution(board, n, m + 1)) return true; 
            board[m][i] = NO; 
        }
    }
    return false; 
}

int solveNQueens(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 0;
    }

    int n;
    if (fscanf(inputFile, "%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid board size\n");
        fclose(inputFile);
        return 0;
    }
    fclose(inputFile);

    Flag_t** board = (Flag_t**)malloc(n * sizeof(Flag_t*));
    if (board == NULL) {
        perror("Memory allocation failed");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        board[i] = (Flag_t*)malloc(n * sizeof(Flag_t));
        if (board[i] == NULL) {
            perror("Memory allocation failed");
            for (int j = 0; j < i; j++) free(board[j]);
            free(board);
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = NO;
        }
    }

    if (!findSolution(board, n, 0)) {
        fprintf(stderr, "No solution found\n");
        for (int i = 0; i < n; i++) free(board[i]);
        free(board);
        return 0;
    }


    FILE* outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        for (int i = 0; i < n; i++) free(board[i]);
        free(board);
        return 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == YES) {
                fprintf(outputFile, "%d %d\n", n - 1 - i, j);
            }
        }
    }

    fclose(outputFile);
    for (int i = 0; i < n; i++) free(board[i]);
    free(board);
    return 1;
}
