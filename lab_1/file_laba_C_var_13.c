#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define MAX 100

int M, N;
int K;
int grid[MAX][MAX];
int visited[MAX][MAX];
int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int isValid(int x, int y) {
    return (x >= 0 && x < M && y >= 0 && y < N && grid[x][y] == 1 && !visited[x][y]);
}

void dfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (isValid(nx, ny)) {
            dfs(nx, ny);
        }
    }
}

int countConnectedComponents() {
    int components = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 1;
            visited[i][j] = 0;
        }
    }
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        grid[x - 1][y - 1] = 0;
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                dfs(i, j);
                components++;
            }
        }
    }
    return components;
}

int main() {
    printf("Enter the grid dimensions M and N: ");
    scanf("%d %d", &M, &N);
    printf("Enter the number of deleted cells: ");
    scanf("%d", &K);
    int result = countConnectedComponents();
    printf("The number of connected components remaining is: %d\n", result);
    return 0;
}

// Lab C test 

#include <stdio.h>

extern int M, N, K, grid[100][100];

int countConnectedComponents();

void runTests() {
    // Тест 1: Сетка 3x3 без удаленных ячеек
    M = 3; N = 3; K = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 1;
        }
    }
    printf("Тест 1 (Сетка 3x3 без удаления) : %d\n", countConnectedComponents());  // Ожидается: 1

    // Тест 2: Сетка 3x3 с удаленными ячейками в разных позициях
    M = 3; N = 3; K = 2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 1;
        }
    }
    grid[0][0] = 0;  // Удаление ячейки (1,1)
    grid[2][2] = 0;  // Удаление ячейки (3,3)
    printf("Тест 2 (Сетка 3x3 с 2 удалениями) : %d\n", countConnectedComponents());  // Ожидается: 2

    // Тест 3: Сетка 5x5, где все ячейки удалены
    M = 5; N = 5; K = 25;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;  // Все ячейки удалены
        }
    }
    printf("Тест 3 (Сетка 5x5 все ячейки удалены) : %d\n", countConnectedComponents());  // Ожидается: 0

    // Тест 4: Сетка 5x5 с некоторыми удаленными ячейками, образующими кластеры
    M = 5; N = 5; K = 5;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 1;  // Инициализация 1
        }
    }
    grid[1][1] = 0;  // Удаление (2,2)
    grid[1][2] = 0;  // Удаление (2,3)
    grid[2][1] = 0;  // Удаление (3,2)
    grid[3][3] = 0;  // Удаление (4,4)
    grid[4][4] = 0;  // Удаление (5,5)
    printf("Тест 4 (Сетка 5x5 с удалениями в кластерах) : %d\n", countConnectedComponents());  // Ожидается: 3

    // Тест 5: Сетка 4x4 с несколькими отсоединенными компонентами
    M = 4; N = 4; K = 2;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 1;  // Инициализация 1
        }
    }
    grid[0][1] = 0;  // Удаление (1,2)
    grid[2][2] = 0;  // Удаление (3,3)
    printf("Тест 5 (Сетка 4x4 с несколькими компонентами) : %d\n", countConnectedComponents());  // Ожидается: 2
}

int main() {
    // Запуск тестов
    runTests();
    return 0;
}
