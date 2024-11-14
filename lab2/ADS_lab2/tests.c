#pragma warning(disable: 4996)
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "tests.h"
int M = 5;
int N = 5;


void isAvailable_incorrectCell_returnValidVal() {
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
    assert(isAvailable(3, -1, M, N, grid, visited) == 0);
    assert(isAvailable(-1, 3, M, N, grid, visited) == 0);
    assert(isAvailable(6, 1, M, N, grid, visited) == 0);
    assert(isAvailable(1, 6, M, N, grid, visited) == 0);
    assert(isAvailable(6, 6, M, N, grid, visited) == 0);
    assert(isAvailable(-1, -1, M, N, grid, visited) == 0);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void isAvailable_correctCell_returnValidVal() {
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

    assert(isAvailable(3, 3, M, N, grid, visited) == 1);
    visited[3][3] = 1;
    assert(isAvailable(3, 3, M, N, grid, visited) == 0);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void isAvailable_deletedCell_returnValidVal() {
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
    grid[1][1] = 1;
    assert(isAvailable(1, 1, M, N, grid, visited) == 0);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void DFS_gridWithOutDeletedCells_returnValidVal() {
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
    DFS(0, 0, M, N, grid, visited);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            assert(visited[i][j] == 1);
        }
    }

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void DFS_gridWithDeletedCells_returnValidVal() {
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
    grid[0][2] = 1;
    grid[1][1] = 1;
    grid[2][0] = 1;

    DFS(0, 0, M, N, grid, visited);
    assert(visited[0][0] == 1);
    assert(visited[0][1] == 1);
    assert(visited[1][0] == 1);
    assert(visited[0][3] == 0);
    assert(visited[1][2] == 0);
    assert(visited[2][1] == 0);
    assert(visited[0][2] == 0);
    assert(visited[1][1] == 0);
    assert(visited[2][0] == 0);

    DFS(0, 3, M, N, grid, visited);
    assert(visited[0][3] == 1);
    assert(visited[4][4] == 1);
    assert(visited[0][2] == 0);
    assert(visited[1][1] == 0);
    assert(visited[2][0] == 0);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void countDisconnectedAreas_EmptyGrid_returnValidVal() {
    int** grid = (int**)malloc(M * sizeof(int*));
    int** visited = (int**)malloc(M * sizeof(int*));

    for (int i = 0; i < M; i++) {
        grid[i] = (int*)malloc(N * sizeof(int));
        visited[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            grid[i][j] = 1;
            visited[i][j] = 0;
        }
    }

    assert(countDisconnectedAreas(M, N, grid, visited) == 0);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void countDisconnectedAreas_OneArea_returnValidVal() {
    int** grid = (int**)malloc(M * sizeof(int*));
    int** visited = (int**)malloc(M * sizeof(int*));

    for (int i = 0; i < M; i++) {
        grid[i] = (int*)malloc(N * sizeof(int));
        visited[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    grid[3][3] = 1; 
    grid[1][2] = 1;
    grid[4][4] = 1;

    assert(countDisconnectedAreas(M, N, grid, visited) == 1);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void countDisconnectedAreas_TwoAreas_returnValidVal() {
    int** grid = (int**)malloc(M * sizeof(int*));
    int** visited = (int**)malloc(M * sizeof(int*));

    for (int i = 0; i < M; i++) {
        grid[i] = (int*)malloc(N * sizeof(int));
        visited[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;  // Все клетки открыты
            visited[i][j] = 0;
        }
    }

    grid[1][0] = 1;
    grid[1][1] = 1;
    grid[1][2] = 1;
    grid[1][3] = 1;
    grid[1][4] = 1;


    assert(countDisconnectedAreas(M, N, grid, visited) == 2);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
}

void TESTS() {
    isAvailable_incorrectCell_returnValidVal();
    isAvailable_correctCell_returnValidVal();
    isAvailable_deletedCell_returnValidVal();
    DFS_gridWithOutDeletedCells_returnValidVal();
    DFS_gridWithDeletedCells_returnValidVal();
    countDisconnectedAreas_EmptyGrid_returnValidVal();
    countDisconnectedAreas_OneArea_returnValidVal();
    countDisconnectedAreas_TwoAreas_returnValidVal();
    printf("~~~Testing completed successfully!~~~");
}
