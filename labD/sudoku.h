#include <malloc.h>

typedef struct {
    int *data;
    int n;
} sudoku;

#define ERR (sudoku){NULL,-1}
#define BAD_INPUT (-2)
#define BAD_OUTPUT (-1)
#define NO_ERR (0)
#define NO_SOLUTION (1)

sudoku create_sudoku(int n);

sudoku backtrack(sudoku s);

sudoku open_sudoku(const char *filename);

int write_sudoku(const char *filename, sudoku s);

sudoku copy_sudoku(sudoku s);

void free_sudoku(sudoku s);

int *at(sudoku s, int x, int y);

int get(sudoku s, int x, int y);

void set(sudoku s, int x, int y, int data);

int check(sudoku s1);

int check_done(sudoku s1);

int get_chunk_id(int x, int y, int n);

int solve_sudoku(const char *filename, const char *output);
