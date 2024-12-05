#define _CRT_SECURE_NO_WARNINGS


#include <assert.h>
#include "funcs.h"
#include "tests.h"


void test_readGraph_validFile_No1()
{
    Graph graph;
    assert(readGraph("test1_input.txt", &graph) == true);
    assert(graph.n == 4);
    assert(graph.k == 2);
    assert(graph.adj[0][1] == 1); // Ребро 1-2
    assert(graph.adj[2][3] == 1); // Ребро 3-4
    printf("test_readGraph_validFile_No1: Passed\n");
}

void test_readGraph_emptyFile_No2() {
    Graph graph;
    assert(readGraph("empty_input.txt", &graph) == false);
    printf("test_readGraph_emptyFile_No2: Passed\n");
}

void test_isCovered_allVerticesIncluded_No3() {
    Graph graph;
    readGraph("test1_input.txt", &graph);
    bool included[MAX_VERTICES] = { true, true, true, true };
    assert(isCovered(&graph, included) == true);
    printf("test_isCovered_allVerticesIncluded_No3: Passed\n");
}

void test_isCovered_notCovered_No4() {
    Graph graph;
    readGraph("test1_input.txt", &graph);
    bool included[MAX_VERTICES] = { true, false, false, false };
    assert(isCovered(&graph, included) == false);
    printf("test_isCovered_notCovered_No4: Passed\n");
}

void test_findVertexCover_minimalCover_No5() {
    Graph graph;
    bool included[MAX_VERTICES] = { false };
    readGraph("test2_input.txt", &graph); // Граф: 1-2, 2-3, 1-3
    assert(findVertexCover(&graph, included, 0, 0) == true);
    assert(included[0] == true || included[1] == true);
    printf("test_findVertexCover_minimalCover_No5: Passed\n");
}

void test_findVertexCover_impossible_No6() {
    Graph graph;
    bool included[MAX_VERTICES] = { false };
    readGraph("test3_input.txt", &graph); // Граф, где K слишком мал
    assert(findVertexCover(&graph, included, 0, 0) == false);
    printf("test_findVertexCover_impossible_No6: Passed\n");
}

void test_isCovered_emptyGraph_No7() {
    Graph emptyGraph = { 0, 0, {{0}} };
    bool included[MAX_VERTICES] = { false };
    assert(isCovered(&emptyGraph, included) == true); // Пустой граф всегда покрыт
    printf("test_isCovered_emptyGraph_No7: Passed\n");
}

void test_isCovered_selfLoop_No8() {
    Graph loopGraph = { 1, 1, {{1}} }; // Вершина 1 с петлёй
    bool included[MAX_VERTICES] = { true };
    assert(isCovered(&loopGraph, included) == true);
    printf("test_isCovered_selfLoop_No8: Passed\n");
}

void test_findVertexCover_chainGraph_No9() {
    Graph graph;
    readGraph("chain_input.txt", &graph); // Граф: 1-2-3-4-5
    bool included[MAX_VERTICES] = { false };
    assert(findVertexCover(&graph, included, 0, 0) == true);
    printf("test_findVertexCover_chainGraph_No9: Passed\n");
}

void test_findVertexCover_singleEdge_No10() {
    Graph singleEdgeGraph = { 2, 1, {{0, 1}, {1, 0}} }; // Граф с одним ребром 1-2
    bool included[MAX_VERTICES] = { false };
    assert(findVertexCover(&singleEdgeGraph, included, 0, 0) == true);
    assert(included[0] == true || included[1] == true);
    printf("test_findVertexCover_singleEdge_No10: Passed\n");
}
