#include "cells.h"

#include <stdio.h>

#include <string.h>

void initializeGrid(bool grid[MAX_M][MAX_N], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = true;
        }
    }
}

void removeCells(bool grid[MAX_M][MAX_N],
    const Cell removed[], int k) {
    for (int i = 0; i < k; i++) {
        grid[removed[i].x][removed[i].y] = false;
    }
}

void dfs(bool grid[MAX_M][MAX_N], bool visited[MAX_M][MAX_N], int x, int y, int m, int n) {
    if (x < 0 || y < 0 || x >= m || y >= n || !grid[x][y] || visited[x][y]) {
        return;
    }

    visited[x][y] = true;

    dfs(grid, visited, x + 1, y, m, n);
    dfs(grid, visited, x - 1, y, m, n);
    dfs(grid, visited, x, y + 1, m, n);
    dfs(grid, visited, x, y - 1, m, n);
}

int countConnectedComponents(bool grid[MAX_M][MAX_N], int m, int n) {
    bool visited[MAX_M][MAX_N];
    memset(visited, 0, sizeof(visited));

    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] && !visited[i][j]) {
                count++;
                dfs(grid, visited, i, j, m, n);
            }
        }
    }

    return count;
}