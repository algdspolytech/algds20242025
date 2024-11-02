#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void readAdjacencyList(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertex_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл %s\n", filename);
        exit(1);
    }

    int u, v;
    *vertex_count = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }

    while (fscanf(file, "%d %d", &u, &v) == 2) {
        graph[u][v] = 1;
        if (u > *vertex_count) *vertex_count = u;
        if (v > *vertex_count) *vertex_count = v;
    }
    (*vertex_count)++;
    fclose(file);
}

void readAdjacencyMatrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertex_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", vertex_count);
    for (int i = 0; i < *vertex_count; i++) {
        for (int j = 0; j < *vertex_count; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);
}

int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            if (graph1[i][j] != graph2[i][j]) {
                return 0;  // Графы не совпадают
            }
        }
    }
    return 1;  // Графы совпадают
}
