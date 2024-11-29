#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjLists[MAX_VERTICES];
    int numVertices;
} Graph;

// Функции для работы с графом
Node* createNode(int vertex);
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
Graph* readGraphFromFile(const char* filename);
void findShortestPath(Graph* graph, int startVertex, int endVertex);
#endif // GRAPH_H
