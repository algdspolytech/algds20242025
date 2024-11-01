#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <assert.h>
#include "lib.h"


// ���� ��� ������� ReadStringFromFile
void test_ReadStringFromFile() {
    FILE* file = fopen("test_file_long.txt", "w");
    fprintf(file, "This is a long line with many characters\n");
    fclose(file);

    file = fopen("test_file_long.txt", "r");
    char* result = ReadStringFromFile(file);
    assert(result != NULL);
    assert(strcmp(result, "This is a long line with many characters") == 0);
    free(result);
    fclose(file);
    remove("test_file_long.txt");

    file = fopen("test_file_empty.txt", "w");
    fprintf(file, "\n");
    fclose(file);

    file = fopen("test_file_empty.txt", "r");
    result = ReadStringFromFile(file);
    assert(result != NULL);
    assert(strcmp(result, "") == 0);
    free(result);
    fclose(file);
    remove("test_file_empty.txt");
}

// ���� ��� ������� Colichestvo
void test_Colichestvo() {
    FILE* file = fopen("test_file_lines.txt", "w");
    fprintf(file, "1: 2 3\n2: 3\n3: 1\n4: 2\n");
    fclose(file);

    int result = Colichestvo("test_file_lines.txt");
    assert(result == 4);
    remove("test_file_lines.txt");

    file = fopen("test_file_empty.txt", "w");
    fclose(file);

    result = Colichestvo("test_file_empty.txt");
    assert(result == 0);
    remove("test_file_empty.txt");
}

// ���� ��� ������� Create_Matrixx
void test_Create_Matrixx() {
    int** matrix = Create_Matrixx(0);
    assert(matrix == NULL);

    matrix = Create_Matrixx(1000);
    assert(matrix != NULL);
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            assert(matrix[i][j] == 0);
        }
    }
    Free_matr(matrix, 1000);
}

// ���� ��� ������� FillMatrix
void test_FillMatrix() {
    // ���� ��� ���������� ������
    FILE* file = fopen("test_file_graph.txt", "w");
    fprintf(file, "0: 1 2\n1: 0 3\n2: 0\n3: 1\n");
    fclose(file);

    int vertexCount = 4;
    int** matrix = Create_Matrixx(vertexCount);
    FillMatrix("test_file_graph.txt", matrix, vertexCount);

    // �������� ���������� ��������
    assert(matrix[0][1] == 1);
    assert(matrix[0][2] == 1);
    assert(matrix[1][3] == 1);
    assert(matrix[2][0] == 1);
    assert(matrix[3][1] == 1);

    Free_matr(matrix, vertexCount);
    remove("test_file_graph.txt");

    // ���� ��� ������������ ������
    file = fopen("test_file_incorrect.txt", "w");
    fprintf(file, "0: 1\n1: 2\n3: 0 1 5\n");
    fclose(file);

    matrix = Create_Matrixx(4);
    FillMatrix("test_file_incorrect.txt", matrix, 4);

    // �������� ����������� ����������, �������� ��� ��������� ��������� �� ���������
    assert(matrix[0][1] == 1);
    assert(matrix[1][2] == 1);

    Free_matr(matrix, 4);
    remove("test_file_incorrect.txt");
}

// ���� ��� ������� Free_matr
void test_Free_matr() {
    int** matrix = NULL;
    Free_matr(matrix, 0); // �������� �� ���������� ����� ��� ������������ NULL-���������

    matrix = Create_Matrixx(3);
    for (int i = 0; i < 3; i++) {
        if (i == 1) { // ������������, ��� ������ ������ �� ��������
            free(matrix[i]);
            matrix[i] = NULL;
        }
    }
    Free_matr(matrix, 3); // �������� ������������ �������� ���������� ������
    printf("���� Free_matr �������.\n");

}

// ���� ��� ������� Print_Matrix
void test_Print_Matrix() {
    int** matrix = NULL;
    Print_Matrix(matrix, 0); // �������� �� ���������� ������ ��� NULL �������

    int n = 3;
    matrix = Create_Matrixx(n);
    matrix[0][1] = 1;
    matrix[1][2] = 1;
    matrix[1][0] = 1;
    matrix[2][1] = 1;
    printf("��������� �����:\n0 1 0\n1 0 1\n0 1 0\n����������� �����:\n");
    Print_Matrix(matrix, n);
    Free_matr(matrix, n);
}

int main() {
    setlocale(LC_ALL, "Rus");

    test_ReadStringFromFile();
    printf("���� ReadStringFromFile �������.\n");
    test_Colichestvo();
    printf("���� Colichestvo �������.\n");
    test_Create_Matrixx();
    printf("���� Create_Matrixx �������.\n");

    test_FillMatrix();
    printf("���� FillMatrix �������.\n");
    test_Free_matr();
    test_Print_Matrix();
    printf("���� Print_Matrix �������.\n");

    return 0;
}