#include <stdio.h>
#include "graph.h"

int main() {
    Graph graph;
    for (int i = 1; i <= 10; i++) {
        createTestGraph(&graph, i);
        printf("Test %d:\n", i);
        int shortest = shortestPath(&graph, 0, graph.numVertices - 1); // Пример, изменить start и end по необходимости
        if (shortest == -1) {
            printf("No path found.\n");
        }
        else {
            printf("Shortest path length: %d\n", shortest);
        }
        printf("\n");
    }

    int result = run_graph_app("input.txt");
    return result;
    return 0;
}

