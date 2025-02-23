#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main() {
    int M, N, K;
    int debug = 1; //1 - to see the grid, 0 - to avoid seeing the grid
    int** grid;
    int** visited;
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

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