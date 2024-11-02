#include <gtest/gtest.h>
#include "Lab_C.h"

void freeAdjacencyList(int** adjacencyList, int* adjacencySizes, int rows) {
    for (int i = 0; i < rows; i++) {
        free(adjacencyList[i]);
    }
    free(adjacencyList);
    free(adjacencySizes);
}
// Òåñò: Ïðîâåðêà, ÷òî ôóíêöèÿ âîçâðàùàåò êîððåêòíûé ñïèñîê ñìåæíîñòè äëÿ ïóñòîé ìàòðèöû
TEST(CreateAdjacencyList_EmptyMatrix_ReturnValidVal_no1) {
    int rows = 0, cols = 0;
    int* adjacencySizes = nullptr;
    int** matrix = nullptr;

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencyList, nullptr);
    ASSERT_EQ(adjacencySizes, nullptr);
}

// Òåñò: Ïðîâåðêà, ÷òî ôóíêöèÿ âîçâðàùàåò êîððåêòíûé ñïèñîê ñìåæíîñòè äëÿ îäèíî÷íîé âåðøèíû áåç ðåáåð
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

// Òåñò: Ïðîâåðêà ñïèñêà ñìåæíîñòè äëÿ îäèíî÷íîé âåðøèíû ñ ïåòëåé
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

// Òåñò: Ïðîâåðêà ñïèñêà ñìåæíîñòè äëÿ äâóõ âåðøèí áåç ðåáåð
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

// Òåñò: Ïðîâåðêà ñïèñêà ñìåæíîñòè äëÿ äâóõ âåðøèí ñ îäíèì ðåáðîì
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

// Òåñò: Ïðîâåðêà ñïèñêà ñìåæíîñòè äëÿ òð¸õ âåðøèí áåç ð¸áåð
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

// Òåñò: Ïðîâåðêà ñïèñêà ñìåæíîñòè äëÿ òð¸õ âåðøèí ñ îäíèì ðåáðîì
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

// Òåñò: Ïðîâåðêà ñïèñêà ñìåæíîñòè äëÿ ïîëíîé ìàòðèöû (òðè âåðøèíû, âñå ñîåäèíåíû)
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
    // Îïðåäåëåíèå ð¸áåð:
    // Âåðøèíà 1 (0) ñîåäèíåíà ñ 2 (1)
    // Âåðøèíà 2 (1) ñîåäèíåíà ñ 3 (2)
    // Âåðøèíà 3 (2) ñîåäèíåíà ñ 1 (0)
    matrix[0][0] = 0; matrix[0][1] = 1; matrix[0][2] = 0; // Âåðøèíà 1
    matrix[1][0] = 0; matrix[1][1] = 0; matrix[1][2] = 1; // Âåðøèíà 2
    matrix[2][0] = 1; matrix[2][1] = 0; matrix[2][2] = 0; // Âåðøèíà 3

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
    // Îïðåäåëåíèå ð¸áåð:
    // Âåðøèíà 1 (0) ñîåäèíåíà ñ 2 (1) è 3 (2)
    // Âåðøèíà 2 (1) ñîåäèíåíà ñ 1 (0)
    // Âåðøèíà 3 (2) íå ñîåäèíåíà íè ñ îäíîé (èçîëèðîâàííàÿ)
    // Âåðøèíà 4 (3) ñîåäèíåíà ñ 1 (0) è 2 (1)
    matrix[0][0] = 0; matrix[0][1] = 1; matrix[0][2] = 1; matrix[0][3] = 0; // Âåðøèíà 1
    matrix[1][0] = 1; matrix[1][1] = 0; matrix[1][2] = 0; matrix[1][3] = 0; // Âåðøèíà 2
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 0; matrix[2][3] = 0; // Âåðøèíà 3 (èçîëèðîâàííàÿ)
    matrix[3][0] = 1; matrix[3][1] = 1; matrix[3][2] = 0; matrix[3][3] = 0; // Âåðøèíà 4

    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    ASSERT_EQ(adjacencySizes[0], 2);
    ASSERT_EQ(adjacencyList[0][0], 2);
    ASSERT_EQ(adjacencySizes[1], 1);
    ASSERT_EQ(adjacencyList[1][0], 1);
    ASSERT_EQ(adjacencySizes[2], 0); // Èçîëèðîâàííàÿ âåðøèíà
    ASSERT_EQ(adjacencySizes[3], 2);
    ASSERT_EQ(adjacencyList[3][0], 1);
    ASSERT_EQ(adjacencyList[3][1], 2);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    freeAdjacencyList(adjacencyList, adjacencySizes, rows);
}