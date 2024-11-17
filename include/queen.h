#ifndef QUEEN_H
#define QUEEN_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 20



int isSafe(int, int);
void solveNQueensUtil(char*, int);

char* solveNQueens(int);

#endif 