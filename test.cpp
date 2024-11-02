#include <gtest/gtest.h>
extern "C" {
#include "lab_c.h"
}


TEST(GraphTest, LoadGraphFromFile_ValidFile_no1) {
    Graph graph;
    load_graph_from_file(&graph, "test.txt");
    EXPECT_EQ(graph.num_vertices, 5);
    EXPECT_EQ(graph.adjacency_matrix[0][1], 1);
}

TEST(GraphTest, PathExists_ValidPath_no2) {
    Graph graph;
    init_graph(&graph, 5);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);
    add_edge(&graph, 2, 3);
    EXPECT_TRUE(path_exists(&graph, 0, 3));
}

TEST(GraphTest, PathExists_NoPath_no3) {
    Graph graph;
    init_graph(&graph, 5);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 2, 3);
    EXPECT_FALSE(path_exists(&graph, 0, 3));
}

TEST(GraphTest, PathExists_SingleVertex_no4) {
    Graph graph;
    init_graph(&graph, 1);
    EXPECT_TRUE(path_exists(&graph, 0, 0));
}

TEST(GraphTest, PathExists_EmptyGraph_no5) {
    Graph graph;
    init_graph(&graph, 0);
    EXPECT_FALSE(path_exists(&graph, 0, 1));
}

TEST(GraphTest, PathExists_TwoVerticesConnected_no6) {
    Graph graph;
    init_graph(&graph, 2);
    add_edge(&graph, 0, 1);
    EXPECT_TRUE(path_exists(&graph, 0, 1));
}

TEST(GraphTest, PathExists_TwoVerticesDisconnected_no7) {
    Graph graph;
    init_graph(&graph, 2);
    EXPECT_FALSE(path_exists(&graph, 0, 1));
}

TEST(GraphTest, PathExists_CycleInGraph_no8) {
    Graph graph;
    init_graph(&graph, 3);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);
    add_edge(&graph, 2, 0);
    EXPECT_TRUE(path_exists(&graph, 0, 2));
}

TEST(GraphTest, PathExists_LargeGraph_no9) {
    Graph graph;
    init_graph(&graph, 6);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 3, 4);
    add_edge(&graph, 4, 5);
    EXPECT_TRUE(path_exists(&graph, 0, 5));
}

TEST(GraphTest, PathExists_LargeGraph_NoPath_no10) {
    Graph graph;
    init_graph(&graph, 6);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 4, 5);
    EXPECT_FALSE(path_exists(&graph, 0, 5));
}

TEST(GraphTest, PathExists_MultiplePaths_no11) {
    Graph graph;
    init_graph(&graph, 4);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);
    add_edge(&graph, 0, 2);     
    EXPECT_TRUE(path_exists(&graph, 0, 2));
}

TEST(GraphTest, PathExists_ComplexGraph_no12) {
    Graph graph;
    init_graph(&graph, 7);
    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 3, 4);
    add_edge(&graph, 4, 5);
    add_edge(&graph, 5, 6);

    EXPECT_TRUE(path_exists(&graph, 0, 6));
}
    