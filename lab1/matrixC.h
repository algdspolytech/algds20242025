#ifndef MATRIX
#define MATRIX

#include <stdio.h>
#include <stdlib.h>

int** initMA(int n);
int** readMatrix(FILE* f, int** matrix, int n, int m);
void showMa(int** ma, int n, int m);
int killMatrix(int** ma, int n);
int compareMatrixes(int** A, int** B, int n);

#endif