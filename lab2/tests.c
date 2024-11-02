#include "Header.h"
#include <assert.h>
#include <stdio.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

// Graph matching tests

void CompareGraphs_IdenticalGraphs_no1() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_identical_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_identical_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==1);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_DifferentVertexCount_no2() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_diff_vertex_count_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_diff_vertex_count_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==0);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_EmptyGraphs_no3() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_empty_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_empty_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==1);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_OneEmptyOneNonEmpty_no4() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_non_empty_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_empty_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==0);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_SingleVertex_no5() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_single_vertex_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_single_vertex_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==1);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_SimilarStructures_no6() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_similar_structure_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_similar_structure_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==0);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_DifferentEdges_no7() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_diff_edges_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_diff_edges_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==0);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_SameEdgesDifferentOrder_no8() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_same_edges_diff_order_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_same_edges_diff_order_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==1);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_NegativeEdges_no9() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_negative_edges_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_negative_edges_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==0);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

void CompareGraphs_LargeGraphs_no10() {
    GraphMatrix* matrixGraph = createGraphFromMatrix("test_large_matrix.txt");
    GraphList* listGraph = createGraphFromList("test_large_list.txt");

    assert(compareGraphs(matrixGraph, listGraph)==1);

    freeGraphMatrix(matrixGraph);
    freeGraphList(listGraph);
}

// Запуск всех тестов
void runAllTests() {

    void CompareGraphs_IdenticalGraphs_no1();
    
    void CompareGraphs_DifferentVertexCount_no2();
    
    void CompareGraphs_EmptyGraphs_no3();
    
    void CompareGraphs_OneEmptyOneNonEmpty_no4();
    
    void CompareGraphs_SingleVertex_no5();
    
    void CompareGraphs_SimilarStructures_no6();
    
    void CompareGraphs_DifferentEdges_no7();
    
    void CompareGraphs_SameEdgesDifferentOrder_no8();
    
    void CompareGraphs_NegativeEdges_no9();
    
    void CompareGraphs_LargeGraphs_no10();
    
    printf("ALL TEST RAN PERFECTLY\n");
}