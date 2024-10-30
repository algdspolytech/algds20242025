#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lab2.h"

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjList[i][j] = 0; // Инициализируем 0 (нет ребер)
        }
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjList[src][dest] = 1; // Добавляем направленное ребро
    //graph->adjList[dest][src] = 1; // Добавляем обратно для неориентированного графа
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjList[i]);
    }
    free(graph->adjList);
    free(graph);
}

bool dfsUtil(Graph* graph, int vertex, bool* visited, int targetVertex) {
    if (vertex == targetVertex) {
        return true; // Если достигли нужной вершины
    }
    visited[vertex] = true;

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjList[vertex][i] == 1 && !visited[i]) {
            if (dfsUtil(graph, i, visited, targetVertex)) {
                return true; // Если найден путь к целевой вершине
            }
        }
    }
    return false; // Путь не найден
}
bool depthFirstSearch(Graph* graph, int startVertex, int targetVertex) {
    if (graph->numVertices == 0) {
        return false; // Проверка на граф с 0 вершинами
    }
    if (startVertex >= graph->numVertices || targetVertex >= graph->numVertices) {
        return false; // Если вершины за пределами графа
    }

    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    if (visited == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для массива посещенных вершин.\n");
        return false;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false; // Инициализация массива посещенных вершин
    }

    bool result = dfsUtil(graph, startVertex, visited, targetVertex);

    free(visited);
    return result;
}
