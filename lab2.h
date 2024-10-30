#pragma once
#include <stdbool.h>

typedef struct Graph {
    int numVertices;
    int** adjList;  // ������ ���������� �� ������� ���������
} Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
bool depthFirstSearch(Graph* graph, int startVertex, int targetVertex);
void freeGraph(Graph* graph);