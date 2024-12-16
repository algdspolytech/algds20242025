#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include "graph.h"

// Инициализация графа
void initGraph(Graph* graph, int V) {
    for (int i = 0; i < V; i++) {
        graph->adj[i] = malloc(MAX_VERTICES * sizeof(int));
        graph->size[i] = 0;
        graph->visited[i] = 0;
    }
}

// Добавление ребра в граф
void addEdge(Graph* graph, int u, int v) {
    graph->adj[u][graph->size[u]++] = v;
    graph->adj[v][graph->size[v]++] = u;
}

// Рекурсивный поиск пути
bool dfs(Graph* graph, int v, int t, int K, int length, int* path, int* pathLength) {
    graph->visited[v] = 1;
    path[(*pathLength)++] = v + 1; // Сохраняем вершину в пути

    if (v == t && length >= K) {
        return true; // Найден путь
    }

    for (int i = 0; i < graph->size[v]; i++) {
        int neighbor = graph->adj[v][i];
        if (!graph->visited[neighbor]) {
            if (dfs(graph, neighbor, t, K, length + 1, path, pathLength)) {
                return true;
            }
        }
    }

    graph->visited[v] = 0; // Возврат к предыдущему состоянию
    (*pathLength)--; // Удаление вершины из пути
    return false;
}
