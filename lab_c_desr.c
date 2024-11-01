#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "lib.h"

//������� ���������� ������ � �����
char* ReadStringFromFile(FILE* file) {
    char* buffer = malloc(sizeof(char));
    if (buffer == NULL) {
        printf("������ ��������� ������");
        return NULL;
    }

    char character;
    int index = 1;
    while (fscanf(file, "%c", &character) != EOF) {
        if (character == '\n' || character == '\0') {
            break;
        }
        buffer[index - 1] = character;
        index++;
        buffer = realloc(buffer, index * sizeof(char));
        if (buffer == NULL) {
            printf("������ ��������� ������");
            return NULL;
        }
    }
    buffer[index - 1] = '\0';  // ��������� ������ ������� ��������
    return buffer;
}

// ������� ��� ����������� ���������� ������
int Colichestvo(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������ �������� �����\n");
        return -1;
    }

    int kol = 0;
    while (1) {
        char* line = ReadStringFromFile(file);
        if (line[0] == '\0') {
            free(line);
            break;
        }
        kol++;
        free(line);
    }

    fclose(file);
    return kol;
}

// ������� ��� �������� ������� ��������� � ������������� � ������
int** Create_Matrixx(int kol) {
    
    int** Matrix = (int**)malloc(kol * sizeof(int*));
    if (kol == 0) {
        return NULL;
    }
    if (Matrix == NULL) {
        free(Matrix);
        return NULL;
    }
    int flag = 0;
    for (int i = 0; i < kol; i++) {
        Matrix[i] = (int*)malloc(kol * sizeof(int));
        if (Matrix[i] == NULL) {
            flag = 1;
        }
        if (flag == 0) {
            for (int j = 0; j < kol; j++) {
                Matrix[i][j] = 0; // �������������� ������
            }
        }
    }
    if (flag == 1) {
        Free_matr(Matrix, kol);
        return NULL;
    }
    return Matrix;
}
void FillMatrix(const char* filename, int** adjacencyMatrix, int vertexCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������ �������� �����\n");
        return;
    }

    int vertex, neighbor;

    while (1) {
        char* line = ReadStringFromFile(file);
        if (line == NULL || line[0] == '\0') {
            free(line);
            break;
        }
        char* lineCopy = line;
        char* token;

        // ��������� ����� ������� ����� ����������
        token = strtok(line, ": ");
        if (token == NULL) {
            free(lineCopy);
            continue;
        }
        neighbor = atoi(token);

        // �������� ������ ������� ������
        token = strtok(NULL, " ");
        while (token != NULL) {
            vertex = atoi(token);
            if (neighbor >= 0 && neighbor < vertexCount && vertex >= 0 && vertex < vertexCount) {
                adjacencyMatrix[neighbor][vertex] = 1;
                adjacencyMatrix[vertex][neighbor] = 1;
            }
            else {
                printf("�������� ������: neighbor=%d, vertex=%d\n", neighbor, vertex);
            }
            token = strtok(NULL, " ");
        }
        free(lineCopy);
    }

    fclose(file);
}


// ������� ��� ������������ ������, ���������� ��� �������
void Free_matr(int** Matrix, int kol) {
    for (int i = 0; i < kol; i++) {
        free(Matrix[i]);
        Matrix[i] = NULL;
    }
    free(Matrix);
    Matrix = NULL;
}

// ������� ��� ������ ���������� ������� 
void Print_Matrix(int** Matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}