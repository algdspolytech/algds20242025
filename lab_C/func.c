#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

bool read_adjacency_list(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertices_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return false;
    }

    fscanf(file, "%d", vertices_count);
    for (int i = 0; i < *vertices_count; i++) {
        int num_edges;
        fscanf(file, "%d", &num_edges);
        for (int j = 0; j < num_edges; j++) {
            int vertex;
            fscanf(file, "%d", &vertex);
            graph[i][vertex] = 1;
        }
    }

    fclose(file);
    return true;
}

bool read_adjacency_matrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertices_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return false;
    }

    fscanf(file, "%d", vertices_count);
    for (int i = 0; i < *vertices_count; i++) {
        for (int j = 0; j < *vertices_count; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
    return true;
}

bool compare_graphs(const char* adjacency_list_file, const char* adjacency_matrix_file) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = {0};
    int graph2[MAX_VERTICES][MAX_VERTICES] = {0};
    int vertices_count1, vertices_count2;

    if (!read_adjacency_list(adjacency_list_file, graph1, &vertices_count1) ||
        !read_adjacency_matrix(adjacency_matrix_file, graph2, &vertices_count2)) {
        return false;
    }

    if (vertices_count1 != vertices_count2) {
        return false;
    }

    for (int i = 0; i < vertices_count1; i++) {
        for (int j = 0; j < vertices_count1; j++) {
            if (graph1[i][j] != graph2[i][j]) {
                return false;
            }
        }
    }

    return true;
}
