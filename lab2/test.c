#include <assert.h>
#include <stdio.h>
#include "graph.h"

void runAllTests() {
    Graph graph;
    int path[MAX_VERTICES];
    int pathLength;

    initializeGraph(&graph, 5);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    if (!findShortestPath(&graph, 0, 4, path, &pathLength)) {
        printf("Test 1 failed: No path found\n");
    }
    assert(pathLength == 5);

    initializeGraph(&graph, 5);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 2, 3);
    if (findShortestPath(&graph, 0, 4, path, &pathLength)) {
        printf("Test 2 failed: Path should not exist\n");
    }

    initializeGraph(&graph, 5);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 0);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    if (!findShortestPath(&graph, 0, 4, path, &pathLength)) {
        printf("Test 3 failed: No path found\n");
    }
    assert(pathLength >= 4 && pathLength <= 5);

    initializeGraph(&graph, 1);
    if (!findShortestPath(&graph, 0, 0, path, &pathLength)) {
        printf("Test 4 failed: No path found\n");
    }
    assert(pathLength == 1);

    initializeGraph(&graph, 2);
    if (findShortestPath(&graph, 0, 1, path, &pathLength)) {
        printf("Test 5 failed: Path should not exist\n");
    }

    initializeGraph(&graph, 4);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 0, 3);
    if (!findShortestPath(&graph, 1, 3, path, &pathLength)) {
        printf("Test 6 failed: No path found\n");
    }
    assert(pathLength == 3);

    initializeGraph(&graph, 4);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 0, 3);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 3);
    if (!findShortestPath(&graph, 2, 3, path, &pathLength)) {
        printf("Test 7 failed: No path found\n");
    }
    assert(pathLength == 2);

    initializeGraph(&graph, 100);
    if (findShortestPath(&graph, 0, 99, path, &pathLength)) {
        printf("Test 8 failed: Path should not exist\n");
    }

    initializeGraph(&graph, 100);
    for (int i = 0; i < 99; i++) {
        addEdge(&graph, i, i + 1);
    }
    if (!findShortestPath(&graph, 0, 99, path, &pathLength)) {
        printf("Test 9 failed: No path found\n");
    }
    assert(pathLength == 100);

    initializeGraph(&graph, 5);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    if (!findShortestPath(&graph, 2, 2, path, &pathLength)) {
        printf("Test 10 failed: No path found\n");
    }
    assert(pathLength == 1);

    printf("All test cases passed!\n");
}

//int main() {
//    runAllTests();
//    return 0;
//}