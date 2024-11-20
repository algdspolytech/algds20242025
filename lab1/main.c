#include <stdio.h>
#include <stdlib.h>

#include "labD.h"

void clearGraph() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
        path[i] = -1;
    }
}

void resetGraph() {
    n = 0;
    clearGraph();
}

void addGraphEdge(const int u, const int v) {
    adj[u - 1][v - 1] = 1;
    adj[v - 1][u - 1] = 1;
}

int isHamiltonianPath(int position) {
    if (position == n) {
        return 1;
    }

    for (int v = 0; v < n; v++) {
        if (!visited[v]) {
            int canAdd = position == 0 || adj[path[position - 1]][v];
            if (canAdd) {
                path[position] = v;
                visited[v] = 1;
                if (isHamiltonianPath(position + 1)) {
                    return 1;
                }
                visited[v] = 0;
                path[position] = -1;
            }
        }
    }
    return 0;
}

int findHamiltonianPath() {
    for (int startVertex = 0; startVertex < n; startVertex++) {
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
            path[i] = -1;
        }
        path[0] = startVertex;
        visited[startVertex] = 1;
        if (isHamiltonianPath(1)) {
            return 1;
        }
    }
    return 0;
}

void readGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка при открытии файла");
        exit(1);
    }

    fscanf(file, "%d", &n);
    clearGraph();

    for (int i = 1; i <= n; i++) {
        int vertex;
        while (fscanf(file, "%d", &vertex) == 1) {
            if (vertex > 0 && vertex <= n) {
                addGraphEdge(i, vertex);
            }
        }
    }

    fclose(file);
}


void writeResult(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка при открытии файла для записи");
        exit(1);
    }

    if (findHamiltonianPath()) {
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d ", path[i] + 1);
        }
        fprintf(file, "\n");
    }
    else {
        fprintf(file, "0\n");
    }

    fclose(file);
}
