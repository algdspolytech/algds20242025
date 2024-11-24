#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

#include <intrin.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int debug = 1; 

int** grid;
int** visited;

int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

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


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    TESTS();

    int M, N, K;
    printf("\n- - - - - - - - - - - - - - - - - - - ");
    printf("\nChange the value of the debug variable \n         to not see the grid.");
    printf("\n- - - - - - - - - - - - - - - - - - - ");
    printf("\nEnter M and N: ");
    scanf("%d %d", &M, &N);

    int** grid = (int**)malloc(M * sizeof(int*));
    int** visited = (int**)malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++) {
        grid[i] = (int*)malloc(N * sizeof(int));
        visited[i] = (int*)malloc(N * sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    printf("Enter count of deleted cells K: ");
    scanf("%d", &K);

    printGrid(M, N, debug, grid);

    printf("Enter x and y of every deleted cell:\n");
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        grid[x][y] = 1;
        printGrid(M, N, debug, grid);
    }

    int result = countDisconnectedAreas(M, N, grid, visited);
    printf("Count of disconnected areas: %d\n", result);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);

    return 0;
}