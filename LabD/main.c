#include "labD.h"

int main() {
    const char* input_file_path = "input.txt";
    const char* output_file_path = "result.txt";

    int total_vertices, start, target, min_length;
    Vertex map[MAX_VERTICES + 1];
    int visited_nodes[MAX_VERTICES + 1] = { 0 };
    int path_tracker[MAX_VERTICES + 1] = { 0 };
    int traverse_path[MAX_VERTICES + 1];
    int path_length = 0;

    load_graph(input_file_path, map, &total_vertices, &start, &target, &min_length);

    path_length = depth_first_search(map, visited_nodes, path_tracker, traverse_path, start, target, 0, min_length, 0);

    save_result(output_file_path, traverse_path, path_length);

    for (int j = 1; j <= total_vertices; j++)
        free(map[j].connections);

    return 0;
}
