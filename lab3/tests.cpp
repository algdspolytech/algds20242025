#include <gtest/gtest.h>
#include "Lab_C.h"

void freeAdjacencyList(int** adjacencyList, int* adjacencySizes, int rows) {
    for (int i = 0; i < rows; i++) {
        free(adjacencyList[i]);
    }
    free(adjacencyList);
    free(adjacencySizes);
}
// ����: ��������, ��� ������� ���������� ���������� ������ ��������� ��� ������ �������
TEST(CreateAdjacencyList_EmptyMatrix_ReturnValidVal_no1) {
    int rows = 0, cols = 0;
    int* adjacencySizes = nullptr;
    int** matrix = nullptr;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencyList, nullptr);
    ASSERT_EQ(adjacencySizes, nullptr);
}

// ����: ��������, ��� ������� ���������� ���������� ������ ��������� ��� ��������� ������� ��� �����
TEST(CreateAdjacencyList_SingleVertexNoEdges_ReturnValidVal_no2) {
    int rows = 1, cols = 1;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    matrix[0] = (int*)malloc(cols * sizeof(int));
    matrix[0][0] = 0;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 0);

    free(matrix[0]);
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

// ����: �������� ������ ��������� ��� ��������� ������� � ������
TEST(CreateAdjacencyList_SingleVertexSelfLoop_ReturnValidVal_no3) {
    int rows = 1, cols = 1;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    matrix[0] = (int*)malloc(cols * sizeof(int));
    matrix[0][0] = 1;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 1);
    ASSERT_EQ(adjacencyList[0][0], 1);

    free(matrix[0]);
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

// ����: �������� ������ ��������� ��� ���� ������ ��� �����
TEST(CreateAdjacencyList_TwoVerticesNoEdges_ReturnValidVal_no4) {
    int rows = 2, cols = 2;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 0);
    ASSERT_EQ(adjacencySizes[1], 0);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

// ����: �������� ������ ��������� ��� ���� ������ � ����� ������
TEST(CreateAdjacencyList_TwoVerticesOneEdge_ReturnValidVal_no5) {
    int rows = 2, cols = 2;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 0;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 1);
    ASSERT_EQ(adjacencySizes[1], 1);
    ASSERT_EQ(adjacencyList[0][0], 2);
    ASSERT_EQ(adjacencyList[1][0], 1);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

// ����: �������� ������ ��������� ��� ��� ������ ��� ����
TEST(CreateAdjacencyList_ThreeVerticesNoEdges_ReturnValidVal_no6) {
    int rows = 3, cols = 3;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 0);
    ASSERT_EQ(adjacencySizes[1], 0);
    ASSERT_EQ(adjacencySizes[2], 0);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

// ����: �������� ������ ��������� ��� ��� ������ � ����� ������
TEST(CreateAdjacencyList_ThreeVerticesOneEdge_ReturnValidVal_no7) {
    int rows = 3, cols = 3;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[0][2] = 0;
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 0;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 1);
    ASSERT_EQ(adjacencyList[0][0], 2);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

// ����: �������� ������ ��������� ��� ������ ������� (��� �������, ��� ���������)
TEST(CreateAdjacencyList_ThreeVerticesFullConnection_ReturnValidVal_no8) {
    int rows = 3, cols = 3;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[2][0] = 1;
    matrix[2][1] = 1;
    matrix[2][2] = 0;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 2);
    ASSERT_EQ(adjacencySizes[1], 2);
    ASSERT_EQ(adjacencySizes[2], 2);
    ASSERT_EQ(adjacencyList[0][0], 2);
    ASSERT_EQ(adjacencyList[0][1], 3);
    ASSERT_EQ(adjacencyList[1][0], 1);
    ASSERT_EQ(adjacencyList[1][1], 3);
    ASSERT_EQ(adjacencyList[2][0], 1);
    ASSERT_EQ(adjacencyList[2][1], 2);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

TEST(CreateAdjacencyList_ThreeVerticesDifferentEdges_ReturnValidVal_no9) {
    int rows = 3, cols = 3;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    // ����������� ����:
    // ������� 1 (0) ��������� � 2 (1)
    // ������� 2 (1) ��������� � 3 (2)
    // ������� 3 (2) ��������� � 1 (0)
    matrix[0][0] = 0; matrix[0][1] = 1; matrix[0][2] = 0; // ������� 1
    matrix[1][0] = 0; matrix[1][1] = 0; matrix[1][2] = 1; // ������� 2
    matrix[2][0] = 1; matrix[2][1] = 0; matrix[2][2] = 0; // ������� 3

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 1);
    ASSERT_EQ(adjacencyList[0][0], 2);
    ASSERT_EQ(adjacencySizes[1], 1);
    ASSERT_EQ(adjacencyList[1][0], 3);
    ASSERT_EQ(adjacencySizes[2], 1);
    ASSERT_EQ(adjacencyList[2][0], 1);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

TEST(CreateAdjacencyList_FourVerticesWithIsolatedVertex_ReturnValidVal_no10) {
    int rows = 4, cols = 4;
    int* adjacencySizes = nullptr;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    // ����������� ����:
    // ������� 1 (0) ��������� � 2 (1) � 3 (2)
    // ������� 2 (1) ��������� � 1 (0)
    // ������� 3 (2) �� ��������� �� � ����� (�������������)
    // ������� 4 (3) ��������� � 1 (0) � 2 (1)
    matrix[0][0] = 0; matrix[0][1] = 1; matrix[0][2] = 1; matrix[0][3] = 0; // ������� 1
    matrix[1][0] = 1; matrix[1][1] = 0; matrix[1][2] = 0; matrix[1][3] = 0; // ������� 2
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 0; matrix[2][3] = 0; // ������� 3 (�������������)
    matrix[3][0] = 1; matrix[3][1] = 1; matrix[3][2] = 0; matrix[3][3] = 0; // ������� 4

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 2);
    ASSERT_EQ(adjacencyList[0][0], 2);
    ASSERT_EQ(adjacencySizes[1], 1);
    ASSERT_EQ(adjacencyList[1][0], 1);
    ASSERT_EQ(adjacencySizes[2], 0); // ������������� �������
    ASSERT_EQ(adjacencySizes[3], 2);
    ASSERT_EQ(adjacencyList[3][0], 1);
    ASSERT_EQ(adjacencyList[3][1], 2);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}

