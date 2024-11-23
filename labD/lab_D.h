#define HAMILTONIAN_PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 1000

extern int graph[MAX_NODES][MAX_NODES];
extern int adjList[MAX_NODES][MAX_NODES];
extern int adjListSize[MAX_NODES];
extern bool visited[MAX_NODES];
extern int path[MAX_NODES];
extern int vertexCount;

// Функции
int cmpfunc(const void* a, const void* b);
void initializeGraph();
void insertEdge(int u, int v);
bool depthFirstSearch(int current, int depth);
bool findHamiltonianPath();
void loadGraph(const char* filename);
void saveResult(const char* filename);
