#include <gtest/gtest.h>
#include "graph.h" // Подключите ваш заголовочный файл с реализацией функций

class GraphTest : public ::testing::Test {
protected:
    Graph graph;
    int V = 6; // Число вершин графа

    void SetUp() override {
        initGraph(&graph, V); // Инициализация графа
    }

    void TearDown() override {
        for (int i = 0; i < V; i++) {
            free(graph.adj[i]); // Освобождение памяти
        }
    }
};

// Тест 1: Путь существует
TEST_F(GraphTest, PathExists) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 3, 3, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 4); // Путь: 1 -> 2 -> 3 -> 4
}

// Тест 2: Путь отсутствует
TEST_F(GraphTest, PathNotExists) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 5, 3, 0, path, &pathLength);

    EXPECT_FALSE(result);
    EXPECT_EQ(pathLength, 0);
}

// Тест 3: Циклический граф
TEST_F(GraphTest, CyclicGraph) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 0);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 1, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 2); // Путь: 1 -> 2
}

// Тест 4: Линейный граф
TEST_F(GraphTest, LinearGraph) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 5, 5, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 6); // Путь: 1 -> 2 -> 3 -> 4 -> 5 -> 6
}

// Тест 5: Несвязный граф
TEST_F(GraphTest, DisconnectedGraph) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 2, 3);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 3, 2, 0, path, &pathLength);

    EXPECT_FALSE(result);
    EXPECT_EQ(pathLength, 0);
}

// Тест 6: Минимальная длина пути
TEST_F(GraphTest, MinLengthPath) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 1, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 3); // Путь: 1 -> 2 -> 3
}

// Тест 7: Граф с петлями
TEST_F(GraphTest, GraphWithLoops) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 2); // Петля

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 2, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 3); // Путь: 1 -> 2 -> 3
}

// Тест 8: Большой K
TEST_F(GraphTest, LargeK) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 5, 0, path, &pathLength);

    EXPECT_FALSE(result); // Пути длиной >= 5 нет
}

// Тест 9: Несколько путей
TEST_F(GraphTest, MultiplePaths) {
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 0, 2);

    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 2, 1, 0, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 2); // Выбирается первый путь: 1 -> 3
}

// Тест 10: Одинокая вершина
TEST_F(GraphTest, SingleNode) {
    int path[MAX_VERTICES], pathLength = 0;
    bool result = dfs(&graph, 0, 0, 1, 0, path, &pathLength);

    EXPECT_FALSE(result); // Пути нет
    EXPECT_EQ(pathLength, 0);
}