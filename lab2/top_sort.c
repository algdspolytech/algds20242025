#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
    int indegree[MAX_VERTICES];
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        graph->indegree[i] = 0;
        for (int j = 0; j < vertices; j++) {
            graph->adj[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adj[src][dest] = 1;
    graph->indegree[dest]++;
}

void topologicalSortUtil(Graph* graph, int v, int visited[], int* stack, int* stackIndex) {
    visited[v] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adj[v][i] && !visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, stackIndex);
        }
    }

    stack[(*stackIndex)++] = v;
}

void topologicalSort(Graph* graph, int* stack) {
    int visited[MAX_VERTICES] = {0};
    int stackIndex = 0;

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    // Переворачиваем стэк, чтобы получить правильный порядок
    for (int i = 0; i < stackIndex / 2; i++) {
        int temp = stack[i];
        stack[i] = stack[stackIndex - i - 1];
        stack[stackIndex - i - 1] = temp;
    }
}