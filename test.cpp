#include "code.h"
#include <gtest/gtest.h>

TEST(Create) {
    Vertex* node = create(1);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->vertex, 1);
    EXPECT_EQ(node->edges, nullptr);
    free(node);
}

TEST(AddVertex) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertex, 1);
    EXPECT_EQ(graph->edges, nullptr);
    free(graph);
}

TEST(Find_Found) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    Vertex* found = find(graph, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->vertex, 1);
    free(graph);
}

TEST(Find_ReturnNull) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    Vertex* found = find(graph, 2);
    EXPECT_EQ(found, nullptr);
    free(graph);
}

TEST(AddEdge_SingieAdd) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    add_edge(graph, 2);
    ASSERT_NE(graph->edges, nullptr);
    EXPECT_EQ(graph->edges->vertex, 2);
    free(graph);
}

TEST(AddEdge_MultipleAdd) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    add_edge(graph, 2);
    add_edge(graph, 3);
    ASSERT_NE(graph->edges, nullptr);
    EXPECT_EQ(graph->edges->vertex, 3);
    EXPECT_EQ(graph->edges->next->vertex, 2);
    free(graph);
}

TEST(FreeGraph_SingleVertex) {
    Vertex* graph = create(1);
    ASSERT_NO_THROW(free_graph(graph));
}

TEST(FreeGraph_MultipleVertex) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    ASSERT_NO_THROW(free_graph(graph));
}

TEST(BuildVertexCover) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    add_edge(graph, 2);

    int cover[10];
    int cover_size = build_vertex_cover(graph, cover, 10);
    EXPECT_EQ(cover_size, 1);

    free(graph);
}

TEST(BuildVertexCover_CoverSizeZero) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    int cover[10];
    int cover_size = build_vertex_cover(graph, cover, 10);
    EXPECT_EQ(cover_size, 0);
    free(graph);
}

TEST(AreAllEdgesCovered_False) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    add_vertex(&graph, 3);
    add_edge(graph, 2);
    add_edge(graph->next, 3);

    int cover[1] = { 1 };
    EXPECT_FALSE(are_all_edges_covered(graph, cover, 1));
    free(graph);
}

TEST(VertexCover_True) {
    Vertex* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    add_edge(graph, 2);

    EXPECT_TRUE(vertex_cover(graph, 2, 1));
    free(graph);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
