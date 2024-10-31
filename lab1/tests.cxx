#include <gtest/gtest.h>

extern "C" {
#include "labC.h"
}

TEST(LabCTEST, CreateGraph_ValidArguments_Valid) {
    //Arrange
    int num_vertices = 5;

    //Act
    Graph* graph = createGraph(num_vertices);

    //Assert
    ASSERT_NE(graph, nullptr);
    ASSERT_EQ(graph->num_vertices, num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        ASSERT_EQ(graph->vertices[i].degree, 0);
    }
    free(graph);
}

TEST(LabCTEST, AddEdge_ValidArguments_Correct) {
    //Arrange
    Graph* graph = createGraph(4);

    //Act
    addEdge(graph, 0, 1);

    //Assert
    ASSERT_EQ(graph->vertices[0].degree, 1);
    ASSERT_EQ(graph->vertices[0].adj[0], 1);
    ASSERT_EQ(graph->vertices[1].degree, 1);
    ASSERT_EQ(graph->vertices[1].adj[0], 0);
    free(graph);
}


TEST(LabCTEST, findShortestPath_SimplePath_RightAnswer) {
    //Arrange
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    int start = 0;
    int end = 4;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_NE(path, nullptr);
    ASSERT_EQ(path[0], 4);
    ASSERT_EQ(path[1], 3);
    ASSERT_EQ(path[2], 2);
    ASSERT_EQ(path[3], 1);
    ASSERT_EQ(path[4], 0);
    free(path);
    free(graph);
}

TEST(LabCTEST, findShortestPath_NoPath_Nullptr) {
    //Arrange
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 3, 4);
    int start = 0;
    int end = 4;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_EQ(path, nullptr);
    free(graph);
}

TEST(LabCTEST, readGraphFromFile_RightPath_NotNull) {
    //Arrange
    const char* filename = "../graph.txt";

    //Act
    Graph* graph = readGraphFromFile(filename);

    //Assert
    ASSERT_NE(graph, nullptr);
    free(graph);
}

TEST(LabCTEST, readGraphFromFile_InvalidPath_Nullptr) {
    //Arrange
    const char* filename = "wrong.path.txt"; //Точка написана специально, чтобы файла не могло существовать

    //Act
    Graph* graph = readGraphFromFile(filename);

    //Assert
    ASSERT_EQ(graph, nullptr);
    free(graph);
}

TEST(LabCTEST, findShortestPath_FromFileFile_RightPath) {
    //Arrange
    Graph* graph = readGraphFromFile("../graph.txt");
    ASSERT_NE(graph, nullptr);
    int start = 0;
    int end = 3;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_NE(path, nullptr);
    ASSERT_EQ(path[0], 3);
    ASSERT_EQ(path[1], 1);
    ASSERT_EQ(path[2], 0);
    free(path);
    free(graph);
}

TEST(LabCTEST, createGraph_SingleVertex_Closure) {
    //Arrange
    Graph* graph = createGraph(1);
    int start = 0;
    int end = 0;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_NE(path, nullptr);
    ASSERT_EQ(path[0], 0);
    free(path);
    free(graph);
}

TEST(LabCTEST, findShortestPath_EmptyGraph_NullPath) {
    //Arrange
    Graph* graph = createGraph(0);
    int start = 0;
    int end = 0;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_EQ(*path, NULL);
    free(graph);
}

TEST(LabCTEST, findShortestPath_SimpleCycle_RightPath) {
    //Arrange
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0);
    int start = 0;
    int end = 2;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_NE(path, nullptr);
    ASSERT_EQ(path[0], 2);
    ASSERT_EQ(path[1], 1);
    ASSERT_EQ(path[2], 0);
    free(path);
    free(graph);
}

TEST(LabCTEST, findShortestPath_DisconnectedGraph_NoPath) {
    //Arrange
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 4, 5);
    int start = 0;
    int end = 5;

    //Act
    int* path = findShortestPath(graph, start, end);

    //Assert
    ASSERT_EQ(path, nullptr);
    free(graph);
}

TEST(LabCTEST, findShortestPath_PathWithMultipleEdges_ShortestPath) {
    //Arrange
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    int start = 0;
    int end = 4;

    //Act
    int* path = findShortestPath(graph, start, end);

    ///Assert
    ASSERT_NE(path, nullptr);
    ASSERT_EQ(path[0], 4);
    ASSERT_EQ(path[1], 3);
    ASSERT_EQ(path[2], 1);
    ASSERT_EQ(path[3], 0);
    free(path);
    free(graph);
}