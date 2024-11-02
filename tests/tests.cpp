#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "dfs.h"
}

FILE* MakeTMP(const char* data) {
    FILE* file = fopen("TMP", "w");
    fputs(data, file);
    fclose(file);

    file = fopen("TMP", "r");
    return file;
}

int** MatrixBypass(const char* content, int* n) {
    FILE* file = MakeTMP(content);
    int** matrix = DFS_ReadFromFile(file, n);
    fclose(file);
    return matrix;
}

TEST(DFS_IsConnectedTest, SameNode) {
    const char* content = "1\n"
                          "0"; // Single node graph
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(0, 0, matrix, n), 1);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, NotConnectedDueToOrientation) {
    const char* content = "3\n"
                          "0 1 0\n"
                          "0 0 1\n"
                          "0 0 0\n"; // Directed graph: 0 -> 1 -> 2
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(2, 1, matrix, n), 0);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, DifferentComponentsInUndirectedGraph) {
    const char* content = "4\n"
                          "0 1 0 0\n"
                          "1 0 0 0\n"
                          "0 0 0 1\n"
                          "0 0 1 0\n"; // Two components: (0,1) and (2,3)
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(0, 2, matrix, n), 0);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, ConnectedNodes) {
    const char* content = "3\n"
                          "0 1 1\n"
                          "1 0 1\n"
                          "1 1 0\n"; // K3
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(0, 2, matrix, n), 1);
\
    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, CheckNonAdjacentNodesInDirectedGraph) {
    const char* content = "4\n"
                          "0 1 0 0\n"
                          "0 0 1 0\n"
                          "0 0 0 1\n"
                          "0 0 0 0\n"; // Directed graph with no direct connection between nodes
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(3, 1, matrix, n), 0);
    // Clean up
    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, SelfLoop) {
    const char* content = "2\n"
                          "1 1\n"
                          "1 0\n"; // Graph with a self-loop at node 0
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(0, 0, matrix, n), 1);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, IsolatedNode) {
    const char* content = "5\n"
                          "0 1 0 0 0\n"
                          "1 0 0 1 1\n"
                          "0 0 0 0 0\n"
                          "0 1 0 1 1\n"
                          "0 1 1 1 0\n"; // Node 2 is isolated
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(2, 3, matrix, n), 0);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, FullyConnectedUndirectedGraph) {
    const char* content = "4\n"
                          "0 1 1 1\n"
                          "1 0 1 1\n"
                          "1 1 0 1\n"
                          "1 1 1 0\n";
    int n;
    int** matrix = MatrixBypass(content, &n);

    ASSERT_EQ(DFS_IsConnected(2, 3, matrix, n), 1);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, MultiplePaths) {
    const char* content = "5\n"
                          "0 1 1 0 0\n"
                          "1 0 1 1 0\n"
                          "1 1 0 1 1\n"
                          "0 1 1 0 1\n"
                          "0 0 1 1 0\n";
    int n;
    int** matrix = MatrixBypass(content, &n);
    ASSERT_EQ(DFS_IsConnected(0, 4, matrix, n), 1);

    DFS_MatrixDispose(matrix, n);
}

TEST(DFS_IsConnectedTest, NonExistentNode) {
    const char* content = "3\n"
                          "0 1 1\n"
                          "1 0 1\n"
                          "1 1 0\n";
    int n;
    int** matrix = MatrixBypass(content, &n);
    
    ASSERT_EQ(DFS_IsConnected(-1, -2, matrix, n), 0);

    DFS_MatrixDispose(matrix, n);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
