#pragma once

#include <stdio.h>

typedef struct {
    int vertex;
    int depth;
} StackNode;

typedef struct {
    int V, s, t, K;
    int** adj;    // Списки смежности
    int* visited; // Массив посещенных вершин
    int* path; // Массив для хранения текущего пути
    int path_length; // Длина текущего пути
} Graph;

// Функция считывания строки из файла
char* Read_line(FILE* file);

// Функция для освобождения памяти, выделенной под матрицу
void Free_Matrix_adj(int** Matrix, int vertices);

// Функция считывания параметров задачи (графа)
Graph* Parse_parameters(const char* filename, Graph* graph);

// Функция для создания матрицы смежности и инициализации её нулями
int** Create_Matrix_adj(int vertices);

// Функция создания графа
Graph* Create_graph(char* filename);

// Функция для инициализации графа и чтения данных
int Parse_Graph(Graph* graph, const char* filename);

// Итеративная функция DFS для поиска пути длиной >= K
int Find_path(Graph* graph);

// Функция для записи результата в файл
void Write_result(Graph* graph, const char* output_filename);

// Функция для освобождения выделенной памяти
void Free_memory(Graph* graph);
