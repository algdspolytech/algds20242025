#pragma once

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define MAX_CONNECTIONS 100

typedef struct {
    int* connections;
    int degree;
} Vertex;

#ifdef __cplusplus
extern "C" {
#endif
    void initialize_graph(Vertex* map, int* total_vertices);
    void insert_edge(Vertex* map, int start, int end);
    int depth_first_search(Vertex* map, int* visited_nodes, int* path_tracker, int* traverse_path,
        int current_vertex, int target, int current_depth, int min_depth, int length);
    void extract_edge(char* buffer, int* from, int* to, Vertex* map);
    void load_graph(const char* file_path, Vertex* map, int* total_vertices, int* start, int* target,
        int* min_length);
    void save_result(const char* file_path, int* traverse_path, int length);
#ifdef __cplusplus
}
#endif
