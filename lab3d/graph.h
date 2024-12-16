#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_VERTICES 1000

typedef struct {
    int* adj[MAX_VERTICES]; // Списки смежности
    int size[MAX_VERTICES]; // Размер каждого списка
    int visited[MAX_VERTICES]; // Для отслеживания посещенных вершин
} Graph;

// Инициализация графа
void initGraph(Graph* graph, int V);

// Добавление ребра в граф
void addEdge(Graph* graph, int u, int v);

// Рекурсивный поиск пути
bool dfs(Graph* graph, int v, int t, int K, int length, int* path, int* pathLength);

#endif // GRAPH_H