#ifndef LABC_H
#define LABC_H

#define MAX_VERTICES 30

typedef struct Vertex {
    int adj[MAX_VERTICES];
    int degree;
} Vertex;

typedef struct Graph {
    Vertex vertices[MAX_VERTICES];
    int num_vertices;
} Graph;

Graph* createGraph(int num_vertices);

void addEdge(Graph* graph, int src, int dest);

Graph* readGraphFile(const char* filename);

int* findPath(Graph* graph, int start, int end);

#endif
