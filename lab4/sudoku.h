#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

#define N 3 // Размер блока
#define GRID_SIZE (N * N)

// Структуры данных для танцующих ссылок
typedef struct ColumnNode {
    struct ColumnNode* left, * right, * up, * down;
    int size;
    char name;
} ColumnNode;

typedef struct Node {
    struct Node* left, * right, * up, * down;
    ColumnNode* column;
} Node;

void readInput(const char* filename, int grid[GRID_SIZE][GRID_SIZE]);
void writeOutput(const char* filename, int grid[GRID_SIZE][GRID_SIZE], bool solved);
bool solveSudokuWithDancingLinks(int grid[GRID_SIZE][GRID_SIZE]);

#endif // SUDOKU_H