#define _CRT_SECURE_NO_WARNINGS
#include "cells.h"
#include <assert.h>
#include <stdio.h>

void TestInitializeGrid_AllCellsTrue_no1() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 5, 5);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            assert(grid[i][j] == true);
        }
    }
}

void TestInitializeGrid_ZeroDimensions_no2() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 0, 0);
}

void TestRemoveCells_CorrectCellsRemoved_no3() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 5, 5);

    Cell removed[] = {{1, 1}, {2, 2}, {3, 3}};
    removeCells(grid, removed, 3);

    assert(grid[1][1] == false);
    assert(grid[2][2] == false);
    assert(grid[3][3] == false);
    assert(grid[0][0] == true);
}

void TestRemoveCells_NoCellsRemoved_no4() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 5, 5);

    Cell removed[] = {};
    removeCells(grid, removed, 0);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            assert(grid[i][j] == true);
        }
    }
}

void TestCountConnectedComponents_SingleComponent_no5() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 3, 3);

    int count = countConnectedComponents(grid, 3, 3);
    assert(count == 1);
}

void TestCountConnectedComponents_MultipleComponents_no6() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 3, 3);

    Cell removed[] = {{1, 1}};
    removeCells(grid, removed, 1);

    int count = countConnectedComponents(grid, 3, 3);
    assert(count == 1);
}

void TestCountConnectedComponents_AllCellsRemoved_no7() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 3, 3);

    Cell removed[] = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0}, {1, 1}, {1, 2},
        {2, 0}, {2, 1}, {2, 2}
    };
    removeCells(grid, removed, 9);

    int count = countConnectedComponents(grid, 3, 3);
    assert(count == 0);
}

void TestCountConnectedComponents_EdgeCase_no8() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 2, 2);

    Cell removed[] = {{0, 0}, {1, 1}};
    removeCells(grid, removed, 2);

    int count = countConnectedComponents(grid, 2, 2);
    assert(count == 2);
}

void TestDFS_OneComponent_no9() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 4, 4);

    bool visited[MAX_M][MAX_N] = {0};
    dfs(grid, visited, 0, 0, 4, 4);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(visited[i][j] == true);
        }
    }
}

void TestDFS_DisconnectedCells_no10() {
    bool grid[MAX_M][MAX_N];
    initializeGrid(grid, 3, 3);

    grid[0][0] = false;
    bool visited[MAX_M][MAX_N] = {0};

    dfs(grid, visited, 0, 1, 3, 3);

    assert(visited[0][0] == false);
    assert(visited[0][1] == true);
}

int main() {
    TestInitializeGrid_AllCellsTrue_no1();
    TestInitializeGrid_ZeroDimensions_no2();
    TestRemoveCells_CorrectCellsRemoved_no3();
    TestRemoveCells_NoCellsRemoved_no4();
    TestCountConnectedComponents_SingleComponent_no5();
    TestCountConnectedComponents_MultipleComponents_no6();
    TestCountConnectedComponents_AllCellsRemoved_no7();
    TestCountConnectedComponents_EdgeCase_no8();
    TestDFS_OneComponent_no9();
    TestDFS_DisconnectedCells_no10();

    printf("All tests passed successfully.\n");
    return 0;
}