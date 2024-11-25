#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int numVertices;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* createGraphFromFile(const char* filename);
void freeGraph(Graph* graph);
int shortestPath(const Graph* graph, int start, int end);
void createTestGraph(Graph* graph, int testNum);


#endif