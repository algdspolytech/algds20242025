#include "longestPath.h"
#include <stdio.h>
#include <stdbool.h>

void initGraph(Graph *graph, int vertices) {
    graph->num_vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adj[i][j] = 0;
        }
    }
}

void addEdge(Graph *graph, int u, int v) {
    graph->adj[u - 1][v - 1] = 1;
    graph->adj[v - 1][u - 1] = 1; // Граф неориентированный
}

bool dfs(Graph *graph, int current, int target, int K, int length, bool *visited, int *path, int *pathLength) {
    visited[current] = true;
    path[(*pathLength)++] = current + 1;

    if (current == target && length >= K) {
        return true;
    }

    for (int i = 0; i < graph->num_vertices; i++) {
        if (graph->adj[current][i] && !visited[i]) {
            if (dfs(graph, i, target, K, length + 1, visited, path, pathLength)) {
                return true;
            }
        }
    }

    visited[current] = false;
    (*pathLength)--;
    return false;
}

bool findPath(Graph *graph, int s, int t, int K, int *path, int *pathLength) {
    bool visited[MAX_VERTICES] = {0};
    *pathLength = 0;
    return dfs(graph, s - 1, t - 1, K, 0, visited, path, pathLength);
}