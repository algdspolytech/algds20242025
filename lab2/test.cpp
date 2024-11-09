#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../algosi2/head.h"
}

TEST(CreateNodeTest, Create_no1) {
    Node* node = createNode(1);
    ASSERT_NE(nullptr, node);
    ASSERT_EQ(1, node->vertex);
    ASSERT_EQ(nullptr, node->next);
}

TEST(CreateGraphTest, CreateEmptyGraph_no2) {
    int matrix[MAX_VERTICES][MAX_VERTICES] = { 0 };
    Graph* graph = createGraph(matrix, 3);
    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(3, graph->numVertices);
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(nullptr, graph->adjacencyList[i]);
    }
}

TEST(CreateGraphTest, CreateGraphSucces_no3) {
    int matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0},
    };
    Graph* graph = createGraph(matrix, 3);
    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(3, graph->numVertices);

    ASSERT_NE(nullptr, graph->adjacencyList[0]);
    ASSERT_EQ(1, graph->adjacencyList[0]->vertex);
    ASSERT_EQ(nullptr, graph->adjacencyList[0]->next);

    ASSERT_NE(nullptr, graph->adjacencyList[1]);
    ASSERT_EQ(2, graph->adjacencyList[1]->vertex);
    ASSERT_NE(nullptr, graph->adjacencyList[1]->next);
    ASSERT_EQ(0, graph->adjacencyList[1]->next->vertex);
    ASSERT_EQ(nullptr, graph->adjacencyList[1]->next->next);

    ASSERT_NE(nullptr, graph->adjacencyList[2]);
    ASSERT_EQ(1, graph->adjacencyList[2]->vertex);
    ASSERT_EQ(nullptr, graph->adjacencyList[2]->next);

    free(graph);
}
TEST(ReadMatrixFromFileTest, ValidFile_no4) {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

    FILE* tempFile = fopen("test_matrix.txt", "w");
    fprintf(tempFile, "3\n0 1 0\n1 0 1\n0 1 0\n");
    fclose(tempFile);

    ASSERT_EQ(readMatrixFromFile("test_matrix.txt", matrix, &numVertices), 0);
    ASSERT_EQ(numVertices, 3);

    ASSERT_EQ(matrix[0][0], 0);
    ASSERT_EQ(matrix[0][1], 1);
    ASSERT_EQ(matrix[0][2], 0);
    ASSERT_EQ(matrix[1][0], 1);
    ASSERT_EQ(matrix[1][1], 0);
    ASSERT_EQ(matrix[1][2], 1);
    ASSERT_EQ(matrix[2][0], 0);
    ASSERT_EQ(matrix[2][1], 1);
    ASSERT_EQ(matrix[2][2], 0);

    remove("test_matrix.txt");
}

TEST(ReadMatrixFromFileTest, InvalidFile_no5) {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

    ASSERT_EQ(readMatrixFromFile("nonexistent_file.txt", matrix, &numVertices),
        1);
}

TEST(ReadMatrixFromFileTest, IncorrectSize_no6) {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

    FILE* tempFile = fopen("test_matrix.txt", "w");
    fprintf(tempFile, "101\n");
    fclose(tempFile);

    ASSERT_EQ(readMatrixFromFile("test_matrix.txt", matrix, &numVertices), 2);

    remove("test_matrix.txt");
}

TEST(ReadMatrixFromFileTest, InvalidData_no7) {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

    FILE* tempFile = fopen("test_matrix.txt", "w");
    fprintf(tempFile, "3\n0 1 2\n1 0 1\n0 1 0\n");
    fclose(tempFile);

    ASSERT_EQ(readMatrixFromFile("test_matrix.txt", matrix, &numVertices), 3);

    remove("test_matrix.txt");
}

TEST(ReadMatrixFromFileTest, InvalidMatrix_no8) {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

    FILE* tempFile = fopen("test_matrix.txt", "w");
    fprintf(tempFile, "3\n0 1 0\n1 0 1\n");
    fclose(tempFile);

    ASSERT_EQ(readMatrixFromFile("test_matrix.txt", matrix, &numVertices), 4);

    remove("test_matrix.txt");
}

TEST(IsAdjacencyTest, AdjacencyExists_no9) {
    int matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0},
    };
    Graph* graph = createGraph(matrix, 3);
    ASSERT_EQ(IsAdjacency(matrix, graph, 0, 1), 1);
    ASSERT_NE(graph->adjacencyList[0], nullptr);
    ASSERT_EQ(graph->adjacencyList[0]->vertex, 1);
}

TEST(IsAdjacencyTest, AdjacencyDoesNotExists_no10) {
    int matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0},
    };
    Graph* graph = createGraph(matrix, 3);
    ASSERT_EQ(IsAdjacency(matrix, graph, 0, 2), 0);
    ASSERT_EQ(graph->adjacencyList[0]->vertex, 1);
}