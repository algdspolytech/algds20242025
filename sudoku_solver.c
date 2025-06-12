#include "sudoku_solver.h"

Node *create_toroidal_matrix(Sudoku *sudoku);
void cover(Node *column);
void uncover(Node *column);
bool search(Node *header, int k, Sudoku *sudoku);
void map_sudoku_to_exact_cover(Sudoku *sudoku, int *exact_cover_matrix);
void map_exact_cover_to_sudoku(int *exact_cover_matrix, Sudoku *sudoku);
void free_memory(Node *header, int *exact_cover_matrix);

Node *create_toroidal_matrix(Sudoku *sudoku) {
    int N = sudoku->N;
    int size = N * N;
    int rows = size * size * size;
    int cols = 4 * size * size;
    
    int *exact_cover_matrix = (int *)calloc(rows * cols, sizeof(int));
    map_sudoku_to_exact_cover(sudoku, exact_cover_matrix);
    
    Node *header = (Node *)malloc(sizeof(Node));
    header->left = header->right = header->up = header->down = header;
    header->size = -1;
    header->name = -1;
    
    Node *column_nodes = (Node *)malloc(cols * sizeof(Node));
    
    for (int i = 0; i < cols; i++) {
        Node *col = &column_nodes[i];
        col->left = header->left;
        col->right = header;
        header->left->right = col;
        header->left = col;
        col->up = col->down = col;
        col->column = col;
        col->name = i;
        col->size = 0;
        
        for (int j = 0; j < rows; j++) {
            if (exact_cover_matrix[j * cols + i]) {
                Node *node = (Node *)malloc(sizeof(Node));
                node->row = j;
                node->column = col;
                node->up = col->up;
                node->down = col;
                col->up->down = node;
                col->up = node;
                
                if (col->size == 0) {
                    node->left = node->right = node;
                } else {
                    node->left = col->down->left;
                    node->right = col->down;
                    col->down->left->right = node;
                    col->down->left = node;
                }
                
                col->size++;
            }
        }
    }
    
    free(exact_cover_matrix);
    return header;
}

void cover(Node *column) {
    column->right->left = column->left;
    column->left->right = column->right;
    
    for (Node *i = column->down; i != column; i = i->down) {
        for (Node *j = i->right; j != i; j = j->right) {
            j->down->up = j->up;
            j->up->down = j->down;
            j->column->size--;
        }
    }
}

void uncover(Node *column) {
    for (Node *i = column->up; i != column; i = i->up) {
        for (Node *j = i->left; j != i; j = j->left) {
            j->column->size++;
            j->down->up = j;
            j->up->down = j;
        }
    }
    
    column->right->left = column;
    column->left->right = column;
}

bool search(Node *header, int k, Sudoku *sudoku) {
    if (header->right == header) {
        map_exact_cover_to_sudoku(NULL, sudoku);
        return true;
    }
    
    Node *column = header->right;
    for (Node *j = header->right; j != header; j = j->right) {
        if (j->size < column->size) {
            column = j;
        }
    }
    
    cover(column);
    
    for (Node *row = column->down; row != column; row = row->down) {
        for (Node *j = row->right; j != row; j = j->right) {
            cover(j->column);
        }
        
        if (search(header, k + 1, sudoku)) {
            return true;
        }
        
        for (Node *j = row->left; j != row; j = j->left) {
            uncover(j->column);
        }
    }
    
    uncover(column);
    return false;
}

void map_sudoku_to_exact_cover(Sudoku *sudoku, int *exact_cover_matrix) {
    int N = sudoku->N;
    int size = N * N;
    int cols = 4 * size * size;
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int num = sudoku->grid[row][col];
            
            if (num != 0) {
                int n = num;
                int pos_constraint = row * size + col;
                int row_constraint = row * size + (n - 1);
                int col_constraint = col * size + (n - 1);
                int box_constraint = ((row / N) * N + (col / N)) * size + (n - 1);
                
                exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + pos_constraint] = 1;
                exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + (size * size + row_constraint)] = 1;
                exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + (2 * size * size + col_constraint)] = 1;
                exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + (3 * size * size + box_constraint)] = 1;
            } else {
                for (int n = 1; n <= size; n++) {
                    int pos_constraint = row * size + col;
                    int row_constraint = row * size + (n - 1);
                    int col_constraint = col * size + (n - 1);
                    int box_constraint = ((row / N) * N + (col / N)) * size + (n - 1);
                    
                    exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + pos_constraint] = 1;
                    exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + (size * size + row_constraint)] = 1;
                    exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + (2 * size * size + col_constraint)] = 1;
                    exact_cover_matrix[(row * size * size + col * size + (n - 1)) * cols + (3 * size * size + box_constraint)] = 1;
                }
            }
        }
    }
}

void map_exact_cover_to_sudoku(int *exact_cover_matrix, Sudoku *sudoku) {
    (void)exact_cover_matrix;
    int N = sudoku->N;
    int size = N * N;
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (sudoku->grid[row][col] == 0) {
                for (int n = 1; n <= size; n++) {
                    sudoku->solution[row][col] = n;
                }
            } else {
                sudoku->solution[row][col] = sudoku->grid[row][col];
            }
        }
    }
}

void free_memory(Node *header, int *exact_cover_matrix) {
    Node *col = header->right;
    while (col != header) {
        Node *node = col->down;
        while (node != col) {
            Node *temp = node;
            node = node->down;
            free(temp);
        }
        Node *next_col = col->right;
        free(col);
        col = next_col;
    }
    free(header);
    if (exact_cover_matrix) free(exact_cover_matrix);
}

void read_input(Sudoku *sudoku, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input file");
        exit(1);
    }
    
    fscanf(file, "%d", &sudoku->N);
    int size = sudoku->N * sudoku->N;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &sudoku->grid[i][j]);
        }
    }
    
    fclose(file);
    sudoku->solved = false;
}

void write_output(Sudoku *sudoku, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening output file");
        exit(1);
    }
    
    int size = sudoku->N * sudoku->N;
    
    if (!sudoku->solved) {
        fprintf(file, "0\n");
        fclose(file);
        return;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%d ", sudoku->solution[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

bool solve_sudoku(Sudoku *sudoku) {
    Node *header = create_toroidal_matrix(sudoku);
    sudoku->solved = search(header, 0, sudoku);
    free_memory(header, NULL);
    return sudoku->solved;
}