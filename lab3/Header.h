#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  
#include <time.h>

#define MAX_VERTICES 10

// Функция для записи списка смежностей в файл
void writeAdjacencyList(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int vertices);

// Функция для записи матрицы смежностей в файл
void writeAdjacencyMatrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int vertices);

// Функция для проверки графов на совпадение
int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertices);

// Функция для генерации случайного графа
void generateRandomGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, float density);

