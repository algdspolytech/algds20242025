#include "LabC_lib.h"

#include <gtest/gtest.h>

TEST(CreateNode_ValidInput_NodeCreated_0) {
    Node* node = create_node(5);
    ASSERT_NE(node, nullptr); 
    EXPECT_EQ(node->vertex, 5); 
    EXPECT_EQ(node->next, nullptr);
    free(node);
}

TEST(CreateNode_InvalidInput_NodeNotNull_1) {
    Node* node = create_node(-1); 
    ASSERT_NE(node, nullptr); 
    EXPECT_EQ(node->vertex, -1);
    free(node);
}

TEST(CreateGraph_ValidVertices_GraphCreated_2) {
    Graph* graph = create_graph(4);
    ASSERT_NE(graph, nullptr); 
    EXPECT_EQ(graph->numVertices, 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(graph->list[i].head, nullptr);
    }
}

TEST(CreateGraph_ZeroVertices_EmptyGraphCreated_3) {
    Graph* graph = create_graph(0);
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->numVertices, 0);
}

TEST(CreateGraph_NegativeVertices_GraphNotCreated_4) {
    Graph* graph = create_graph(-5);
    EXPECT_EQ(graph, nullptr);
}

TEST(AddEdge_AddSingleEdge_EdgeAddedCorrectly_5) {
    Graph* graph = create_graph(2);
    add_edge(graph, 0, 1);
    ASSERT_NE(graph->list[0].head, nullptr); 
    EXPECT_EQ(graph->list[0].head->vertex, 1);
    EXPECT_EQ(graph->list[0].head->next, nullptr);
}

TEST(AddEdge_AddMultipleEdges_EdgesAddedInOrder_6) {
    Graph* graph = create_graph(3);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    ASSERT_NE(graph->list[0].head, nullptr);
    EXPECT_EQ(graph->list[0].head->vertex, 2); 
    EXPECT_EQ(graph->list[0].head->next->vertex, 1);
}

TEST(AddEdge_InvalidSourceVertex_NoEdgeAdded_7) {
    Graph* graph = create_graph(3);
    add_edge(graph, 3, 1); 
    EXPECT_EQ(graph->list[0].head, nullptr);
    EXPECT_EQ(graph->list[1].head, nullptr);
    EXPECT_EQ(graph->list[2].head, nullptr);
}

TEST(BuildAdjacencyList_ValidMatrix_GraphCreatedCorrectly_8) {
    int size = 3;
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
    }

    matrix[0][1] = 1;
    matrix[1][2] = 1;

    Graph* graph = build_adjacency_list(matrix, size);
    ASSERT_NE(graph, nullptr);

    EXPECT_EQ(graph->numVertices, 3);
    ASSERT_NE(graph->list[0].head, nullptr);
    EXPECT_EQ(graph->list[0].head->vertex, 1);
    ASSERT_NE(graph->list[1].head, nullptr);
    EXPECT_EQ(graph->list[1].head->vertex, 2);
    EXPECT_EQ(graph->list[2].head, nullptr);
}

TEST(BuildAdjacencyList_EmptyMatrix_GraphEmpty_9) {
    int size = 2;
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
    }

    Graph* graph = build_adjacency_list(matrix, size);
    ASSERT_NE(graph, nullptr);

    EXPECT_EQ(graph->numVertices, 2);
    EXPECT_EQ(graph->list[0].head, nullptr);
    EXPECT_EQ(graph->list[1].head, nullptr);
}

TEST(FreeGraph_ValidGraph_NoMemoryLeaks_10) {
    Graph* graph = create_graph(3);
    add_edge(graph, 0, 1);
    add_edge(graph, 1, 2);

    free_graph(graph);
    SUCCEED();
}

TEST(FreeGraph_EmptyGraph_NoMemoryLeaks_11) {
    Graph* graph = create_graph(0);

    free_graph(graph);
    SUCCEED();
}

TEST(FreeAdjacencyMatrix_ValidMatrix_NoMemoryLeaks_12) {
    int size = 3;
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
    }

    free_adjacency_matrix(matrix, size);
    SUCCEED();
}

TEST(FreeAdjacencyMatrix_EmptyMatrix_NoMemoryLeaks_13) {
    int size = 0;
    int** matrix = nullptr;

    free_adjacency_matrix(matrix, size);
    SUCCEED();
}