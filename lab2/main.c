#include "head.h"
#define MAX_VERTICES 10

int main() {

    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

    if (readMatrixFromFile("graph.txt", matrix, &numVertices) != 0) {
        return 1;
    }

    Graph* graph = createGraph(matrix, numVertices);

    printGraph(graph);
    freeGraph(graph);

    return 0;
}
