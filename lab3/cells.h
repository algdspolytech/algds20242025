#pragma once
#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

#define MAX_M 100
#define MAX_N 100

typedef struct {
    int x;
    int y;
}
Cell;

void initializeGrid(bool grid[MAX_M][MAX_N], int m, int n);
void removeCells(bool grid[MAX_M][MAX_N],
    const Cell removed[], int k);
int countConnectedComponents(bool grid[MAX_M][MAX_N], int m, int n);
void dfs(bool grid[MAX_M][MAX_N], bool visited[MAX_M][MAX_N], int x, int y, int m, int n);

#endif