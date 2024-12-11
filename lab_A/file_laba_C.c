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

т