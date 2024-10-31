#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#define MAX_VERTICES 100

int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int numVertices;

int dfs(int vertex, int target) {
    visited[vertex] = 1;
    if (vertex == target) {
        return 1;
    }
    for (int i = 0; i < numVertices; i++) {
        if (adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            if (dfs(i, target)) {
                return 1;
            }
        }
    }
    return 0;
}

int CorrectNumOfPointCheck(int numVertices) {
    if (numVertices <= MAX_VERTICES) {
        return 1;
    }
    else {
        return 0;
    }
}

int MatrixCheck(int elementmatrix) {
    if (elementmatrix != 0 && elementmatrix != 1) {
        return 0;
    }
    else {
        return 1;
    }
}

int PointsCheck(int numVertices, int u, int v) {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) {
        return 0;
    }
    else {
        return 1;
    }
}