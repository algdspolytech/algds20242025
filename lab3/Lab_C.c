#include <stdio.h>
#include <stdlib.h>

#include "Lab_C.h"

// Функция для считывания матрицы смежности из файла
int** readMatrix(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Определяем размер матрицы
    *rows = 0;
    *cols = 0;
    int ch;
    int currentCols = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            currentCols++;
        }
        else if (ch == '\n') {
            (*rows)++;
            if (*cols == 0) {
                *cols = currentCols + 1; // Количество столбцов в первой строке
            }
            currentCols = 0;
        }
    }
    fseek(file, 0, SEEK_SET); // Возвращаемся к началу файла

    // Выделяем память под матрицу
    int** matrix = (int**)malloc(*rows * sizeof(int*));
    for (int i = 0; i < *rows; i++) {
        matrix[i] = (int*)malloc(*cols * sizeof(int));
    }

    // Читаем данные из файла в матрицу
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

// Функция для создания списка смежности
int** createAdjacencyList(int** matrix, int rows, int cols, int** adjacencySizes) {
    int** adjacencyList = (int**)malloc(rows * sizeof(int*));
    *adjacencySizes = (int*)malloc(rows * sizeof(int)); // Массив для хранения количества смежных вершин

    for (int i = 0; i < rows; i++) {
        (*adjacencySizes)[i] = 0;
        // Считаем количество смежных вершин для текущей вершины
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                (*adjacencySizes)[i]++;
            }
        }
        // Выделяем память для списка смежных вершин текущей вершины
        adjacencyList[i] = (int*)malloc((*adjacencySizes)[i] * sizeof(int));
        int index = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                adjacencyList[i][index++] = j + 1; // Нумерация вершин с 1
            }
        }
    }
    return adjacencyList;
}

// Функция для записи списка смежности в файл
void writeAdjacencyListToFile(const char* filename, int** adjacencyList, int* adjacencySizes, int rows) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < rows; i++) {
        fprintf(file, "%d:", i + 1); // Нумерация вершин с 1
        for (int j = 0; j < adjacencySizes[i]; j++) {
            fprintf(file, " %d", adjacencyList[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}