#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h> 

typedef enum { NO, YES } Flag_t;

bool isSafe(Flag_t** board, int row, int col, int size);
bool findSolution(Flag_t** board, int n, int m);
int solveNQueens(const char* inputFilename, const char* outputFilename);

#endif 