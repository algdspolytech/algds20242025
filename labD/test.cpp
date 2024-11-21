#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../AlgosiD/main.h"
}
class GraphTest : public ::testing::Test {
protected:
    Graph graph;
};

TEST_F(GraphTest, InitialiseGraphWithThreeVertices_no1) {
    graph.num_vertices = 3;
    GraphInitialise(&graph);

    for (int i = 0; i < graph.num_vertices; i++) {
        for (int j = 0; j < graph.num_vertices; j++) {
            EXPECT_EQ(graph.adj[i][j], 0);
        }
    }
}

TEST_F(GraphTest, InitialiseGraphWithZeroVertices_no2) {
    graph.num_vertices = 0;
    GraphInitialise(&graph);
}

class NullGraphTest : public ::testing::Test {
protected:
    Graph graph;

    void SetUp() override {
        graph.num_vertices = 0;
        for (int i = 0; i < MAX_V; i++)
            for (int j = 0; j < MAX_V; j++)
                graph.adj[i][j] = 0;
    }
};

TEST_F(NullGraphTest, EmptyGraphIsNull_no3) {
    graph.num_vertices = 0;
    EXPECT_EQ(GraphIsNull(graph), 1);
}

TEST_F(NullGraphTest, FullNullGraph_no4) {
    graph.num_vertices = 3;
    EXPECT_EQ(GraphIsNull(graph), 1);
}

TEST_F(NullGraphTest, NonNullGraph_no5) {
    graph.num_vertices = 3;
    graph.adj[0][1] = 1;
    EXPECT_EQ(GraphIsNull(graph), 0);
}

TEST_F(NullGraphTest, GraphWithSelfLoop_no6) {
    graph.num_vertices = 2;
    graph.adj[0][0] = 1;
    EXPECT_EQ(GraphIsNull(graph), 0);
}

class FindMaxTest : public ::testing::Test {
protected:
    Graph graph;

    void SetUp() override {
        graph.num_vertices = 0;
        for (int i = 0; i < MAX_V; i++)
            for (int j = 0; j < MAX_V; j++)
                graph.adj[i][j] = 0;
    }
};

TEST_F(FindMaxTest, NoConnections_no7) {
    graph.num_vertices = 3;
    EXPECT_EQ(FindMax(graph, 0), 0);
}

TEST_F(FindMaxTest, SimpleConnections_no8) {
    graph.num_vertices = 3;
    graph.adj[0][1] = graph.adj[1][0] = 1;
    EXPECT_EQ(FindMax(graph, 0), 0);
}

TEST_F(FindMaxTest, DifferentConnections_no9) {
    graph.num_vertices = 3;
    graph.adj[0][1] = graph.adj[1][0] = 1;
    graph.adj[1][2] = graph.adj[2][1] = 1;
    graph.adj[0][3] = graph.adj[3][0] = 1;

    EXPECT_EQ(FindMax(graph, 0), 1);
}

TEST_F(FindMaxTest, StartFromSecondVertex_no10) {
    graph.num_vertices = 5;
    graph.adj[0][1] = graph.adj[1][0] = 1;
    graph.adj[0][2] = graph.adj[2][0] = 1;
    graph.adj[1][3] = graph.adj[3][1] = 1;
    graph.adj[1][4] = graph.adj[4][1] = 1;

    EXPECT_EQ(FindMax(graph, 1), 1);
}

class VertexCoverTests : public ::testing::Test {
protected:
    Graph graph;
    UsedVertexes uv;
    void SetUp() override {
        graph.num_vertices = 0;
        for (int i = 0; i < MAX_V; i++) {
            uv.Vertexes[i] = 1;
        }
        for (int i = 0; i < MAX_V; i++)
            for (int j = 0; j < MAX_V; j++)
                graph.adj[i][j] = 0;
    }
};
TEST_F(VertexCoverTests, GraphIsEmpty_no11) {
    EXPECT_EQ(FindVertexCover(graph, 0, 0, &uv), 0);
}

TEST_F(VertexCoverTests, GraphWithTwoVertices_no12) {
    graph.num_vertices = 2;
    graph.adj[0][1] = graph.adj[1][0] = 1;
    int result = FindVertexCover(graph, 0, 0, &uv);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uv.Vertexes[0], 0);
}

TEST_F(VertexCoverTests, GraphWithThreeVerticesAndTwoEdges_no13) {
    graph.num_vertices = 3;
    graph.adj[0][1] = graph.adj[1][0] = 1;
    graph.adj[0][2] = graph.adj[2][0] = 1;
    int result = FindVertexCover(graph, 0, 0, &uv);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uv.Vertexes[0], 0);
}