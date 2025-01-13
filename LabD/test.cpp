#include "labD.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

int connection_exists(Vertex* map, int u, int v) {
    for (int k = 0; k < map[u].degree; k++) {
        if (map[u].connections[k] == v)
            return 1;
    }
    return 0;
}

TEST(DepthFirstSearchTests, PathExists) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3, start = 1, target = 3, min_length = 2;
    initialize_graph(map, &total_vertices);
    insert_edge(map, 1, 2);
    insert_edge(map, 2, 3);
    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    EXPECT_GT(path_length, 0);
    EXPECT_EQ(traverse_path[path_length - 1], target);
    EXPECT_GE(path_length - 1, min_length);
}

TEST(DepthFirstSearchTests, NoPathForLargeK) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3, start = 1, target = 3, min_length = 3;
    initialize_graph(map, &total_vertices);
    insert_edge(map, 1, 2);
    insert_edge(map, 2, 3);
    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    EXPECT_EQ(path_length, 0);
}

TEST(DepthFirstSearchTests, NoPathExists) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3, start = 1, target = 3, min_length = 1;
    initialize_graph(map, &total_vertices);
    insert_edge(map, 1, 2);
    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    EXPECT_EQ(path_length, 0);
}

TEST(DepthFirstSearchTests, CycleInGraphNoValidPath) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3, start = 1, target = 3, min_length = 4;
    initialize_graph(map, &total_vertices);
    insert_edge(map, 1, 2);
    insert_edge(map, 2, 3);
    insert_edge(map, 3, 1);

    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    EXPECT_EQ(path_length, 0);
}

TEST(DepthFirstSearchTests, SingleNodeGraph) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 1, start = 1, target = 1, min_length = 0;
    initialize_graph(map, &total_vertices);

    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    EXPECT_GT(path_length, 0);
    EXPECT_EQ(traverse_path[path_length - 1], target);
}

TEST(DepthFirstSearchTests, EmptyGraph) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3, start = 1, target = 3, min_length = 1;
    initialize_graph(map, &total_vertices);
    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    EXPECT_EQ(path_length, 0);
}

TEST(EdgeTests, SingleEdge) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3;
    initialize_graph(map, &total_vertices);

    insert_edge(map, 1, 2);

    EXPECT_TRUE(connection_exists(map, 1, 2));
    EXPECT_TRUE(connection_exists(map, 2, 1));
    EXPECT_EQ(map[1].degree, 1);
    EXPECT_EQ(map[2].degree, 1);
}

TEST(EdgeTests, TwoEdges) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3;
    initialize_graph(map, &total_vertices);

    insert_edge(map, 1, 2);
    insert_edge(map, 2, 3);

    EXPECT_TRUE(connection_exists(map, 1, 2));
    EXPECT_TRUE(connection_exists(map, 2, 1));
    EXPECT_TRUE(connection_exists(map, 2, 3));
    EXPECT_TRUE(connection_exists(map, 3, 2));

    EXPECT_EQ(map[1].degree, 1);
    EXPECT_EQ(map[2].degree, 2);
    EXPECT_EQ(map[3].degree, 1);
}

TEST(EdgeTests, SelfLoop) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3;
    initialize_graph(map, &total_vertices);

    insert_edge(map, 1, 1);

    EXPECT_TRUE(connection_exists(map, 1, 1));
    EXPECT_EQ(map[1].degree, 1);
}

TEST(EdgeTests, DisconnectedGraph) {
    Vertex map[MAX_VERTICES + 1];
    int total_vertices = 3;
    initialize_graph(map, &total_vertices);

    insert_edge(map, 1, 2);

    EXPECT_TRUE(connection_exists(map, 1, 2));
    EXPECT_TRUE(connection_exists(map, 2, 1));
    EXPECT_EQ(map[1].degree, 1);
    EXPECT_EQ(map[2].degree, 1);
    EXPECT_EQ(map[3].degree, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    cout << "Starting Tests" << endl;

    return RUN_ALL_TESTS();
}
