#pragma once

#include <stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_VERTICES 50

typedef struct {
    int numVertices;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// ��������� BFS
int shortestPath(const char* filename);