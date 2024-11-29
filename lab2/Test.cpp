#include <gtest/gtest.h>
extern "C" {
#include "graph.h"
}

// Тест 1: Путь существует между вершинами 0 и 3
TEST(GraphTest, PathExists) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);

    ASSERT_TRUE(hasPath(&g, 0, 3));
}

// Тест 2: Путь не существует между вершинами 0 и 4
TEST(GraphTest, NoPathExists) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);

    ASSERT_FALSE(hasPath(&g, 0, 4));
}

// Тест 3: Путь существует между вершинами 1 и 2
TEST(GraphTest, DirectPathExists) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);

    ASSERT_TRUE(hasPath(&g, 1, 2));
}

// Тест 4: Проверка на граф без рёбер
TEST(GraphTest, NoEdges) {
    Graph g;
    initGraph(&g, 5);

    ASSERT_FALSE(hasPath(&g, 0, 4));  // Без рёбер путь не существует
}

// Тест 5: Путь существует в графе с петлёй
TEST(GraphTest, PathWithLoop) {
    Graph g;
    initGraph(&g, 3);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 0);  // Петля

    ASSERT_TRUE(hasPath(&g, 0, 2));
    ASSERT_TRUE(hasPath(&g, 2, 0));
}

// Тест 6: Путь существует между вершинами, добавленными через несколько рёбер
TEST(GraphTest, PathWithMultipleEdges) {
    Graph g;
    initGraph(&g, 6);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);

    ASSERT_TRUE(hasPath(&g, 0, 4));  // Путь через несколько рёбер
}

// Тест 7: Проверка на граф с несколькими компонентами
TEST(GraphTest, MultipleComponents) {
    Graph g;
    initGraph(&g, 6);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 3, 4);

    ASSERT_FALSE(hasPath(&g, 2, 4));  // Компоненты не соединены
    ASSERT_TRUE(hasPath(&g, 0, 2));   // Путь существует в одной компоненте
}

// Тест 8: Путь существует, но граф содержит циклы
TEST(GraphTest, PathInGraphWithCycles) {
    Graph g;
    initGraph(&g, 4);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 0);  // Цикл

    ASSERT_TRUE(hasPath(&g, 0, 3));  // Путь существует
}

// Тест 9: Путь между одной и той же вершиной (не должно быть пути)
TEST(GraphTest, SameStartEnd) {
    Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);

    ASSERT_TRUE(hasPath(&g, 2, 2));  // Путь существует (из самой себя)
}

// Тест 10: Граф с единственным ребром
TEST(GraphTest, SingleEdgeGraph) {
    Graph g;
    initGraph(&g, 2);
    addEdge(&g, 0, 1);

    ASSERT_TRUE(hasPath(&g, 0, 1));  // Путь существует
    ASSERT_TRUE(hasPath(&g, 1, 0));  // Путь существует в обе стороны
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}