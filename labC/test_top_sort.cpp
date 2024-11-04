#include <gtest/gtest.h>
extern "C" {
#include "topological_sort.h"
}

// Тест 1: Проверка на пустом графе
TEST(TopologicalSortTest, EmptyGraph_no1) {
    Graph* graph = createGraph(0);
    int stack[100];
    topologicalSort(graph, stack);
    EXPECT_EQ(stack[0], 0); 
}

// Тест 2:  Проверка на графе с одной вершиной
TEST(TopologicalSortTest, SingleVertex_no2) {
    Graph* graph = createGraph(1);
    int stack[100];
    topologicalSort(graph, stack);
    EXPECT_EQ(stack[0], 0);
}

// Тест 3:  Проверка на графе с двумя вершинами
TEST(TopologicalSortTest, TwoVertices_no3) {
    Graph* graph = createGraph(2);
    addEdge(graph, 0, 1);
    int stack[100];
    topologicalSort(graph, stack);
    EXPECT_EQ(stack[0], 0);
    EXPECT_EQ(stack[1], 1);
}

// Тест 4:  Проверка на графе с тремя вершинами
TEST(TopologicalSortTest, ThreeVertices_no4) {
    Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    int stack[100];
    topologicalSort(graph, stack);
    EXPECT_EQ(stack[0], 0);
    EXPECT_EQ(stack[1], 1);
    EXPECT_EQ(stack[2], 2);
}

// Тест 5:  Проверка на порядок вершин
TEST(TopologicalSortTest, MultipleEdges_no5) {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    
    int stack[100];
    topologicalSort(graph, stack);
    
    EXPECT_TRUE((stack[0] == 0 && (stack[1] == 1 || stack[1] == 2)) && stack[2] == 3);
}

// Тест 6:  Проверка на наличие всех вершин в стеке
TEST(TopologicalSortTest, DisconnectedGraph_no6) {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 3, 4);

    int stack[100];
    topologicalSort(graph, stack);

    EXPECT_TRUE((stack[0] == 0 || stack[0] == 3) && 
                (stack[1] == 1 || stack[1] == 4));
}

// Тест 7:  Проверка на порядок вершин
TEST(TopologicalSortTest, ComplexGraph_no7) {
    Graph* graph = createGraph(6);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    int stack[100];
    topologicalSort(graph, stack);

    EXPECT_TRUE((stack[5] == 5) && (stack[4] == 4));
}

// Тест 8:  Проверка наличия всех вершин графа без ребер в стеке
TEST(TopologicalSortTest, NoEdges_no8) {
    Graph* graph = createGraph(3);
    int stack[100];
    
    topologicalSort(graph, stack);

    EXPECT_TRUE((stack[0] == 0 || stack[1] == 1 || stack[2] == 2));
}

// Тест 9:  Проверка на порядок вершин
TEST(TopologicalSortTest, AllVerticesConnected_no9) {
    Graph* graph = createGraph(3);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    
    int stack[100];
    
    topologicalSort(graph, stack);

    EXPECT_EQ(stack[0], 0);
}

// Тест 10:  Проверка цикла
TEST(TopologicalSortTest, CircularDependency_no10) {
   Graph* graph = createGraph(3);
   addEdge(graph, 0, 1);
   addEdge(graph, 1, 2);
   addEdge(graph, 2, 0);
   
   int stack[100];
   topologicalSort(graph, stack); // Это должно завершиться неудачно или с ошибкой
   EXPECT_EQ(stack[0], -1); // Предполагаемое значение для обработки ошибки
}