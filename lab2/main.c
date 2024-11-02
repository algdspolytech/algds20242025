#include <stdio.h>
#include <stdlib.h>
#include "tests.c"

void read_adjacency_list(int **adjacency_matrix, int n, FILE *file) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(file, "%d", &adjacency_matrix[i][j]);
        }
    }
}

void read_adjacency_matrix(int **adjacency_matrix, int n, FILE *file) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(file, "%d", &adjacency_matrix[i][j]);
        }
    }
}

void list_to_matrix(int **list, int **matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = 0;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (list[i][j]) {
                matrix[i][j] = 1;
            }
        }
    }
}

int compare_matrices(int **matrix1, int **matrix2, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    int n;

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    int **adjacency_list = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adjacency_list[i] = malloc(n * sizeof(int));
    }

    int **adjacency_matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adjacency_matrix[i] = malloc(n * sizeof(int));
    }

    int **converted_matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        converted_matrix[i] = malloc(n * sizeof(int));
    }

    FILE *list_file = fopen("adj_list.txt", "r");
    FILE *matrix_file = fopen("adj_matrix.txt", "r");

    if (!list_file || !matrix_file) {
        fprintf(stderr, "Ошибка открытия файлов.\n");
        exit(EXIT_FAILURE);
    }

    read_adjacency_list(adjacency_list, n, list_file);
    read_adjacency_matrix(adjacency_matrix, n, matrix_file);

    fclose(list_file);
    fclose(matrix_file);

    list_to_matrix(adjacency_list, converted_matrix, n);

    int result = compare_matrices(converted_matrix, adjacency_matrix, n);

    if (result) {
        printf("Графы совпадают.\n");
    } else {
        printf("Графы не совпадают.\n");
    }

    for (int i = 0; i < n; ++i) {
        free(adjacency_list[i]);
        free(adjacency_matrix[i]);
        free(converted_matrix[i]);
    }
    free(adjacency_list);
    free(adjacency_matrix);
    free(converted_matrix);
    
    test_read_adjacency_list_no1();
    test_read_adjacency_matrix_no2();
    test_list_to_matrix_no3();
    test_empty_adjacency_matrix_no4();
    test_empty_list_to_matrix_no5();
    test_incorrect_number_of_rows_in_adjacency_list_no6();
    test_invalid_values_in_adjacency_matrix_no7();
    test_asymmetric_list_to_matrix_no8();
    test_compare_matrices_no9();
    test_comparing_different_size_matrices_10();

    printf("Все тесты прошли успешно!\n");

    return 0;
}
