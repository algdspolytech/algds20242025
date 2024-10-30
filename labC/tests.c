#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "functions.h"
#include "tests.h"

void test_create_node_OrdinaryNumber_return0_no1() {
    Node* node = NULL;
    node = create_node(TEST_NUM);
    assert(node != NULL && node->v == TEST_NUM && node->next == NULL);
}

void test_init_graph_OrdinarySettings_return0_no2() {
    Graph* g = init_graph(TEST_NUM);
    assert(g != NULL && g->size == TEST_NUM);
}

void test_add_edge_OrdinaryEdge_return0_no3() {
    Graph* g = init_graph(TEST_NUM);
    add_edge(g, 0, 1);
    assert(g->list[0]->v==1);
}

void test_add_edge_TwoSideEdge_return0_no4() {
    Graph* g = init_graph(TEST_NUM);
    add_edge(g, 0, 1);
    add_edge(g, 1, 0);
    assert(g->list[0]->v == 1);
    assert(g->list[1]->v == 0);
}

void test_add_edge_SomeEdges_return0_no5() {
    Graph* g = init_graph(TEST_NUM);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 3, 2);
    assert(g->list[0]->v == 1);
    assert(g->list[1]->v == 2);
    assert(g->list[3]->v == 2);
}

void test_read_graph_ReadFromFile_return0_no6() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g = read_graph("source.txt");
    assert(g != NULL && g->size == 8);
}

void test_find_path_WithPath_returnValidVal_no7() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g = read_graph("test_with_path.txt");
    printf("test_with_path: ");
    find_path(g, 0, 2);
}

void test_find_path_WithoutPath_returnValidVal_no8() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g = read_graph("test_without_path.txt");
    printf("test_without_path: ");
    find_path(g, 0, 2);
}

void test_find_path_OneVertex_returnValidVal_no9() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g = read_graph("test_without_path.txt");
    printf("test_one_vertex: ");
    find_path(g, 0, 0);
}