#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <stdlib.h>

typedef enum {
    GRID_SUCCESS = 0,
    GRID_NO_SOLUTION = 1,
    GRID_INPUT_ERROR = -2,
    GRID_OUTPUT_ERROR = -1
} GridStatus;

typedef struct {
    int* cells;       
    int block_size;   
} Grid;


Grid create_grid(int block_size);
void destroy_grid(Grid grid);
Grid read_grid_from_file(const char* filename);
GridStatus write_grid_to_file(const char* filename, Grid grid);
int* access_grid_cell(Grid grid, int row, int col);
int is_grid_valid(Grid grid);
int is_grid_complete(Grid grid);
Grid solve_grid_backtracking(Grid grid);
GridStatus solve_grid(const char* input_file, const char* output_file);

#endif 
