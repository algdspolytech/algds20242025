#include "tests.h"
#include <string.h>
#include <assert.h>

void read_adjacency_list(int **adjacency_matrix, int n, FILE *file);
void read_adjacency_matrix(int **adjacency_matrix, int n, FILE *file);
void list_to_matrix(int **list, int **matrix, int n);
int compare_matrices(int **matrix1, int **matrix2, int n);


void create_test_matrix(int **matrix, int n, int (*values)[4])
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = values[i][j];
        }
    }
}

void test_read_adjacency_list_no1(void)
{
    const int n = 4;
    int **adjacency_list = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adjacency_list[i] = malloc(n * sizeof(int));
    }

    FILE *file = tmpfile();
    if (!file) {
        perror("tmpfile");
        abort();
    }

    fprintf(file, "1 0 1 0\n");
    fprintf(file, "0 1 0 1\n");
    fprintf(file, "1 0 1 0\n");
    fprintf(file, "0 1 0 1\n");
    rewind(file);

    read_adjacency_list(adjacency_list, n, file);
    fclose(file);

    int expected_values[4][4] = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(adjacency_list[i][j] == expected_values[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        free(adjacency_list[i]);
    }
    free(adjacency_list);
}

void test_read_adjacency_matrix_no2(void)
{
    const int n = 4;
    int **adjacency_matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adjacency_matrix[i] = malloc(n * sizeof(int));
    }

    FILE *file = tmpfile();
    if (!file) {
        perror("tmpfile");
        abort();
    }

    fprintf(file, "0 1 0 1\n");
    fprintf(file, "1 0 1 0\n");
    fprintf(file, "0 1 0 1\n");
    fprintf(file, "1 0 1 0\n");
    rewind(file);

    read_adjacency_matrix(adjacency_matrix, n, file);
    fclose(file);

    int expected_values[4][4] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(adjacency_matrix[i][j] == expected_values[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
}

void test_list_to_matrix_no3(void)
{
    const int n = 4;
    int **list = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        list[i] = malloc(n * sizeof(int));
    }

    int **matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(n * sizeof(int));
    }

    int input_values[4][4] = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    create_test_matrix(list, n, input_values);

    list_to_matrix(list, matrix, n);

    int expected_values[4][4] = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(matrix[i][j] == expected_values[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        free(list[i]);
        free(matrix[i]);
    }
    free(list);
    free(matrix);
}

void test_empty_adjacency_matrix_no4(void)
{
    const int n = 0;
    int **adjacency_matrix = NULL;

    FILE *file = tmpfile();
    if (!file) {
        perror("tmpfile");
        abort();
    }

    read_adjacency_matrix(adjacency_matrix, n, file);
    fclose(file);

    assert(adjacency_matrix == NULL);
}

void test_empty_list_to_matrix_no5(void)
{
    const int n = 0;
    int **list = NULL;
    int **matrix = NULL;

    list_to_matrix(list, matrix, n);

    assert(matrix == NULL);
}

void test_incorrect_number_of_rows_in_adjacency_list_no6(void)
{
    const int n = 4;
    int **adjacency_list = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adjacency_list[i] = malloc(n * sizeof(int));
    }

    FILE *file = tmpfile();
    if (!file) {
        perror("tmpfile");
        abort();
    }

    fprintf(file, "1 0 1 0\n");
    fprintf(file, "0 1 0 1\n");
    rewind(file);

    read_adjacency_list(adjacency_list, n, file);
    fclose(file);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < 2 && j < 4) {
                assert(adjacency_list[i][j] == (i + j) % 2);
            } else {
                assert(adjacency_list[i][j] == 0);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        free(adjacency_list[i]);
    }
    free(adjacency_list);
}

void test_invalid_values_in_adjacency_matrix_no7(void)
{
    const int n = 4;
    int **adjacency_matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adjacency_matrix[i] = malloc(n * sizeof(int));
    }

    FILE *file = tmpfile();
    if (!file) {
        perror("tmpfile");
        abort();
    }

    fprintf(file, "0 x 0 1\n");
    fprintf(file, "1 0 1 0\n");
    fprintf(file, "0 1 0 1\n");
    fprintf(file, "1 0 1 0\n");
    rewind(file);

    read_adjacency_matrix(adjacency_matrix, n, file);
    fclose(file);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 1) {
                assert(adjacency_matrix[i][j] == 0);
            } else {
                int expected_value = (i + j) % 2;
                assert(adjacency_matrix[i][j] == expected_value);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
}

void test_asymmetric_list_to_matrix_no8(void)
{
    const int n = 4;
    int **list = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        list[i] = malloc(n * sizeof(int));
    }

    int **matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(n * sizeof(int));
    }

    int input_values[4][4] = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    create_test_matrix(list, n, input_values);

    list_to_matrix(list, matrix, n);

    int expected_values[4][4] = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(matrix[i][j] == expected_values[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        free(list[i]);
        free(matrix[i]);
    }
    free(list);
    free(matrix);
}

void test_compare_matrices_no9(void)
{
    const int n = 4;
    int **matrix1 = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix1[i] = malloc(n * sizeof(int));
    }

    int **matrix2 = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix2[i] = malloc(n * sizeof(int));
    }

    int values1[4][4] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    create_test_matrix(matrix1, n, values1);

    int values2[4][4] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    create_test_matrix(matrix2, n, values2);

    assert(compare_matrices(matrix1, matrix2, n) == 1);

    matrix2[0][0] = 1;

    assert(compare_matrices(matrix1, matrix2, n) == 0);

    for (int i = 0; i < n; ++i) {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
}

void test_comparing_different_size_matrices_10(void)
{
    const int n1 = 4;
    const int n2 = 3;
    int **matrix1 = malloc(n1 * sizeof(int*));
    for (int i = 0; i < n1; ++i) {
        matrix1[i] = malloc(n1 * sizeof(int));
    }

    int **matrix2 = malloc(n2 * sizeof(int*));
    for (int i = 0; i < n2; ++i) {
        matrix2[i] = malloc(n2 * sizeof(int));
    }
    int values1[4][4] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    create_test_matrix(matrix1, n1, values1);

    int values2[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    create_test_matrix(matrix2, n2, values2);
    assert(compare_matrices(matrix1, matrix2, n1) == 0);

    for (int i = 0; i < n1; ++i) {
        free(matrix1[i]);
    }
    free(matrix1);

    for (int i = 0; i < n2; ++i) {
        free(matrix2[i]);
    }
    free(matrix2);
}

