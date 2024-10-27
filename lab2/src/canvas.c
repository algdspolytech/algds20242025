#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"

// Структура для направлений
typedef struct {
    int dx;
    int dy;
} Direction;

// Направления движения: вниз, вверх, вправо, влево
Direction directions[4] = {
    {1, 0},   // вниз
    {-1, 0},  // вверх
    {0, 1},   // вправо
    {0, -1}   // влево
};

// Рекурсионный поиск в глубину, проходя по всем связанным клеткам c оптимизацией
void dfs(int** canvas, int** visited, int m, int n, int x, int y) {
    visited[x][y] = 1;

    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i].dx;
        int ny = y + directions[i].dy;

        if (nx >= 0 && nx < m && ny >= 0 && ny < n && canvas[nx][ny] == 1 && !visited[nx][ny]) {
            dfs(canvas, visited, m, n, nx, ny);
        }
    }
}

// Вспомогательная функция для создания холста с заданными размерами и значениями
int** createCanvas(int m, int n, int defaultValue) {
    int** canvas = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        canvas[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            canvas[i][j] = defaultValue;
        }
    }
    return canvas;
}

// Вспомогательная функция для освобождения памяти холста
void freeCanvas(int** canvas, int m) {
    for (int i = 0; i < m; i++) {
        free(canvas[i]);
    }
    free(canvas);
}

// Функция для создания массива посещений
int** createVisited(int m, int n) {
    return createCanvas(m, n, 0);
}

// Функция для подсчета количества частей на холсте
int countComponents(int** canvas, int m, int n) {
    int** visited = createVisited(m, n);
    int components = 0;

    // Поиск компонент связности
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (canvas[i][j] == 1 && !visited[i][j]) {
                dfs(canvas, visited, m, n, i, j);
                components++;
            }
        }
    }

    freeCanvas(visited, m);  // Освобождаем память для visited
    return components;
}
