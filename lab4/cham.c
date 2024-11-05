#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_VERTICES 1000

int adj[MAX_VERTICES][MAX_VERTICES]; // Матрица смежности для графа
int visited[MAX_VERTICES]; // Массив для отслеживания посещенных вершин
int path[MAX_VERTICES]; // Массив для хранения пути
int n; // Количество вершин

// Очистка графа
void clearGraph() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
        path[i] = -1;
    }
}
// Вспомогательная функция для сброса состояния графа
void resetGraph() {
    n = 0;
    clearGraph();
}
// Функция добавления ребра в граф
void addEdge(int u, int v) {
    // Поскольку u и v начинаются с 1, мы уменьшаем их на 1 для индексации массива
    adj[u - 1][v - 1] = 1;  // Добавляем ребро u-v
    adj[v - 1][u - 1] = 1;  // Добавляем ребро v-u (для неориентированного графа)
}

// Определение гамильтонова пути от конкретной стартовой позиции
// Определение гамильтонова пути от конкретной стартовой позиции 
int hamiltonianPath(int pos) {
    if (pos == n) {
        return 1; // Найден гамильтонов путь
    }

    for (int v = 0; v < n; v++) {
        if (!visited[v]) {
            int canAdd = (pos == 0 || adj[path[pos - 1] - 1][v - 1]); // Используем v - 1 для индексации
            if (canAdd) {
                path[pos] = v; // Добавление вершины в путь (используем v как есть, поскольку он начинается с 1)
                visited[v - 1] = 1; // Пометка вершины как посещенной
                if (hamiltonianPath(pos + 1)) {
                    return 1; // Если найден путь, возвращаем успех
                }
                // Откат
                visited[v - 1] = 0; // Используем v - 1 для индексации
                path[pos] = -1; // Сброс пути
            }
        }
    }
    return 0; // Гамильтонов путь не найден
}
// Основная функция для поиска гамильтонова пути, начиная с каждой вершины
int findHamiltonianPath() {
    for (int startVertex = 1; startVertex <= n; startVertex++) { // Начинаем с 1
        // Очищаем массивы перед началом поиска с новой вершины
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
            path[i] = -1;
        }
        path[0] = startVertex; // Устанавливаем первую вершину (начинаем с 1)
        visited[startVertex - 1] = 1; // Помечаем как посещенную
        if (hamiltonianPath(1)) {
            return 1;
        }
    }
    return 0;
}

void readGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла");
        exit(1);
    }

    fscanf(file, "%d", &n);  // Считываем количество вершин
    clearGraph();            // Очищаем граф

    for (int i = 1; i <= n; i++) { // Начинаем с 1
        int vertex;
        // Считываем смежные вершины для вершины i
        while (fscanf(file, "%d", &vertex) == 1) {
            if (vertex > 0 && vertex <= n) {
                addEdge(i, vertex); // Добавляем ребро, номер вершины передаем как есть
            }
        }
    }

    fclose(file);
}

// Функция для вывода результата в файл
void outputResult(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка при открытии файла для записи");
        exit(1);
    }

    if (findHamiltonianPath()) {
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d ", path[i] + 1); // Выводим индексы +1, чтобы начинались с 1
        }
        fprintf(file, "\n");
    }
    else {
        fprintf(file, "0\n");
    }

    fclose(file);
}
