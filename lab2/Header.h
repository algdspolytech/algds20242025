#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct {
    int vertexCount;
    int** adjacencyMatrix;
} GraphMatrix;

typedef struct {
    int vertexCount;
    int* adjacencyList;
} GraphList;

GraphMatrix* createGraphFromMatrix(const char* filename);
GraphList* createGraphFromList(const char* filename);
bool compareGraphs(GraphMatrix* matrixGraph, GraphList* listGraph);
void freeGraphMatrix(GraphMatrix* graph);
void freeGraphList(GraphList* graph);

// For tests

void runAllTests();

#endif // GRAPH_H