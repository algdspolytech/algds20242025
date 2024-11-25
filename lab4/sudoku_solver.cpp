#include <stdio.h>
#include <limits.h>
#include "sudoku_solver.h"

#define GRID_SIZE(g) ((g).block_size * (g).block_size)

Grid create_grid(int block_size) {
    Grid grid;
    grid.cells = (int*)malloc(sizeof(int) * GRID_SIZE(grid) * GRID_SIZE(grid));
    grid.block_size = block_size;
    return grid;
}

void destroy_grid(Grid grid) {
    if (grid.cells) {
        free(grid.cells);
    }
}

int* access_grid_cell(Grid grid, int row, int col) {
    return &(grid.cells[row * GRID_SIZE(grid) + col]);
}

int read_grid_cell(Grid grid, int row, int col) {
    return grid.cells[row * GRID_SIZE(grid) + col];
}

void write_grid_cell(Grid grid, int row, int col, int value) {
    grid.cells[row * GRID_SIZE(grid) + col] = value;
}

Grid read_grid_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return (Grid){NULL, -1};

    int block_size;
    if (fscanf(file, "%d", &block_size) != 1 || block_size < 2 || block_size > 9) {
        fclose(file);
        return (Grid){NULL, -1};
    }

    Grid grid = create_grid(block_size);
    int total_cells = GRID_SIZE(grid) * GRID_SIZE(grid);

    for (int i = 0; i < total_cells; i++) {
        if (fscanf(file, "%d", &grid.cells[i]) != 1 || grid.cells[i] < 0 || grid.cells[i] > GRID_SIZE(grid)) {
            destroy_grid(grid);
            fclose(file);
            return (Grid){NULL, -1};
        }
    }

    fclose(file);
    return grid;
}

GridStatus write_grid_to_file(const char* filename, Grid grid) {
    FILE* file = fopen(filename, "w");
    if (!file) return GRID_OUTPUT_ERROR;

    fprintf(file, "%d\n", grid.block_size);
    int total_cells = GRID_SIZE(grid) * GRID_SIZE(grid);

    for (int i = 0; i < total_cells; i++) {
        fprintf(file, "%d ", grid.cells[i]);
        if ((i + 1) % GRID_SIZE(grid) == 0) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
    return GRID_SUCCESS;
}

int is_grid_valid(Grid grid) {
    int size = GRID_SIZE(grid);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int value = read_grid_cell(grid, row, col);
            if (value == 0) continue;


            write_grid_cell(grid, row, col, 0);

            for (int i = 0; i < size; i++) {
                if (read_grid_cell(grid, row, i) == value || read_grid_cell(grid, i, col) == value) {
                    write_grid_cell(grid, row, col, value);
                    return 0;
                }
            }

            int start_row = (row / grid.block_size) * grid.block_size;
            int start_col = (col / grid.block_size) * grid.block_size;

            for (int r = start_row; r < start_row + grid.block_size; r++) {
                for (int c = start_col; c < start_col + grid.block_size; c++) {
                    if (read_grid_cell(grid, r, c) == value) {
                        write_grid_cell(grid, row, col, value);
                        return 0;
                    }
                }
            }

            write_grid_cell(grid, row, col, value);
        }
    }
    return 1;
}

int is_grid_complete(Grid grid) {
    int size = GRID_SIZE(grid);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (read_grid_cell(grid, row, col) == 0) return 0;
        }
    }
    return is_grid_valid(grid);
}

Grid solve_grid_backtracking(Grid grid) {
    int size = GRID_SIZE(grid);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (read_grid_cell(grid, row, col) == 0) {
                for (int num = 1; num <= size; num++) {
                    write_grid_cell(grid, row, col, num);
                    if (is_grid_valid(grid)) {
                        Grid solved_grid = solve_grid_backtracking(grid);
                        if (is_grid_complete(solved_grid)) {
                            return solved_grid;
                        }
                    }
                    write_grid_cell(grid, row, col, 0);
                }
                return grid; 
            }
        }
    }
    return grid;  
}

GridStatus solve_grid(const char* input_file, const char* output_file) {
    Grid grid = read_grid_from_file(input_file);
    if (grid.cells == NULL) return GRID_INPUT_ERROR;

    Grid solved_grid = solve_grid_backtracking(grid);
    GridStatus status;

    if (is_grid_complete(solved_grid)) {
        status = write_grid_to_file(output_file, solved_grid);
    } else {
        FILE* file = fopen(output_file, "w");
        if (!file) {
            destroy_grid(grid);
            return GRID_OUTPUT_ERROR;
        }
        fprintf(file, "0\n");
        fclose(file);
        status = GRID_NO_SOLUTION;
    }

    destroy_grid(grid);
    return status;
}