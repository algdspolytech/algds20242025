// graph.c
#include <stdio.h>
#include <stdlib.h>
#include "lab_c.h"
#pragma warning(disable : 4996)

void init_graph(Graph* graph, int num_vertices) {
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            graph->adjacency_matrix[i][j] = 0;
        }
    }
}

void add_edge(Graph* graph, int src, int dest) {
    graph->adjacency_matrix[src][dest] = 1;
    graph->adjacency_matrix[dest][src] = 1; 
}

bool dfs(Graph* graph, int visited[], int current, int target) {
    if (current == target) {
        return true;
    }

    visited[current] = 1; 

    for (int i = 0; i < graph->num_vertices; i++) {
        if (graph->adjacency_matrix[current][i] == 1 && !visited[i]) {
            if (dfs(graph, visited, i, target)) {
                return true;
            }
        }
    }

    return false;
}

bool path_exists(Graph* graph, int start, int end) {
    if (start < 0 || start >= graph->num_vertices || end < 0 || end >= graph->num_vertices) {
        return false; 
    }

    int visited[MAX_VERTICES] = { 0 };
    return dfs(graph, visited, start, end);
}

void load_graph_from_file(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &graph->num_vertices);
    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = 0; j < graph->num_vertices; j++) {
            fscanf(file, "%d", &graph->adjacency_matrix[i][j]);
        }
    }

    fclose(file);
}
