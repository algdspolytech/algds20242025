#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 6

typedef enum {
    DIR_LEFT,  
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    NO_DIRECTION
} Dir;

typedef struct {
    int rows, cols;
    int grid[ROWS][COLS];
} Maze;

void InitializeMaze(Maze* maze, int matrix[ROWS][COLS]);
int SearchPath(Maze* maze, int row, int col, Dir* path, int* path_length);
void PrintPath(Dir* path, int path_length);
int FindExitPath(Maze* maze, int startRow, int startCol, Dir* path);