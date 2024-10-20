#pragma once
#include "pch.h"
#include <stdio.h>

// Функция для считывания строки из файла
char* Read_line(FILE* file);

// Функция для освобождения памяти, выделенной под матрицу
void Free_Matrix_adj(int** adjMatrix, int vertices);

// Функция для определения количества вершин (по количеству строк в файле)
int Count_Vertices(const char* filename);

// Функция для создания матрицы смежности и инициализации её нулями
int** Create_Matrix_adj(int vertices);

// Функция для заполнения матрицы смежности на основе файла
void Parsing_Matrix_adj(const char* filename, int** Matrix_adj, int vertices);

// Функция для вывода квадратной матрицы
void Print_Matrix(int** Matrix, int n);
