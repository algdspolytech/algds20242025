#include "pch.h"
#include <gtest/gtest.h>
#include "pch.cpp" // Предполагается, что основной код сохранен в `graph.h`

class GraphTest : public ::testing::Test {
protected:
    Graph* graph;

    void SetUp() override {
        graph = createGraph(5);
        addEdge(graph, 0, 1);
        addEdge(graph, 0, 2);
        addEdge(graph, 1, 2);
        addEdge(graph, 1, 3);
        addEdge(graph, 3, 4);
    }

    void TearDown() override {
        freeGraph(graph);
    }
};

TEST_F(GraphTest, PathExists) {
    EXPECT_TRUE(pathExists(graph, 0, 4));
    EXPECT_TRUE(pathExists(graph, 0, 1));
    EXPECT_TRUE(pathExists(graph, 1, 3));
}

TEST_F(GraphTest, NoPathExists) {
    EXPECT_FALSE(pathExists(graph, 2, 4));
    EXPECT_FALSE(pathExists(graph, 3, 0));
}

TEST_F(GraphTest, SameVertex) {
    EXPECT_TRUE(pathExists(graph, 1, 1));
}

TEST_F(GraphTest, DisconnectedVertices) {
    EXPECT_FALSE(pathExists(graph, 2, 3));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}