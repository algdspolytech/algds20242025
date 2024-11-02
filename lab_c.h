#ifndef LAB_C_H
#define LAB_C_H

#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Graph;

void init_graph(Graph* graph, int num_vertices);
void add_edge(Graph* graph, int src, int dest);
bool dfs(Graph* graph, int visited[], int current, int target);
bool path_exists(Graph* graph, int start, int end);
void load_graph_from_file(Graph* graph, const char* filename);

#endif 
