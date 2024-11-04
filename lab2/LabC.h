#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"


typedef struct Graph {
	int v; // Кол-во вершин

	int** adjacency; // Список смежности графа
	char** names; // Имя каждой вершины
} Graph;


Graph* init_graph(); // Создание графа

void add_vertex(Graph* graph, char* vertex); // Функция добавления вершины
void add_edge(Graph* graph, char* v1, char* v2); // Добавляем грань из v1 в v2

int get_vertex_index(Graph* graph, char* vertex); // Функция для получения индекса вершины по ее названию
char* get_vertex_name(Graph* graph, int index); // Функция для получения имени вершины по индексу

Graph* load_graph(FILE* file); // Получаем из файла граф список вершин
void topological_sort(Graph* graph, Stack* stack, int v, int* visited); // Функция топологической сортировки
int acycle_check(Graph* graph); // Функция для проверки графа на ацикличность
