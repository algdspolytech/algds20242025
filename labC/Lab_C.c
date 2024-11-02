#include <stdio.h>
#include <stdlib.h>

#include "Lab_C.h"

// ������� ��� ���������� ������� ��������� �� �����
int** readMatrix(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // ���������� ������ �������
    *rows = 0;
    *cols = 0;
    int ch;
    int currentCols = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            currentCols++;
        }
        else if (ch == '\n') {
            (*rows)++;
            if (*cols == 0) {
                *cols = currentCols + 1; // ���������� �������� � ������ ������
            }
            currentCols = 0;
        }
    }
    fseek(file, 0, SEEK_SET); // ������������ � ������ �����

    // �������� ������ ��� �������
    int** matrix = (int**)malloc(*rows * sizeof(int*));
    for (int i = 0; i < *rows; i++) {
        matrix[i] = (int*)malloc(*cols * sizeof(int));
    }

    // ������ ������ �� ����� � �������
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

// ������� ��� �������� ������ ���������
int** createAdjacencyList(int** matrix, int rows, int cols, int** adjacencySizes) {
    int** adjacencyList = (int**)malloc(rows * sizeof(int*));
    *adjacencySizes = (int*)malloc(rows * sizeof(int)); // ������ ��� �������� ���������� ������� ������

    for (int i = 0; i < rows; i++) {
        (*adjacencySizes)[i] = 0;
        // ������� ���������� ������� ������ ��� ������� �������
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                (*adjacencySizes)[i]++;
            }
        }
        // �������� ������ ��� ������ ������� ������ ������� �������
        adjacencyList[i] = (int*)malloc((*adjacencySizes)[i] * sizeof(int));
        int index = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                adjacencyList[i][index++] = j + 1; // ��������� ������ � 1
            }
        }
    }
    return adjacencyList;
}

// ������� ��� ������ ������ ��������� � ����
void writeAdjacencyListToFile(const char* filename, int** adjacencyList, int* adjacencySizes, int rows) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < rows; i++) {
        fprintf(file, "%d:", i + 1); // ��������� ������ � 1
        for (int j = 0; j < adjacencySizes[i]; j++) {
            fprintf(file, " %d", adjacencyList[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}