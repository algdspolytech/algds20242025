#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lab_D.h"

void TestinitializeGraph_EmptyGraph_no1() {
    initializeGraph();
    bool isValid = true;
    for (int i = 0; i < MAX_NODES; i++) {
        if (visited[i] || path[i] != -1 || adjListSize[i] != 0) {
            isValid = false;
            break;
        }
        for (int j = 0; j < MAX_NODES; j++) {
            if (graph[i][j] != 0 || adjList[i][j] != -1) {
                isValid = false;
                break;
            }
        }
    }
    printf("TestinitializeGraph_EmptyGraph_no1 = %i\n", isValid);
}

void TestinsertEdge_AddEdge_no2() {
    initializeGraph();
    insertEdge(1, 2);
    bool isValid = graph[0][1] == 1 && graph[1][0] == 1 && adjListSize[0] == 1 && adjListSize[1] == 1;
    printf("TestinsertEdge_AddEdge_no2 = %i\n", isValid);
}

void TestinsertEdge_SelfLoop_no3() {
    initializeGraph();
    insertEdge(1, 1);
    bool isValid = graph[0][0] == 1 && adjListSize[0] == 1 && adjList[0][0] == 0;
    printf("TestinsertEdge_SelfLoop_no3 = %i\n", isValid);
}

void Testdfs_ValidPath_no4() {
    initializeGraph();
    vertexCount = 3;
    insertEdge(1, 2);
    insertEdge(2, 3);
    bool isValid = depthFirstSearch(0, 0);
    printf("Testdfs_ValidPath_no4 = %i\n", isValid);
}

void Testdfs_NoPath_no5() {
    initializeGraph();
    vertexCount = 3;
    insertEdge(1, 2);
    bool isValid = !depthFirstSearch(0, 0);
    printf("Testdfs_NoPath_no5 = %i\n", isValid);
}

void TestfindHamiltonianPath_ValidPath_no6() {
    initializeGraph();
    vertexCount = 3;
    insertEdge(1, 2);
    insertEdge(2, 3);
    bool isValid = findHamiltonianPath();
    printf("TestfindHamiltonianPath_ValidPath_no6 = %i\n", isValid);
}

void TestfindHamiltonianPath_NoPath_no7() {
    initializeGraph();
    vertexCount = 3;
    insertEdge(1, 2);
    bool isValid = !findHamiltonianPath();
    printf("TestfindHamiltonianPath_NoPath_no7 = %i\n", isValid);
}

void TestloadGraph_ValidGraph_no8() {
    const char* filename = "testgraph.txt";
    FILE* file = fopen(filename, "w");
    fprintf(file, "3\n1 2\n2 3\n");
    fclose(file);

    loadGraph(filename);
    bool isValid = graph[0][1] == 1 && graph[1][2] == 1 && vertexCount == 3;
    printf("TestloadGraph_ValidGraph_no8 = %i\n", isValid);
}

void TestloadGraph_EmptyGraph_no9() {
    const char* filename = "emptygraph.txt";
    FILE* file = fopen(filename, "w");
    fprintf(file, "0\n");
    fclose(file);

    loadGraph(filename);
    bool isValid = vertexCount == 0;
    printf("TestloadGraph_EmptyGraph_no9 = %i\n", isValid);
}

void TestsaveResult_ValidPath_no10() {
    initializeGraph();
    const char* filename = "output.txt";
    vertexCount = 3;
    insertEdge(1, 2);
    insertEdge(2, 3);

    saveResult(filename);
    FILE* file = fopen(filename, "r");
    char result[100];
    fgets(result, sizeof(result), file);
    fclose(file);

    bool isValid = strcmp(result, "1 2 3 \n") == 0;
    printf("TestsaveResult_ValidPath_no10 = %i\n", isValid);
}

void TestinsertEdge_MultipleEdges_no11() {
    initializeGraph();
    insertEdge(1, 2);
    insertEdge(2, 3);
    insertEdge(3, 4);
    bool isValid = graph[0][1] == 1 && graph[1][2] == 1 && graph[2][3] == 1;
    printf("TestinsertEdge_MultipleEdges_no11 = %i\n", isValid);
}

void TestfindHamiltonianPath_DisconnectedGraph_no12() {
    initializeGraph();
    vertexCount = 4;
    insertEdge(1, 2);
    insertEdge(3, 4);
    bool isValid = !findHamiltonianPath();
    printf("TestfindHamiltonianPath_DisconnectedGraph_no12 = %i\n", isValid);
}

void TestLoadAndSaveGraph_EquivalentMain_no13() {
    const char* inputFile = "test_input_main.txt";
    const char* outputFile = "test_output_main.txt";

    FILE* file = fopen(inputFile, "w");
    fprintf(file, "4\n1 2 3\n2 3 4\n3 4\n4\n");
    fclose(file);

    loadGraph(inputFile);

    saveResult(outputFile);

    file = fopen(outputFile, "r");
    char result[100];
    fgets(result, sizeof(result), file);
    fclose(file);

    bool isValid = strstr(result, "1 2 3 4") != NULL || strstr(result, "0") == NULL;
    printf("TestLoadAndSaveGraph_EquivalentMain_no13 = %i\n", isValid);
}

void runAllTests() {
    TestinitializeGraph_EmptyGraph_no1();
    TestinsertEdge_AddEdge_no2();
    TestinsertEdge_SelfLoop_no3();
    Testdfs_ValidPath_no4();
    Testdfs_NoPath_no5();
    TestfindHamiltonianPath_ValidPath_no6();
    TestfindHamiltonianPath_NoPath_no7();
    TestloadGraph_ValidGraph_no8();
    TestloadGraph_EmptyGraph_no9();
    TestsaveResult_ValidPath_no10();
    TestinsertEdge_MultipleEdges_no11();
    TestfindHamiltonianPath_DisconnectedGraph_no12();
    TestLoadAndSaveGraph_EquivalentMain_no13();
}

int main() {
    runAllTests();
    return 0;
}
