#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

typedef struct Graph {
  int n_vertices;
  Node *adj_lists[MAX_VERTICES];
  int visited[MAX_VERTICES];
} Graph;

#ifdef __cplusplus

extern "C" {
#endif

Node *create_node(int v);
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest);
int DFS(Graph *graph, int start, int target);
Graph *read_file(char *filename);
void parse_line(char *line, int *src, int *dest, int edges[MAX_VERTICES][2],
                int *max_vertex, int *edge_count);

#ifdef __cplusplus
}
#endif