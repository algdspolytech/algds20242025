#include "cells.h"

#include <stdio.h>

int main() {
    int m, n, k;
    Cell removed[MAX_M * MAX_N];

    FILE * input = fopen("test_input.txt", "r");
    if (!input) {
        printf("Can't find test_input.txt\n");
        return 1;
    }
    /*
    Файл в формате: в первой строчке размеры клетчатой бумаги m, n и к - 
    количество удалённых клеток
    В следующих k строчках - координаты удалённых клеток
    */

    fscanf(input, "%d %d %d", & m, & n, & k);
    for (int i = 0; i < k; i++) {
        fscanf(input, "%d %d", & removed[i].x, & removed[i].y);
    }
    fclose(input);

    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, m, n);
    removeCells(grid, removed, k);
    int components = countConnectedComponents(grid, m, n);

    printf("Number of connected components: %d\n", components);
    return 0;
}