#include "grid.h"
#pragma warning(disable:4996)

int isAvailable(int x, int y, int M, int N, int** grid, int** visited) {
    if (x >= 0 && x < M && y >= 0 && y < N && grid[x][y] == 0 && visited[x][y] == 0) {
        return 1;
    }
    return 0;
}

void DFS(int x, int y, int M, int N, int** grid, int** visited) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isAvailable(nx, ny, M, N, grid, visited)) {
            DFS(nx, ny, M, N, grid, visited);
        }
    }
}

int countDisconnectedAreas(int M, int N, int** grid, int** visited) {
    int count = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                DFS(i, j, M, N, grid, visited);
                count++;
            }
        }
    }
    return count;
}

void printGrid(int M, int N, int debug, int** grid) {
    if (debug) {
        printf("  ");
        for (int j = 0; j < N; j++) {
            printf("%d ", j);
        }
        printf("\n");

        for (int i = 0; i < M; i++) {
            printf("%d ", i);
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 1) {
                    printf("X ");
                }
                else {
                    printf(". ");
                }
            }
            printf("\n");
        }
    }
}

