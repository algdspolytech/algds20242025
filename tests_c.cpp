#include "C:\Users\User\Documents\projects C++\MY_LIBRARY\Windows-Machine-Learning-master\Samples\WinMLSamplesGallery\WinMLSamplesGalleryNative\External\pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\User\Documents\projects C++\MY_LIBRARY\gtests\googletest\include\gtest\gtest.h"
#include "LIB_C.h"

void TestwriteAdjacencyList_ValidGraph_no1() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    graph[0][1] = 1;
    graph[1][2] = 1;


    writeAdjacencyList("test_list_c.txt", graph, 3);

    printf("TestwriteAdjacencyList_ValidGraph_no1 = 1\n"); 
}


void TestwriteAdjacencyMatrix_ValidGraph_no2() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    graph[0][1] = 1;
    graph[1][0] = 1;


    writeAdjacencyMatrix("test_matrix_c.txt", graph, 2);

    printf("TestwriteAdjacencyMatrix_ValidGraph_no1 = 1\n"); 
}


void TestcompareGraphs_SameGraphs_no3() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };

    graph1[0][1] = 1;
    graph1[1][0] = 1;

    graph2[0][1] = 1;
    graph2[1][0] = 1;


    int result = compareGraphs(graph1, graph2, 2);
    printf("TestcompareGraphs_SameGraphs_no1 = %i\n", result == 1 ? 1 : 0);
}

void TestcompareGraphs_DifferentGraphs_no4() {
    int graph1[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int graph2[MAX_VERTICES][MAX_VERTICES] = { 0 };

    graph1[0][1] = 1;
    graph1[1][0] = 1;
    graph2[1][2] = 1;
    graph2[2][1] = 1;


    int result = compareGraphs(graph1, graph2, 3);
    printf("TestcompareGraphs_DifferentGraphs_no1 = %i\n", result == 0 ? 1 : 0);
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

    printf("TestgenerateRandomGraph_FullDensity_no5 = %i\n", connections == 12 ? 1 : 0);
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

    printf("TestgenerateRandomGraph_ZeroDensity_no6 = %i\n", connections == 0 ? 1 : 0);
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

    printf("TestgenerateRandomGraph_MidDensity_no7 = %i\n", connections > 0 ? 1 : 0);
}

void TestwriteAdjacencyList_EmptyGraph_no8() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    writeAdjacencyList("test_list_empty.txt", graph, 0);
    printf("TestwriteAdjacencyList_EmptyGraph_no1 = 1\n");

}
void TestwriteAdjacencyMatrix_EmptyGraph_no9() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    writeAdjacencyMatrix("test_matrix_empty.txt", graph, 0);
    printf("TestwriteAdjacencyMatrix_EmptyGraph_no1 = 1\n"); 
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

    printf("TestgenerateRandomGraph_DensityCheck_no10 = %i\n", connections >= expected_min_edges ? 1 : 0);
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
}

int main() {
    RunAllTests();
    return 0;
}