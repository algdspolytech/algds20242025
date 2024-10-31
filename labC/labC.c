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

void InitializeMaze(Maze* maze, int matrix[ROWS][COLS]) {
    maze->rows = ROWS;
    maze->cols = COLS;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze->grid[i][j] = matrix[i][j];
        }
    }
}

int SearchPath(Maze* maze, int row, int col, Dir* path, int* path_length) {
    if (row < 0 || col < 0 || row >= maze->rows || col >= maze->cols) {
        return 0;
    }

    if (maze->grid[row][col] != 0) {
        return 0;
    }

    if (row == maze->rows - 1 && col == maze->cols - 1) {
        *path_length = 0;
        return 1;
    }

    maze->grid[row][col] = 2;

    Dir moves[4] = { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN };
    int row_change[] = { 0, -1, 0, 1 };
    int col_change[] = { -1, 0, 1, 0 };

    for (int i = 0; i < 4; i++) {
        int new_row = row + row_change[i];
        int new_col = col + col_change[i];

        if (SearchPath(maze, new_row, new_col, path, path_length)) {
            path[*path_length] = moves[i];
            (*path_length)++;
            return 1;
        }
    }

    maze->grid[row][col] = 0;
    return 0;
}

void PrintPath(Dir* path, int path_length) {
    if (path_length > 0) {
        printf("START");
        for (int i = path_length - 1; i >= 0; i--) {
            printf(" -> ");
            switch (path[i]) {
            case DIR_LEFT: printf("left"); break;
            case DIR_UP: printf("up"); break;
            case DIR_RIGHT: printf("right"); break;
            case DIR_DOWN: printf("down"); break;
            default: break;
            }
        }
        printf(" -> EXIT\n");
    }
    else {
        printf("Path not found\n");
    }
}

int FindExitPath(Maze* maze, int startRow, int startCol, Dir* path) {
    int path_length = 0;
    int found = SearchPath(maze, startRow, startCol, path, &path_length);
    if (found) {
        return path_length;
    }
    else {
        return 0;
    }

}