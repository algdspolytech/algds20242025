#pragma once

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define MAX_NEIGHBORS 100

typedef struct {
  int *neighbors;
  int count;
} Node;

#ifdef __cplusplus

extern "C" {
#endif
void create_graph(Node *graph, int *V);
void add_edge(Node *graph, int u, int v);
int dfs(Node *graph, int *visited, int *current_path_visited, int *path,
        int node, int t, int depth, int K, int path_length);
void parse_line(char *line, int *src, int *dest, Node *graph);
void read_graph(const char *filename, Node *graph, int *V, int *s, int *t,
                int *K);
void write_output(const char *filename, int *path, int path_length);
#ifdef __cplusplus
}
#endif