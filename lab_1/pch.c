//
// pch.cpp
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adj[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adj[src][dest] = 1;
    graph->adj[dest][src] = 1; // Для неориентированного графа
}

int dfs(Graph* graph, int src, int dest, int visited[]) {
    if (src == dest) {
        return 1; // Путь найден
    }

    visited[src] = 1; // Помечаем текущую вершину как посещенную

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adj[src][i] && !visited[i]) {
            if (dfs(graph, i, dest, visited)) {
                return 1; // Путь найден в рекурсивном вызове
            }
        }
    }
    return 0; // Путь не найден
}

int pathExists(Graph* graph, int src, int dest) {
    int visited[MAX_VERTICES] = { 0 }; // Массив для отслеживания посещенных вершин
    return dfs(graph, src, dest, visited);
}

void freeGraph(Graph* graph) {
    free(graph);
}

int main() {
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);

    int src = 0, dest = 4;
    if (pathExists(graph, src, dest)) {
        printf("Path exists between %d and %d\n", src, dest);
    }
    else {
        printf("No path exists between %d and %d\n", src, dest);
    }

    freeGraph(graph);
    return 0;
}


