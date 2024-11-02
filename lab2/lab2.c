//
// Created by Александр on 02.11.2024.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Функция считывания строки в файле
char* Read_line(FILE* file) {
    char* line = malloc(sizeof(char));
    if (line == NULL) {
        free(line);
        printf("Ошибка выделения памяти");
        return NULL;
    }
    char c;
    int i = 1;
    while (fscanf(file, "%c", &c) != EOF) {
        if (c == '\n' || c == '\0') {
            break;
        }
        line[i - 1] = c;
        i++;
        line = realloc(line, i * sizeof(char));
        if (line == NULL) {
            free(line);
            printf("Ошибка выделения памяти");
            return NULL;
        }
    }
    line[i-1] = '\0';
    return line;
}

// Функция для освобождения памяти, выделенной под матрицу
void Free_Matrix_adj(int** Matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(Matrix[i]);
        Matrix[i] = NULL;
    }
    free(Matrix);
    Matrix = NULL;
}

// Функция для определения количества вершин (по количеству строк в файле)
int Count_Vertices(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return -1;
    }

    int vertices = 0;
    int u;

    while (1) {
        char* line = Read_line(file);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        vertices++;
        free(line);
    }

    fclose(file);
    return vertices;
}

// Функция для создания матрицы смежности и инициализации её нулями
int** Create_Matrix_adj(int vertices) {
    int** Matrix_adj = (int**)malloc(vertices * sizeof(int*));
    if (Matrix_adj == NULL) {
        free(Matrix_adj);
        return NULL;
    }
    int flag = 0;
    for (int i = 0; i < vertices; i++) {
        Matrix_adj[i] = (int*)malloc(vertices * sizeof(int));
        if (Matrix_adj[i] == NULL) {
            flag = 1;
        }
        if (flag == 0) {
            for (int j = 0; j < vertices; j++) {
                Matrix_adj[i][j] = 0; // Инициализируем нулями
            }
        }
    }
    if (flag == 1) {
        Free_Matrix_adj(Matrix_adj, vertices);
        return NULL;
    }
    return Matrix_adj;
}

// Функция для заполнения матрицы смежности на основе файла
void Parsing_Matrix_adj(const char* filename, int** Matrix_adj, int vertices) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }

    int i, j;

    while (1) {
        char* line = Read_line(file);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        char* line_cp = line;
        char* token;

        // Первым считываем вершину (номер перед двоеточием)
        sscanf(line, "%d:", &j);

        // Получаем список смежных вершин (разделённых пробелами)
        token = strtok(
            line, " "); // Первым токеном будет номер вершины j, его пропускаем
        token = strtok(NULL, " "); // Следующие токены — это смежные вершины

        while (token != NULL) {
            i = atoi(token); // Преобразуем строку в число
            Matrix_adj[j][i] = 1;
            Matrix_adj[i][j] = 1;
            token = strtok(NULL, " "); // Переходим к следующему токену
        }
        free(line_cp);
    }

    fclose(file);
}

// Функция для вывода квадратной матрицы
void Print_Matrix(int** Matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    return 0;
}