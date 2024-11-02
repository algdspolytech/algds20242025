#ifndef DFS_H
#define DFS_H
#include<stdio.h>

int **DFS_ReadFromFile(FILE* file, int* n);
void DFS_MatrixDispose(int **matrix, int n);
void DFS_WriteToFile(FILE *file, int **matrix, int n);
unsigned char DFS_IsConnected(int v, int u, int **matrix, int n);

#endif //DFS_H
