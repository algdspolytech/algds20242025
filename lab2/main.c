#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

// A function for creating a graph from an adjacency matrix
GraphMatrix* createGraphFromMatrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    GraphMatrix* graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    fscanf(file, "%d", &graph->vertexCount);

    graph->adjacencyMatrix = (int**)malloc(graph->vertexCount * sizeof(int*));
    for (int i = 0; i < graph->vertexCount; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc(graph->vertexCount * sizeof(int));
        for (int j = 0; j < graph->vertexCount; j++) {
            fscanf(file, "%d", &graph->adjacencyMatrix[i][j]);
        }
    }

    fclose(file);
    return graph;
}

// A function for creating a graph from a list of adjacencies
GraphList* createGraphFromList(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    GraphList* graph = (GraphList*)malloc(sizeof(GraphList));
    fscanf(file, "%d", &graph->vertexCount);

    graph->adjacencyList = (int*)malloc(graph->vertexCount * sizeof(int));
    for (int i = 0; i < graph->vertexCount; i++) {
        fscanf(file, "%d", &graph->adjacencyList[i]);
    }

    fclose(file);
    return graph;
}

// Graph comparison function
bool compareGraphs(GraphMatrix* matrixGraph, GraphList* listGraph) {
    if (matrixGraph->vertexCount != listGraph->vertexCount) {
        return false;
    }

    return true; // Temporarily returning true
}

// Freeing up memory
void freeGraphMatrix(GraphMatrix* graph) {
    for (int i = 0; i < graph->vertexCount; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph);
}

void freeGraphList(GraphList* graph) {
    free(graph->adjacencyList);
    free(graph);
}

int main() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("matrix.txt");
    GraphList* listGraph = createGraphFromList("list.txt");

    if (matrixGraph && listGraph) {
        if (compareGraphs(matrixGraph, listGraph)) {
            printf("The graphs match\n");
        }
        else {
            printf("The graphs do not match\n");
        }
    }

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);

    return 0;
}
