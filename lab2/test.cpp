#include "pch.h"
#include "gtest/gtest.h"
#include "../Lab_C/main.h"

// Проверка функции readAdjacencyList для пустого графа
TEST(GraphTest, ReadAdjacencyList_EmptyGraph_no1) {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertex_count = 0;
    readAdjacencyList("empty_list.txt", graph, &vertex_count);
    ASSERT_EQ(vertex_count, 0);
}

// Проверка функции readAdjacencyList для графа с одной вершиной
TEST(GraphTest, ReadAdjacencyList_SingleVertex_no2) {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertex_count = 0;
    readAdjacencyList("single_vertex_list.txt", graph, &vertex_count);
    ASSERT_EQ(vertex_count, 1);
    ASSERT_EQ(graph[0][0], 0);
}

// Проверка функции readAdjacencyList для графа с несколькими вершинами, но без рёбер
TEST(GraphTest, ReadAdjacencyList_DisconnectedGraph_no3) {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertex_count = 0;
    readAdjacencyList("disconnected_list.txt", graph, &vertex_count);
    ASSERT_EQ(vertex_count, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ASSERT_EQ(graph[i][j], 0);
        }
    }
}

// Проверка функции readAdjacencyMatrix для пустого графа
TEST(GraphTest, ReadAdjacencyMatrix_EmptyGraph_no4) {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertex_count = 0;
    readAdjacencyMatrix("empty_matrix.txt", graph, &vertex_count);
    ASSERT_EQ(vertex_count, 0);
}

// Проверка функции readAdjacencyMatrix для графа с одной вершиной
TEST(GraphTest, ReadAdjacencyMatrix_SingleVertex_no5) {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertex_count = 0;
    readAdjacencyMatrix("single_vertex_matrix.txt", graph, &vertex_count);
    ASSERT_EQ(vertex_count, 1);
    ASSERT_EQ(graph[0][0], 0);
}

// Проверка функции compareGraphs для двух пустых графов
TEST(GraphTest, CompareGraphs_EmptyGraphs_no6) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };
    ASSERT_EQ(compareGraphs(graph1, graph2, 0), 1);
}

// Проверка функции compareGraphs для графов с одной вершиной без рёбер
TEST(GraphTest, CompareGraphs_SingleVertex_no7) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { {0} };
    ASSERT_EQ(compareGraphs(graph1, graph2, 1), 1);
}

// Проверка функции compareGraphs для двух несвязанных графов
TEST(GraphTest, CompareGraphs_DisconnectedGraphs_no8) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int vertex_count = 3;
    ASSERT_EQ(compareGraphs(graph1, graph2, vertex_count), 1);
}

// Проверка функции compareGraphs для графов, где один граф является подграфом другого
TEST(GraphTest, CompareGraphs_Subgraph_no9) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int vertex_count = 3;

    // graph1 имеет ребро 0->1
    graph1[0][1] = 1;

    // graph2 не имеет рёбер
    ASSERT_EQ(compareGraphs(graph1, graph2, vertex_count), 0);
}

// Проверка функции compareGraphs для одинаковых графов с рёбрами
TEST(GraphTest, CompareGraphs_SameGraph_no10) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int vertex_count = 3;

    // Оба графа имеют рёбра 0->1 и 1->2
    graph1[0][1] = 1;
    graph1[1][2] = 1;
    graph2[0][1] = 1;
    graph2[1][2] = 1;

    ASSERT_EQ(compareGraphs(graph1, graph2, vertex_count), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
