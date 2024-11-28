#include "LabD_lib.h"

#include <gtest/gtest.h>

TEST(CreateVertex_ValidInput_NodeCreated_1) {
    VertexNode* node = create_vertex(1);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->vertex, 1);
    EXPECT_EQ(node->edges, nullptr);
    free(node);
}

TEST(AddVertex_NewVertexAdded_VertexExistsInGraph_2) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertex, 1);
    EXPECT_EQ(graph->edges, nullptr);
    free_graph(graph);
}

TEST(FindVertex_VertexExists_FoundVertex_3) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    VertexNode* found = find_vertex(graph, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->vertex, 1);
    free_graph(graph);
}

TEST(FindVertex_VertexNotExists_ReturnNull_4) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    VertexNode* found = find_vertex(graph, 2);
    EXPECT_EQ(found, nullptr);
    free_graph(graph);
}

TEST(AddEdge_ValidEdgeAdded_EdgeExists_5) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    add_edge(graph, 2);
    ASSERT_NE(graph->edges, nullptr);
    EXPECT_EQ(graph->edges->vertex, 2);
    free_graph(graph);
}

TEST(AddEdge_MultipleEdgesAdded_AllEdgesExist_6) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    add_edge(graph, 2);
    add_edge(graph, 3);
    ASSERT_NE(graph->edges, nullptr);
    EXPECT_EQ(graph->edges->vertex, 3);
    EXPECT_EQ(graph->edges->next->vertex, 2);
    free_graph(graph);
}

TEST(FreeGraph_SingleVertex_VertexFreed_7) {
    VertexNode* graph = create_vertex(1);
    ASSERT_NO_THROW(free_graph(graph));
}

TEST(FreeGraph_MultipleVertices_AllFreed_8) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    ASSERT_NO_THROW(free_graph(graph));
}

TEST(BuildVertexCover_NoEdges_CoverSizeZero_9) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    int cover[10];
    int cover_size = build_vertex_cover(graph, cover, 10);
    EXPECT_EQ(cover_size, 0);
    free_graph(graph);
}

TEST(BuildVertexCover_SufficientK_CoverSizeK_10) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    add_edge(graph, 2);

    int cover[10];
    int cover_size = build_vertex_cover(graph, cover, 10);
    EXPECT_EQ(cover_size, 1);

    free_graph(graph);
}

TEST(AreAllEdgesCovered_NotAllCovered_ReturnFalse_11) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    add_vertex(&graph, 3);
    add_edge(graph, 2);
    add_edge(graph->next, 3);

    int cover[1] = { 1 };
    EXPECT_FALSE(are_all_edges_covered(graph, cover, 1));
    free_graph(graph);
}

TEST(VertexCover_PossibleWithinK_CoverFound_12) {
    VertexNode* graph = nullptr;
    add_vertex(&graph, 1);
    add_vertex(&graph, 2);
    add_edge(graph, 2);

    EXPECT_TRUE(vertex_cover(graph, 2, 1));
    free_graph(graph);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}