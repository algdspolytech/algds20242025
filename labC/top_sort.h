#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

typedef struct Graph Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void topologicalSort(Graph* graph, int* stack);

#endif