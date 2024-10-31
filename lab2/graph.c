#include "graph.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void initializeGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->adjList[i][j] = 0;
        }
    }
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjList[src][dest] = 1;
    graph->adjList[dest][src] = 1;
}

bool findShortestPath(Graph* graph, int startVertex, int endVertex, int* path, int* pathLength) {
    int queue[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int front = 0, rear = 0;
    memset(visited, false, sizeof(visited));
    memset(parent, -1, sizeof(parent));

    visited[startVertex] = true;
    queue[rear++] = startVertex;
    while (front < rear) {
        int currentVertex = queue[front++];

        if (currentVertex == endVertex) {

            int tempPath[MAX_VERTICES];
            int count = 0;

            for (int at = endVertex; at != -1; at = parent[at]) {
                tempPath[count++] = at;
            }

            for (int i = 0; i < count; i++) {
                path[i] = tempPath[count - 1 - i];
            }

            *pathLength = count;
            return true;
        }

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjList[currentVertex][i] && !visited[i]) {
                visited[i] = true;
                parent[i] = currentVertex;
                queue[rear++] = i;
            }
        }
    }

    *pathLength = 0;
    return false;
}

void printPath(int* path, int pathLength) {
    for (int i = 0; i < pathLength; ++i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}