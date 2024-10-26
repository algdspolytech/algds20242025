#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include "graph.h"
#include "tests.h"


void runTest(const char* testName, int result, const char* expected, const char* actual) {
    if (result) {
        printf("%s: Test passed\n", testName);
    }
    else {
        printf("%s: Test failed\nExpected: %s\nActual: %s\n", testName, expected, actual);
    }
}

void comparePaths(const char* testName, int* expectedPath, int expectedLength, int* actualPath, int actualLength) {
    int isEqual = (expectedLength == actualLength);
    if (isEqual) {
        for (int i = 0; i < expectedLength; i++) {
            if (expectedPath[i] != actualPath[i]) {
                isEqual = 0;
                break;
            }
        }
    }

    if (isEqual) {
        printf("%s: Test passed\n", testName);
    }
    else {
        printf("%s: Test failed\nExpected: ", testName);
        for (int i = 0; i < expectedLength; i++) {
            printf("%d ", expectedPath[i] + 1);
        }
        printf("\nActual: ");
        for (int i = 0; i < actualLength; i++) {
            printf("%d ", actualPath[i] + 1);
        }
        printf("\n");
    }
}

void readGraphFromFile(const char* filename, int graph[MAX_VERTEXES][MAX_VERTEXES], int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);
}

void testPath_singleVertex_1(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int expectedPath[] = { 0 };
    int actualPath[MAX_VERTEXES];
    int actualLength = bfs(graph, n, 0, 0, actualPath);
    comparePaths("testPath_singleVertex_1 (BFS)", expectedPath, 1, actualPath, actualLength);

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, 0, 0, visited, 0, &minDepth, path, tempPath, 0);
    comparePaths("testPath_singleVertex_1 (DFS)", expectedPath, 1, path, minDepth + 1);
}

void testPath_severalVertexes_2(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int expectedPath[] = { 1, 6, 7, 8 };
    int actualPath[MAX_VERTEXES];
    int actualLength = bfs(graph, n, 1, 8, actualPath);
    comparePaths("testPath_severalVertexes_2 (BFS)", expectedPath, 4, actualPath, actualLength);

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, 1, 8, visited, 0, &minDepth, path, tempPath, 0);
    comparePaths("testPath_severalVertexes_2 (DFS)", expectedPath, 4, path, minDepth + 1);
}

void testPath_severalVertexes_3(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int expectedPath[] = { 8, 2, 1 };
    int actualPath[MAX_VERTEXES];
    int actualLength = bfs(graph, n, 8, 1, actualPath);
    comparePaths("testPath_severalVertexes_3 (BFS)", expectedPath, 3, actualPath, actualLength);

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, 8, 1, visited, 0, &minDepth, path, tempPath, 0);
    comparePaths("testPath_severalVertexes_3 (DFS)", expectedPath, 3, path, minDepth + 1);
}

void testNoPath_4(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int expectedPathLength = -1;
    int actualPath[MAX_VERTEXES];
    int actualLengthBFS = bfs(graph, n, 0, 1, actualPath);

    if (actualLengthBFS == expectedPathLength) {
        printf("testNoPath_4 (BFS): Test passed (no path found)\n");
    }
    else {
        printf("testNoPath_4 (BFS): Test failed (expected no path)\n");
    }

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, 0, 1, visited, 0, &minDepth, path, tempPath, 0);

    if (minDepth == INT_MAX) {
        printf("testNoPath_4 (DFS): Test passed (no path found)\n");
    }
    else {
        printf("testNoPath_4 (DFS): Test failed (expected no path)\n");
    }
}

void testPath_single_edge_5(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int expectedPathLength = 1;
    int actualPath[MAX_VERTEXES];

    int actualLengthBFS = bfs(graph, n, 0, 1, actualPath) - 1;
    if (actualLengthBFS == expectedPathLength) {
        printf("testPath_single_edge_5 (BFS): Test passed (path found)\n");
    }
    else {
        printf("testPath_single_edge_5 (BFS): Test failed (expected path length: %d, actual: %d)\n", expectedPathLength, actualLengthBFS);
    }

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, 0, 1, visited, 0, &minDepth, path, tempPath, 0);

    if (minDepth == expectedPathLength) {
        printf("testPath_single_edge_5 (DFS): Test passed (path found)\n");
    }
    else {
        printf("testPath_single_edge_5 (DFS): Test failed (expected path length: %d, actual: %d)\n", expectedPathLength, minDepth);
    }
}

void testPath_Non_existentVertex_6(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int start = 0;
    int end = 6;

    int actualPath[MAX_VERTEXES];
    int actualLengthBFS = bfs(graph, n, start, end, actualPath);
    if (actualLengthBFS == -1) {
        printf("testPath_Non_existentVertex_6 (BFS): Test passed (no path found)\n");
    }
    else {
        printf("testPath_Non_existentVertex_6 (BFS): Test failed (expected no path found)\n");
    }

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, start, end, visited, 0, &minDepth, path, tempPath, 0);
    if (minDepth == INT_MAX) {
        printf("testPath_Non_existentVertex_6 (DFS): Test passed (no path found)\n");
    }
    else {
        printf("testPath_Non_existentVertex_6 (DFS): Test failed (expected no path found)\n");
    }
}

void test_QueueInitialization_7() {
    Queue q;
    initQueue(&q);
    if (isEmpty(&q)) {
        printf("test_QueueInitialization_7: Test passed (queue is empty)\n");
    }
    else {
        printf("test_QueueInitialization_7: Test failed (queue is not empty)\n");
    }
}

void test_Queue_add_remove_8() {
    Queue q;
    initQueue(&q);
    add_queue(&q, 1);
    if (!isEmpty(&q)) {
        printf("test_Queue_add_remove_8: Test passed (item added)\n");
    }
    else {
        printf("test_Queue_add_remove_8: Test failed (item not added)\n");
    }

    int removedValue = out_queue(&q);
    if (removedValue == 1 && isEmpty(&q)) {
        printf("test_Queue_add_remove_8: Test passed (item removed correctly)\n");
    }
    else {
        printf("test_Queue_add_remove_8: Test failed (item not removed correctly)\n");
    }
}

void test_Queue_multiple_addRemove_9() {
    Queue q;
    initQueue(&q);
    add_queue(&q, 1);
    add_queue(&q, 2);
    int removedValue1 = out_queue(&q);
    int removedValue2 = out_queue(&q);

    if (removedValue1 == 1 && removedValue2 == 2 && isEmpty(&q)) {
        printf("test_Queue_multiple_addRemove_9: Test passed (multiple items added and removed correctly)\n");
    }
    else {
        printf("test_Queue_multiple_addRemove_9: Test failed (error in adding/removing multiple items)\n");
    }
}

void test_Multiple_paths_10(int graph[MAX_VERTEXES][MAX_VERTEXES], int n) {
    int expectedPath[] = { 1, 0, 4 };
    int actualPath[MAX_VERTEXES];
    int actualLength = bfs(graph, n, 1, 4, actualPath);
    comparePaths("test_Multiple_paths_10 (BFS)", expectedPath, 3, actualPath, actualLength);

    int visited[MAX_VERTEXES] = { 0 };
    int minDepth = INT_MAX;
    int path[MAX_VERTEXES];
    int tempPath[MAX_VERTEXES];

    dfs(graph, n, 1, 4, visited, 0, &minDepth, path, tempPath, 0);
    comparePaths("test_Multiple_paths_10 (DFS)", expectedPath, 3, path, minDepth + 1);
}
