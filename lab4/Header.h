#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

extern int adj[MAX_VERTICES][MAX_VERTICES];
extern int visited[MAX_VERTICES];
extern int path[MAX_VERTICES];
extern int n;

// Функция для чтения графа из файла
void readGraphFromFile(const char* filename);

// Основная функция для поиска гамильтонова пути, начиная с каждой вершины
int findHamiltonianPath();

// Вспомогательная рекурсивная функция для поиска гамильтонова пути с конкретной стартовой позиции
int hamiltonianPath(int pos);

// Функция для вывода результата в файл
void outputResult(const char* filename);

// Функции для добавления ребра и очистки графа
void addEdge(int u, int v);
void clearGraph();
void resetGraph();
#endif // HEADER_H
