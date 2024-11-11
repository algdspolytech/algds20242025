#ifndef LONGEST_PATH_H
#define LONGEST_PATH_H

#include <stdbool.h>

#define MAX_VERTICES 1000

typedef struct {
    int adj[MAX_VERTICES][MAX_VERTICES]; // Матрица смежности
    int num_vertices;
} Graph;

// Функция для создания графа
void initGraph(Graph *graph, int vertices);

// Функция для добавления ребра в граф
void addEdge(Graph *graph, int u, int v);

// Основная функция для поиска пути
bool findPath(Graph *graph, int s, int t, int K, int *path, int *pathLength);

#endif 