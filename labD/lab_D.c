#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 1000

int graph[MAX_NODES][MAX_NODES];
int adjList[MAX_NODES][MAX_NODES];
int adjListSize[MAX_NODES];
bool visited[MAX_NODES];
int path[MAX_NODES];
int vertexCount;

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void initializeGraph() {
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
        path[i] = -1;
        adjListSize[i] = 0;
        for (int j = 0; j < MAX_NODES; j++) {
            graph[i][j] = 0;
            adjList[i][j] = -1;
        }
    }
}

void insertEdge(int u, int v) {
    graph[u - 1][v - 1] = 1;
    graph[v - 1][u - 1] = 1;

    if (u != v) {
        adjList[u - 1][adjListSize[u - 1]++] = v - 1;
        adjList[v - 1][adjListSize[v - 1]++] = u - 1;
    }
    else {
        adjList[u - 1][adjListSize[u - 1]++] = v - 1;
    }
}

bool depthFirstSearch(int current, int depth) {
    path[depth] = current;
    if (depth == vertexCount - 1) {
        return true;
    }

    visited[current] = true;
    for (int i = 0; i < adjListSize[current]; i++) {
        int next = adjList[current][i];
        if (!visited[next]) {
            if (depthFirstSearch(next, depth + 1)) {
                return true;
            }
        }
    }
    visited[current] = false;
    return false;
}

bool findHamiltonianPath() {
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
        path[i] = -1;
    }
    if (depthFirstSearch(0, 0)) {
        return true;
    }
    return false;
}

void loadGraph(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    fscanf_s(file, "%d", &vertexCount);
    initializeGraph();

    char line[1024];
    fgets(line, sizeof(line), file);

    for (int i = 1; i <= vertexCount; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            char* next_token = NULL;
            char* token = strtok_s(line, " \t\n", &next_token);
            while (token != NULL) {
                int neighbor = atoi(token);
                insertEdge(i, neighbor);
                token = strtok_s(NULL, " \t\n", &next_token);
            }
        }
    }

    fclose(file);

    for (int i = 0; i < vertexCount; i++) {
        qsort(adjList[i], adjListSize[i], sizeof(int), cmpfunc);
    }
}

void saveResult(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        perror("Ошибка открытия файла для записи");
        exit(EXIT_FAILURE);
    }

    if (findHamiltonianPath()) {
        for (int i = 0; i < vertexCount; i++) {
            fprintf(file, "%d ", path[i] + 1);
        }
        fprintf(file, "\n");
    }
    else {
        fprintf(file, "0\n");
    }

    fclose(file);
}
