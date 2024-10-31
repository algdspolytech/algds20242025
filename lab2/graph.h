#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int numVertices;
    int adjList[MAX_VERTICES][MAX_VERTICES];
} Graph;

void initializeGraph(Graph* graph, int numVertices);
void addEdge(Graph* graph, int src, int dest);
bool findShortestPath(Graph* graph, int startVertex, int endVertex, int* path, int* pathLength);
void printPath(int* path, int pathLength);

#endif