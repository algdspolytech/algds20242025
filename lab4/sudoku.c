#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"

// ������ ������� ������ �� �����
void readInput(const char* filename, int grid[GRID_SIZE][GRID_SIZE]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    int n;
    fscanf(file, "%d", &n); // ��������� ������ N (������ ���� ����� 3)

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            fscanf(file, "%d", &grid[i][j]);
        }
    }

    fclose(file);
}

// ������ ���������� � ����
void writeOutput(const char* filename, int grid[GRID_SIZE][GRID_SIZE], bool solved) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    if (!solved) {
        fprintf(file, "0\n");
    }
    else {
        fprintf(file, "3\n");
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                fprintf(file, "%d ", grid[i][j]);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

// ��������� ������ � ��������������� ������� ��� ��������� ������
#define MAX_NODES 10000

ColumnNode columnNodes[GRID_SIZE * GRID_SIZE * 4];
Node nodes[MAX_NODES];
int nodeCount;

void initDancingLinks() {
    // ������������� ���� ��������
    memset(columnNodes, 0, sizeof(columnNodes));
    memset(nodes, 0, sizeof(nodes));
    nodeCount = 0;
}

// �������� ����
Node* createNode(ColumnNode* column) {
    Node* node = &nodes[nodeCount++];
    node->column = column;
    node->left = node->right = node->up = node->down = node;
    return node;
}

// ���������� ��������� ������ (�������� DLX)
bool solveSudokuWithDancingLinks(int grid[GRID_SIZE][GRID_SIZE]) {
    // TODO: ���������� ���������� ������� �������� ��� ������
    // � ������������� ��������� DLX ��� ������ �������.
    //
    // �������� DLX:
    // 1. ��������� ������� �������� �� ������ ������ ������.
    // 2. ����������� ��������� ������ ��� ������ � ��������.
    // 3. ��������� ����� � ��������� ��� ������ ����������� �������.

    // ��������: ���� ��� ���������� false
    return false;
}