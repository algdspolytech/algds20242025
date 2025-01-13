#include "labD.h"

void initialize_graph(Vertex* map, int* total_vertices) {
    for (int j = 1; j <= *total_vertices; j++) {
        map[j].connections = (int*)malloc(MAX_CONNECTIONS * sizeof(int));
        map[j].degree = 0;
    }
}

void insert_edge(Vertex* map, int start, int end) {
    map[start].connections[map[start].degree++] = end;
    if (start != end)
        map[end].connections[map[end].degree++] = start;
}

int depth_first_search(Vertex* map, int* visited_nodes, int* path_tracker, int* traverse_path,
    int current_vertex, int target, int current_depth, int min_depth, int length) {
    visited_nodes[current_vertex] = 1;
    path_tracker[current_vertex] = 1;
    traverse_path[length] = current_vertex;

    if (current_vertex == target && current_depth >= min_depth) {
        path_tracker[current_vertex] = 0;
        return length + 1;
    }

    for (int k = 0; k < map[current_vertex].degree; k++) {
        int adjacent = map[current_vertex].connections[k];
        if (!visited_nodes[adjacent] && !path_tracker[adjacent]) {
            int new_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path,
                adjacent, target, current_depth + 1, min_depth, length + 1);
            if (new_length > 0) {
                path_tracker[current_vertex] = 0;
                return new_length;
            }
        }
    }

    visited_nodes[current_vertex] = 0;
    path_tracker[current_vertex] = 0;
    return 0;
}

void extract_edge(char* buffer, int* from, int* to, Vertex* map) {
    int parsed_count = sscanf(buffer, "%d %d", from, to);
    if (parsed_count == 2)
        insert_edge(map, *from, *to);
}

void load_graph(const char* file_path, Vertex* map, int* total_vertices, int* start, int* target,
    int* min_length) {
    FILE* file_pointer = fopen(file_path, "r");
    char buffer[20];
    int from, to;

    fscanf(file_pointer, "%d %d %d %d", total_vertices, start, target, min_length);
    initialize_graph(map, total_vertices);
    while (fgets(buffer, sizeof(buffer), file_pointer))
        extract_edge(buffer, &from, &to, map);

    fclose(file_pointer);
}

void save_result(const char* file_path, int* traverse_path, int length) {
    FILE* file_pointer = fopen(file_path, "w");

    if (length > 0) {
        for (int j = 0; j < length; j++)
            fprintf(file_pointer, "%d ", traverse_path[j]);
        fprintf(file_pointer, "\n");
    }
    else
        fprintf(file_pointer, "0
            ");

            fclose(file_pointer);
}
