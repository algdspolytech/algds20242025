#include "graph_sort.h"
#include <gtest/gtest.h>

// Тест на корректное построение графа
TEST(GraphTest, AddEdgeTest) {
    Graph graph;
    initializeGraph(&graph);

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");

    int indexA = findWordIndex(&graph, "a");
    int indexB = findWordIndex(&graph, "b");
    int indexC = findWordIndex(&graph, "c");

    ASSERT_EQ(graph.adjMatrix[indexA][indexB], 1);
    ASSERT_EQ(graph.adjMatrix[indexB][indexC], 1);
    ASSERT_EQ(graph.adjMatrix[indexA][indexC], 0);
}

// Тест на топологическую сортировку без циклов
TEST(GraphTest, TopologicalSortTest) {
    Graph graph;
    initializeGraph(&graph);

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");

    char output[MAX_WORDS][MAX_LEN];
    int outputSize;

    bool result = topologicalSort(&graph, output, &outputSize);

    ASSERT_TRUE(result); // Сортировка успешна
    EXPECT_STREQ(output[0], "a");
    EXPECT_STREQ(output[1], "b");
    EXPECT_STREQ(output[2], "c");
}

// Тест на цикл в графе
TEST(GraphTest, CycleDetectionTest) {
    Graph graph;
    initializeGraph(&graph);

    addEdge(&graph, "a", "b");
    addEdge(&graph, "b", "c");
    addEdge(&graph, "c", "a"); // Создаем цикл

    char output[MAX_WORDS][MAX_LEN];
    int outputSize;

    bool result = topologicalSort(&graph, output, &outputSize);

    ASSERT_FALSE(result); // Топологическая сортировка невозможна
}

// Тест на обработку входных данных
TEST(GraphTest, ReadInputFileTest) {
    const char* inputFilename = "test_input.txt";
    FILE* file = fopen(inputFilename, "w");
    ASSERT_TRUE(file != nullptr);

    // Записываем тестовые данные
    fprintf(file, "a b c d\n");
    fprintf(file, "a b\n");
    fprintf(file, "b c\n");
    fclose(file);

    Graph graph;
    readInputFile(inputFilename, &graph);

    ASSERT_EQ(graph.wordCount, 4);

    int indexA = findWordIndex(&graph, "a");
    int indexB = findWordIndex(&graph, "b");
    int indexC = findWordIndex(&graph, "c");

    ASSERT_EQ(graph.adjMatrix[indexA][indexB], 1);
    ASSERT_EQ(graph.adjMatrix[indexB][indexC], 1);
}

// Тест на запись в файл
TEST(GraphTest, WriteOutputFileTest) {
    const char* outputFilename = "test_output.txt";

    char output[MAX_WORDS][MAX_LEN] = { "a", "b", "c" };
    int outputSize = 3;

    writeOutputFile(outputFilename, output, outputSize, false);

    FILE* file = fopen(outputFilename, "r");
    ASSERT_TRUE(file != nullptr);

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    ASSERT_STREQ(buffer, "a b c \n");
}

// Тест на запись ошибки в файл
TEST(GraphTest, WriteErrorTest) {
    const char* outputFilename = "test_error.txt";
    writeOutputFile(outputFilename, nullptr, 0, true);

    FILE* file = fopen(outputFilename, "r");
    ASSERT_TRUE(file != nullptr);

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    ASSERT_STREQ(buffer, "[Error]\n");
}

// Главная функция тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}