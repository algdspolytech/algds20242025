#include <stdio.h>
#include "graph.h"

int main() {
    Graph graph;
    int numVertices = 0;

    FILE* inputFile;
    errno_t err = fopen_s(&inputFile, "adjacency_list.txt", "r");
    if (err != 0) {
        perror("Failed to open file");
        return 1;
    }

    fscanf_s(inputFile, "%d", &numVertices);
    initializeGraph(&graph, numVertices);

    int vertex1, vertex2;
    while (fscanf_s(inputFile, "%d %d", &vertex1, &vertex2) != EOF) {
        addEdge(&graph, vertex1, vertex2);
    }
    fclose(inputFile);

    int startVertex, endVertex;

    printf("Enter start vertex: ");
    scanf_s("%d", &startVertex);
    printf("Enter end vertex: ");
    scanf_s("%d", &endVertex);

    int path[MAX_VERTICES];
    int pathLength;

    if (findShortestPath(&graph, startVertex, endVertex, path, &pathLength)) {
        printf("Shortest path from %d to %d: ", startVertex, endVertex);
        printPath(path, pathLength);
    }
    else {
        printf("No path found from %d to %d\n", startVertex, endVertex);
    }

    return 0;
}