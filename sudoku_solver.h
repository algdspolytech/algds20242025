#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 9

typedef struct Node {
    struct Node *left, *right, *up, *down;
    struct Node *column;
    int row, size, name;
} Node;

typedef struct {
    int N;
    int grid[MAX_SIZE][MAX_SIZE];
    int solution[MAX_SIZE][MAX_SIZE];
    bool solved;
} Sudoku;

void read_input(Sudoku *sudoku, const char *filename);
void write_output(Sudoku *sudoku, const char *filename);
bool solve_sudoku(Sudoku *sudoku);

#endif