#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_V 10

typedef struct {
    int adj[MAX_V][MAX_V];
    int num_vertices;
} Graph;

typedef struct {
    int Vertexes[MAX_V];
} UsedVertexes;
void GraphInitialise(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = 0; j < graph->num_vertices; j++) {
            graph->adj[i][j] = 0;
        }
    }
}
int FindMax(Graph graph, int StartVertex) {
    int MaxVertex = 0;
    int Maxnum = 0;
    for (int i = StartVertex; i < graph.num_vertices; i++) {
        int num = 0;
        for (int j = 0; j < graph.num_vertices; j++) {
            if (graph.adj[i][j] == 1) {
                num += 1;
            }
        }
        if (num > Maxnum) {
            Maxnum = num;
            MaxVertex = i;
        }
    }
    return MaxVertex;
}

int GraphIsNull(Graph graph) {
    for (int i = 0; i < graph.num_vertices; i++) {
        for (int j = 0; j < graph.num_vertices; j++) {
            if (graph.adj[i][j] == 1) {
                return 0;
            }
        }
    }
    return 1;
}
int FindVertexCover(Graph graph, int result_found, int StartVertex,
    UsedVertexes* array) {
    if (GraphIsNull(graph) == 1) {
        return result_found;
    }
    else {
        int Vertex = FindMax(graph, StartVertex);
        for (int i = 0; i < graph.num_vertices; i++) {
            graph.adj[Vertex][i] = 0;
            graph.adj[i][Vertex] = 0;
        }
        array->Vertexes[Vertex] = 0;
        result_found += 1;
        return FindVertexCover(graph, result_found, StartVertex, array);
    }
}