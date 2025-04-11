#include "labC.h"
#include <stdio.h>
#include <stdlib.h>

int** read_graph(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    fscanf_s(file, "%d", size);
    int** graph = malloc(*size * sizeof(int*));
    for (int i = 0; i < *size; ++i) {
        graph[i] = malloc(*size * sizeof(int));
        for (int j = 0; j < *size; ++j) {
            fscanf_s(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);
    return graph;
}

int find_shortest_path(int** graph, int size, int start, int end) {
    if (start == end) return 0;

    int* visited = (int*)malloc(size * sizeof(int));
    int* dist = (int*)malloc(size * sizeof(int));

    if (!visited || !dist) {
        if (visited) free(visited);
        if (dist) free(dist);
        return -1; 
    }

    for (int i = 0; i < size; i++) {
        visited[i] = 0;
        dist[i] = -1;
    }

    visited[start] = 1;
    dist[start] = 0;

    for (int step = 0; step < size; step++) {
        for (int u = 0; u < size; u++) {
            if (visited[u] && dist[u] >= 0) {
                for (int v = 0; v < size; v++) {
                    if (graph[u][v] && !visited[v]) {
                        dist[v] = dist[u] + 1;
                        visited[v] = 1;
                        if (v == end) {
                            int result = dist[v];
                            free(visited);
                            free(dist);
                            return result;
                        }
                    }
                }
            }
        }
    }

    free(visited);
    free(dist);
    return -1;
}

void free_graph(int** graph, int size) {
    for (int i = 0; i < size; ++i) {
        free(graph[i]);
    }
    free(graph);
}
