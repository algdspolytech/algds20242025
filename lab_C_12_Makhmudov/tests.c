#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"



//tests
void testMatrixRead_Valid() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int vertices;
    readAdjMatrix("test_matrix.txt", graph, &vertices);

    int expected[MAX_VERTICES][MAX_VERTICES] = {
        {0,1,0},
        {1,0,1},
        {0,1,0}
    };
    assert(compareGraphs(graph, expected, vertices));
}

void testListRead_Valid() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int vertices;
    readAdjList("test_list.txt", graph, &vertices);

    int expected[MAX_VERTICES][MAX_VERTICES] = {
        {0,1,1},
        {1,0,0},
        {0,0,0}
    };
    assert(compareGraphs(graph, expected, vertices));
}

void testCompare_Identical() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { {0,1}, {1,0} };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { {0,1}, {1,0} };
    assert(compareGraphs(graph1, graph2, 2));
}

void testCompare_Different() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { {0,1}, {1,0} };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { {0,1}, {0,0} };
    assert(!compareGraphs(graph1, graph2, 2));
}

void testZeroVerticesMatrix_ReturnZero() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int vertices = -1;
    readAdjMatrix("zero_vertices.txt", graph, &vertices);
    assert(vertices == 0);
}

void testListNoEdges_Valid() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int vertices;
    readAdjList("no_edges_list.txt", graph, &vertices);

    int expected[MAX_VERTICES][MAX_VERTICES] = { {0} };
    assert(compareGraphs(graph, expected, vertices));
}

void testListMultipleEdges_Valid() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int vertices;
    readAdjList("multi_edge_list.txt", graph, &vertices);

    int expected[MAX_VERTICES][MAX_VERTICES] = {
        {0,1,1},
        {1,0,1},
        {1,1,0}
    };
    assert(compareGraphs(graph, expected, vertices));
}

void testMatrixListEquivalence_Equivalent() {
    int matrix_graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int list_graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int m_vertices, l_vertices;

    readAdjMatrix("equiv_matrix.txt", matrix_graph, &m_vertices);
    readAdjList("equiv_list.txt", list_graph, &l_vertices);

    assert(compareGraphs(matrix_graph, list_graph, m_vertices));
}

void testCompareDifferentSizes() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { {0,1}, {1,0} };
    int graph2[MAX_VERTICES][MAX_VERTICES] = {
        {0,1,0},
        {1,0,0},
        {0,0,0}
    };
    assert(compareGraphs(graph1, graph2, 2)); 
}

void testNoneBinaryWeights_Valid() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int vertices;
    readAdjMatrix("weighted_matrix.txt", graph, &vertices);

    int expected[MAX_VERTICES][MAX_VERTICES] = {
        {0,5},
        {3,0}
    };
    assert(compareGraphs(graph, expected, vertices));
}

int main() {
    testMatrixRead_Valid();
    testListRead_Valid();
    testCompare_Identical();
    testCompare_Different();
    testZeroVerticesMatrix_ReturnZero();
    testListNoEdges_Valid();
    testListMultipleEdges_Valid();
    testMatrixListEquivalence_Equivalent();
    testCompareDifferentSizes();
    testNoneBinaryWeights_Valid();

    printf("All tests passed!\n");
    return 0;
}

