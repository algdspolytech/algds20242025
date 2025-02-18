#include "gtest/gtest.h"
#include "graph.h"  // Предполагается, что graph.h находится в той же директории

// Тест для функции создания графа списком смежности
TEST(GraphAdjListTest, CreateGraphAdjList) {
  GraphAdjList* graph = createGraphAdjList(5);
  ASSERT_NE(graph, nullptr);
  ASSERT_EQ(graph->V, 5);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(graph->array[i].head, nullptr);
  }
  freeGraphAdjList(graph);
}

// Тест для добавления ребра в граф списком смежности
TEST(GraphAdjListTest, AddEdgeAdjList) {
  GraphAdjList* graph = createGraphAdjList(4);
  addEdgeAdjList(graph, 0, 1);
  ASSERT_NE(graph->array[0].head, nullptr);
  ASSERT_EQ(graph->array[0].head->dest, 1);
  ASSERT_NE(graph->array[1].head, nullptr);
  ASSERT_EQ(graph->array[1].head->dest, 0);
  freeGraphAdjList(graph);
}

// Тест для функции создания графа матрицей смежности
TEST(GraphAdjMatrixTest, CreateGraphAdjMatrix) {
  GraphAdjMatrix* graph = createGraphAdjMatrix(3);
  ASSERT_NE(graph, nullptr);
  ASSERT_EQ(graph->V, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ASSERT_EQ(graph->adjMatrix[i][j], 0);
    }
  }
  freeGraphAdjMatrix(graph);
}

// Тест для добавления ребра в граф матрицей смежности
TEST(GraphAdjMatrixTest, AddEdgeAdjMatrix) {
  GraphAdjMatrix* graph = createGraphAdjMatrix(4);
  addEdgeAdjMatrix(graph, 1, 2);
  ASSERT_EQ(graph->adjMatrix[1][2], 1);
  ASSERT_EQ(graph->adjMatrix[2][1], 1);
  freeGraphAdjMatrix(graph);
}

// Тест для сравнения равных графов
TEST(GraphCompareTest, AreGraphsEqual_EqualGraphs) {
  GraphAdjList* graphAdjList = createGraphAdjList(3);
  addEdgeAdjList(graphAdjList, 0, 1);
  addEdgeAdjList(graphAdjList, 1, 2);

  GraphAdjMatrix* graphAdjMatrix = createGraphAdjMatrix(3);
  addEdgeAdjMatrix(graphAdjMatrix, 0, 1);
  addEdgeAdjMatrix(graphAdjMatrix, 1, 2);

  ASSERT_TRUE(areGraphsEqual(graphAdjList, graphAdjMatrix));

  freeGraphAdjList(graphAdjList);
  freeGraphAdjMatrix(graphAdjMatrix);
}

// Тест для сравнения неравных графов
TEST(GraphCompareTest, AreGraphsEqual_UnequalGraphs) {
  GraphAdjList* graphAdjList = createGraphAdjList(3);
  addEdgeAdjList(graphAdjList, 0, 1);

  GraphAdjMatrix* graphAdjMatrix = createGraphAdjMatrix(3);
  addEdgeAdjMatrix(graphAdjMatrix, 0, 2);

  ASSERT_FALSE(areGraphsEqual(graphAdjList, graphAdjMatrix));

  freeGraphAdjList(graphAdjList);
  freeGraphAdjMatrix(graphAdjMatrix);
}

// Тест для чтения графа списком смежности из файла
TEST(GraphAdjListTest, ReadGraphAdjListFromFile) {
    // Создаем тестовый файл
    FILE* file = fopen("test_adjlist.txt", "w");
    ASSERT_NE(file, nullptr);
    fprintf(file, "3 2\n0 1\n1 2\n");  // 3 вершины, 2 ребра
    fclose(file);

    GraphAdjList* graph = readGraphAdjListFromFile("test_adjlist.txt");
    ASSERT_NE(graph, nullptr);
    ASSERT_EQ(graph->V, 3);
    ASSERT_NE(graph->array[0].head, nullptr);
    ASSERT_EQ(graph->array[0].head->dest, 1);
    ASSERT_NE(graph->array[1].head, nullptr);
    ASSERT_EQ(graph->array[1].head->dest, 0);
    ASSERT_NE(graph->array[1].head->next, nullptr);
    ASSERT_EQ(graph->array[1].head->next->dest, 2);
    ASSERT_NE(graph->array[2].head, nullptr);
    ASSERT_EQ(graph->array[2].head->dest, 1);
    freeGraphAdjList(graph);
    remove("test_adjlist.txt"); // Удаляем тестовый файл
}

// Тест для чтения графа матрицей смежности из файла
TEST(GraphAdjMatrixTest, ReadGraphAdjMatrixFromFile) {
    // Создаем тестовый файл
    FILE* file = fopen("test_adjmatrix.txt", "w");
    ASSERT_NE(file, nullptr);
    fprintf(file, "3 2\n0 1\n1 2\n");  // 3 вершины, 2 ребра
    fclose(file);

    GraphAdjMatrix* graph = readGraphAdjMatrixFromFile("test_adjmatrix.txt");
    ASSERT_NE(graph, nullptr);
    ASSERT_EQ(graph->V, 3);
    ASSERT_EQ(graph->adjMatrix[0][1], 1);
    ASSERT_EQ(graph->adjMatrix[1][0], 1);
    ASSERT_EQ(graph->adjMatrix[1][2], 1);
    ASSERT_EQ(graph->adjMatrix[2][1], 1);
    freeGraphAdjMatrix(graph);
    remove("test_adjmatrix.txt"); // Удаляем тестовый файл
}

// Тест для сравнения пустых графов
TEST(GraphCompareTest, AreGraphsEqual_EmptyGraphs) {
  GraphAdjList* graphAdjList = createGraphAdjList(5); // Граф с 5 вершинами, но без ребер
  GraphAdjMatrix* graphAdjMatrix = createGraphAdjMatrix(5); // Граф с 5 вершинами, но без ребер

  ASSERT_TRUE(areGraphsEqual(graphAdjList, graphAdjMatrix));

  freeGraphAdjList(graphAdjList);
  freeGraphAdjMatrix(graphAdjMatrix);
}

// Тест для сравнения графов с разным количеством вершин
TEST(GraphCompareTest, AreGraphsEqual_DifferentVertexCount) {
  GraphAdjList* graphAdjList = createGraphAdjList(3);
  GraphAdjMatrix* graphAdjMatrix = createGraphAdjMatrix(5);

  ASSERT_FALSE(areGraphsEqual(graphAdjList, graphAdjMatrix));

  freeGraphAdjList(graphAdjList);
  freeGraphAdjMatrix(graphAdjMatrix);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}