#include "gtest/gtest.h"
extern "C" {
#include "../src/longestPath.h"
}

TEST(LongestPathTest, PathExistsExactLengthK) {
    Graph graph;
    initGraph(&graph, 5);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 1, 5, 4, path, &pathLength));
    EXPECT_EQ(pathLength, 5);
}

TEST(LongestPathTest, PathExistsGreaterThanK) {
    Graph graph;
    initGraph(&graph, 6);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 5, 6);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 1, 6, 4, path, &pathLength));
    EXPECT_GE(pathLength - 1, 4);
}

TEST(LongestPathTest, PathDoesNotExist) {
    Graph graph;
    initGraph(&graph, 3);

    addEdge(&graph, 1, 2);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_FALSE(findPath(&graph, 1, 3, 2, path, &pathLength));
}

TEST(LongestPathTest, PathTooShort) {
    Graph graph;
    initGraph(&graph, 4);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_FALSE(findPath(&graph, 1, 4, 5, path, &pathLength));
}

TEST(LongestPathTest, DisconnectedGraph) {
    Graph graph;
    initGraph(&graph, 5);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 4, 5);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_FALSE(findPath(&graph, 1, 5, 1, path, &pathLength));
}

TEST(LongestPathTest, SingleVertexGraph) {
    Graph graph;
    initGraph(&graph, 1);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 1, 1, 0, path, &pathLength));
    EXPECT_EQ(pathLength, 1);
}

TEST(LongestPathTest, StartEqualsEnd) {
    Graph graph;
    initGraph(&graph, 4);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 2, 2, 0, path, &pathLength));
    EXPECT_EQ(pathLength, 1);
}

TEST(LongestPathTest, CycleGraph) {
    Graph graph;
    initGraph(&graph, 4);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 1);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 1, 3, 2, path, &pathLength));
    EXPECT_GE(pathLength - 1, 2);
}

TEST(LongestPathTest, LongPathInDenseGraph) {
    Graph graph;
    initGraph(&graph, 6);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 4);
    addEdge(&graph, 3, 5);
    addEdge(&graph, 4, 6);
    addEdge(&graph, 5, 6);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 1, 6, 3, path, &pathLength));
    EXPECT_GE(pathLength - 1, 3);
}

TEST(LongestPathTest, PathExceedsVertexCount) {
    Graph graph;
    initGraph(&graph, 6);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 5, 6);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_FALSE(findPath(&graph, 1, 6, 10, path, &pathLength));
}

TEST(LongestPathTest, PathExistsInSparseGraph) {
    Graph graph;
    initGraph(&graph, 8);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 5, 6);
    addEdge(&graph, 6, 7);
    addEdge(&graph, 7, 8);

    int path[MAX_VERTICES];
    int pathLength;
    EXPECT_TRUE(findPath(&graph, 1, 8, 6, path, &pathLength));
    EXPECT_GE(pathLength - 1, 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}