#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>

// Функция DFS
bool dfs(const Graph* graph, int start_vertex, int end_vertex, bool* visited) {
    if (start_vertex == end_vertex) return true;
    visited[start_vertex] = true;

    for (int i = 0; i < graph->vertices[start_vertex].neighbor_count; ++i) {
        int neighbor = graph->vertices[start_vertex].neighbors[i];
        if (!visited[neighbor]) {
            if (dfs(graph, neighbor, end_vertex, visited)) return true;
        }
    }
    return false;
}

// Функция создания графа из файла
Graph* create_graph_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    int vertex_count;
    if (fscanf(file, "%d", &vertex_count) != 1) {
        perror("Error reading vertex count");
        fclose(file);
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertex_count = vertex_count;
    graph->vertices = (Vertex*)malloc(vertex_count * sizeof(Vertex));


    for (int i = 0; i < vertex_count; ++i) {
        graph->vertices[i].vertex = i;
        int neighbor_count;
        fscanf(file, "%d", &neighbor_count);
        graph->vertices[i].neighbor_count = neighbor_count;
        graph->vertices[i].neighbors = (int*)malloc(neighbor_count * sizeof(int));
        for (int j = 0; j < neighbor_count; ++j) {
            fscanf(file, "%d", &graph->vertices[i].neighbors[j]);
        }
    }
    fclose(file);
    return graph;
}

//Функция освобождения памяти, занимаемой графом
void free_graph(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; ++i) {
        free(graph->vertices[i].neighbors);
    }
    free(graph->vertices);
    free(graph);
}
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    char filename[100];
    int start_vertex, end_vertex;

    printf("Enter the filename: ");
    scanf("%s", filename);

    printf("Enter the start vertex: ");
    scanf("%d", &start_vertex);

    printf("Enter the end vertex: ");
    scanf("%d", &end_vertex);

    Graph* graph = create_graph_from_file(filename);
    if (graph == NULL) return 1;

    if (start_vertex >= graph->vertex_count || end_vertex >= graph->vertex_count || start_vertex < 0 || end_vertex < 0) {
        printf("Invalid vertex indices.\n");
        free_graph(graph);
        return 1;
    }

    bool* visited = (bool*)calloc(graph->vertex_count, sizeof(bool));
    bool path_exists = dfs(graph, start_vertex, end_vertex, visited);
    free(visited);

    if (path_exists) {
        printf("Path exists between vertices %d and %d.\n", start_vertex, end_vertex);
    }
    else {
        printf("No path exists between vertices %d and %d.\n", start_vertex, end_vertex);
    }

    free_graph(graph);
    return 0;
}