//
// Created by kiril on 11/2/2024.
//
#include "dfs.h"

#include <stdlib.h>

int **DFS_ReadFromFile(FILE *file, int *n) {
    fscanf(file, "%i", n);
    int **matrix = malloc(*n * sizeof(int *));

    for (int i = 0; i < *n; i++) {
        matrix[i] = calloc(*n, sizeof(int));
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%i", &matrix[i][j]);
        }
    }

    return matrix;
}

void DFS_MatrixDispose(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void DFS_WriteToFile(FILE *file, int **matrix, int n) {
    fprintf(file, "%i\n", n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%i ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

unsigned char IsConnectedRec(int v, int u, int **matrix, int *visited, int n) {
    if (v == u)
        return 1;
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (matrix[v][i] && !visited[i]) {
            if (IsConnectedRec(i, u, matrix, visited, n))
                return 1;
        }
    }

    return 0;
}

unsigned char DFS_IsConnected(int v, int u, int **matrix, int n) {
    if(v >= n || u >= n || v < 0 || u < 0) return 0;

    int *visited = calloc(n, sizeof(int));
    unsigned char res = 0;

    return IsConnectedRec(v, u, matrix, visited, n);
}