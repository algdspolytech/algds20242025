#define _CRT_SECURE_NO_WARNINGS


#include "funcs.h"


bool readGraph(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть файл");
        return false;
    }

    fscanf(file, "%d %d", &graph->n, &graph->k);

    for (int i = 0; i < graph->n; i++) {
        for (int j = 0; j < graph->n; j++) {
            graph->adj[i][j] = 0;
        }
    }

    int u, v;
    while (fscanf(file, "%d %d", &u, &v) == 2) {
        graph->adj[u - 1][v - 1] = 1; 
        graph->adj[v - 1][u - 1] = 1; 
    }

    fclose(file);
    return true;
}

bool isCovered(Graph* graph, bool included[MAX_VERTICES]) {
    for (int u = 0; u < graph->n; u++) {
        for (int v = 0; v < graph->n; v++) {
            if (graph->adj[u][v] && !(included[u] || included[v])) {
                return false; // Найдено ребро без покрытия
            }
        }
    }
    return true;
}

bool findVertexCover(Graph* graph, bool included[MAX_VERTICES], int idx, int includedCount) {
    if (includedCount > graph->k) return false;

    if (idx == graph->n) {
        return isCovered(graph, included);
    }

    if (findVertexCover(graph, included, idx + 1, includedCount)) {
        return true;
    }

    included[idx] = true;
    if (findVertexCover(graph, included, idx + 1, includedCount + 1)) {
        return true;
    }
    included[idx] = false;

    return false;
}

void writeResult(const char* filename, bool included[MAX_VERTICES], int n) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Не удалось открыть файл для записи");
        return;
    }

    bool hasSolution = false;
    for (int i = 0; i < n; i++) {
        if (included[i]) {
            fprintf(file, "%d ", i + 1);
            hasSolution = true;
        }
    }

    if (!hasSolution) {
        fprintf(file, "0");
    }

    fclose(file);
}