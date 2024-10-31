#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

Graph* createGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d", &graph->numVertices) != 1 || graph->numVertices <= 0 || graph->numVertices > MAX_VERTICES) {
        perror("Error reading or invalid number of vertices");
        free(graph);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (fscanf(file, "%d", &graph->matrix[i][j]) != 1) {
                perror("Error reading adjacency matrix");
                free(graph);
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);
    return graph;
}

void freeGraph(Graph* graph) {
    free(graph);
}

int shortestPath(const Graph* graph, int start, int end) {
    if (start < 0 || start >= graph->numVertices || end < 0 || end >= graph->numVertices) {
        return -1;
    }

    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES] = { false };

    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = -1;
        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && graph->matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->matrix[u][v];
            }
        }
    }

    return (dist[end] == INT_MAX) ? -1 : dist[end];
}

void createTestGraph(Graph* graph, int testNum) {
    switch (testNum) {
    case 1: // Одна вершина
        graph->numVertices = 1;
        graph->matrix[0][0] = 0;
        break;
    case 2: // Смежные вершины
        graph->numVertices = 2;
        graph->matrix[0][1] = 1;
        graph->matrix[1][0] = 1;
        graph->matrix[0][0] = graph->matrix[1][1] = 0;
        break;
    case 3: // Несмежные, но на одном пути
        graph->numVertices = 3;
        graph->matrix[0][1] = 1;
        graph->matrix[1][2] = 1;
        graph->matrix[0][0] = graph->matrix[1][1] = graph->matrix[2][2] = 0;
        graph->matrix[2][0] = graph->matrix[0][2] = graph->matrix[1][0] = graph->matrix[2][1] = 0;
        break;
    case 4: // Нет пути
        graph->numVertices = 2;
        graph->matrix[0][0] = graph->matrix[1][1] = graph->matrix[0][1] = graph->matrix[1][0] = 0;
        break;
    case 5: //Большое количество вершин
        graph->numVertices = 50;
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                if (i != j && (rand() % 2 == 0)) {
                    graph->matrix[i][j] = rand() % 10 + 1;
                }
                else {
                    graph->matrix[i][j] = 0;
                }
            }
        }
        break;
    case 6: // Пустой граф
        graph->numVertices = 0;
        break;
    case 7: // Стартовая и конечная вершины совпадают
        graph->numVertices = 1;
        graph->matrix[0][0] = 0;
        break;
    case 8: // Граф с циклом
        graph->numVertices = 3;
        graph->matrix[0][1] = 1;
        graph->matrix[1][2] = 1;
        graph->matrix[2][0] = 1;
        graph->matrix[0][0] = graph->matrix[1][1] = graph->matrix[2][2] = 0;
        graph->matrix[0][2] = graph->matrix[1][0] = graph->matrix[2][1] = 0;
        break;
    case 9: // Путь есть, но не кратчайший
        graph->numVertices = 3;
        graph->matrix[0][1] = 5;
        graph->matrix[1][2] = 1;
        graph->matrix[0][2] = 2;
        graph->matrix[0][0] = graph->matrix[1][1] = graph->matrix[2][2] = 0;
        graph->matrix[1][0] = graph->matrix[2][0] = graph->matrix[2][1] = 0;
        break;
    case 10: //  Несколько вариантов кратчайшего пути
        graph->numVertices = 4;
        graph->matrix[0][1] = 1;
        graph->matrix[0][2] = 1;
        graph->matrix[1][3] = 1;
        graph->matrix[2][3] = 1;
        graph->matrix[0][0] = graph->matrix[1][1] = graph->matrix[2][2] = graph->matrix[3][3] = 0;
        graph->matrix[3][0] = graph->matrix[3][1] = graph->matrix[3][2] = graph->matrix[1][0] = graph->matrix[1][2] = graph->matrix[2][0] = graph->matrix[2][1] = 0;
        break;

    default:
        graph->numVertices = 0; //Ошибка
        break;
    }
}