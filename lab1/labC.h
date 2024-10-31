#ifndef LABC_H
#define LABC_H

#define MAX_VERTICES 50

typedef struct Vertex {
    int adj[MAX_VERTICES];
    int degree;
} Vertex;

typedef struct Graph {
    Vertex vertices[MAX_VERTICES];
    int num_vertices;
} Graph;

Graph* createGraph(int num_vertices);

void addEdge(Graph* graph, int source, int destination);

Graph* readGraphFromFile(const char* filename);

int* findShortestPath(Graph* graph, int start, int end);

#endif
