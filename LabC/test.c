#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../LabC/Source.h"

void TestwriteAdjacencyList_ValidGraph_no1() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    graph[0][1] = 1;
    graph[1][2] = 1;

    writeAdjacencyList("test_list1.txt", graph, 3);
    FILE* file = fopen("test_list1.txt", "r");
    assert(file != NULL);
    fclose(file);
}

void TestwriteAdjacencyMatrix_ValidGraph_no2() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    graph[0][1] = 1;
    graph[1][0] = 1;

    writeAdjacencyMatrix("test_matrix1.txt", graph, 2);
    FILE* file = fopen("test_matrix1.txt", "r");
    assert(file != NULL);
    fclose(file);
}

void TestcompareGraphs_SameGraphs_no3() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };

    graph1[0][1] = 1;
    graph1[1][0] = 1;

    graph2[0][1] = 1;
    graph2[1][0] = 1;

    int result = compareGraphs(graph1, graph2, 2);
    assert(result == 1);
}

void TestcompareGraphs_DifferentGraphs_no4() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };

    graph1[0][1] = 1;
    graph1[1][0] = 1;
    graph2[1][2] = 1;
    graph2[2][1] = 1;

    int result = compareGraphs(graph1, graph2, 3);
    assert(result == 0);
}

void TestgenerateRandomGraph_FullDensity_no5() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 1.0;

    generateRandomGraph(graph, 4, density);

    int connections = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            connections += (i != j) * graph[i][j];
        }
    }

    assert(connections == 12); // Полная плотность (4 узла, 12 рёбер)
}

void TestgenerateRandomGraph_ZeroDensity_no6() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 0.0;

    generateRandomGraph(graph, 4, density);

    int connections = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            connections += graph[i][j];
        }
    }

    assert(connections == 0); // Нулевая плотность
}

void TestgenerateRandomGraph_MidDensity_no7() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 0.5;

    generateRandomGraph(graph, 4, density);

    int connections = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            connections += (i != j) * graph[i][j];
        }
    }

    assert(connections > 0 && connections <= 12); // Средняя плотность
}

void TestwriteAdjacencyList_EmptyGraph_no8() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    writeAdjacencyList("test_list_empty.txt", graph, 0);
    FILE* file = fopen("test_list_empty.txt", "r");
    assert(file != NULL);
    fclose(file);
}

void TestwriteAdjacencyMatrix_EmptyGraph_no9() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    writeAdjacencyMatrix("test_matrix_empty.txt", graph, 0);
    FILE* file = fopen("test_matrix_empty.txt", "r");
    assert(file != NULL);
    fclose(file);
}

void TestgenerateRandomGraph_DensityCheck_no10() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    float density = 0.8;

    generateRandomGraph(graph, 5, density);

    int connections = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            connections += (i != j) * graph[i][j];
        }
    }

    int max_edges = 5 * (5 - 1) / 2;
    int expected_min_edges = max_edges * density;

    assert(connections >= expected_min_edges);
}

void RunAllTests() {
    TestwriteAdjacencyList_ValidGraph_no1();
    TestwriteAdjacencyMatrix_ValidGraph_no2();
    TestcompareGraphs_SameGraphs_no3();
    TestcompareGraphs_DifferentGraphs_no4();
    TestgenerateRandomGraph_FullDensity_no5();
    TestgenerateRandomGraph_ZeroDensity_no6();
    TestgenerateRandomGraph_MidDensity_no7();
    TestwriteAdjacencyList_EmptyGraph_no8();
    TestwriteAdjacencyMatrix_EmptyGraph_no9();
    TestgenerateRandomGraph_DensityCheck_no10();
    printf("Все тесты успешно пройдены!\n");
}

int main() {
    RunAllTests();
    return 0;
}
