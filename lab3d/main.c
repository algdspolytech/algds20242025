#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include "graph.h"

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        perror("Error opening the file");
        return 1;
    }

    int V, s, t, K;
    fscanf(input, "%d %d %d %d", &V, &s, &t, &K);

    Graph graph;
    initGraph(&graph, V);

    for (int i = 0; i < V; i++) {
        int neighbor;
        while (fscanf(input, "%d", &neighbor) == 1) {
            if (neighbor == 0) break; // Для случая окончания строки
            addEdge(&graph, i, neighbor - 1);
        }
    }

    fclose(input);

    int path[MAX_VERTICES], pathLength = 0;
    if (dfs(&graph, s - 1, t - 1, K, 0, path, &pathLength)) {
        for (int i = 0; i < pathLength; i++) {
            fprintf(output, "%d ", path[i]);
        }
    }
    else {
        fprintf(output, "0");
    }

    fclose(output);

    // Освобождение памяти
    for (int i = 0; i < V; i++) {
        free(graph.adj[i]);
    }

    return 0;
}