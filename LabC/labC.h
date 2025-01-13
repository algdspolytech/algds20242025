#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

typedef struct GraphStructure {
    int vertexCount; // Кол-во вершин
    int** adjacencyList; // Список смежности графа
    char** vertexNames; // Имя каждой вершины
} GraphStructure;

GraphStructure* create_graph(); // Создание графа
void insert_vertex(GraphStructure* graph, char* vertex); // Функция добавления вершины
void insert_edge(GraphStructure* graph, char* source, char* destination); // Добавляем грань из source в destination
int find_vertex_index(GraphStructure* graph, char* vertex); // Функция для получения индекса вершины по её названию
char* fetch_vertex_name(GraphStructure* graph, int index); // Функция для получения имени вершины по индексу
GraphStructure* read_graph(FILE* file); // Получаем из файла граф
void perform_topological_sort(GraphStructure* graph, Stack* stack, int vertex, int* visited); // Функция топологической сортировки
int verify_acylclic(GraphStructure* graph); // Функция для проверки графа на ацикличность
