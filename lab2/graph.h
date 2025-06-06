#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex {
  int v;
  struct Vertex *next;
} Vertex;

typedef struct Graph {
  int vertexes;
  Vertex **adjLists;
} Graph;

Vertex *make_vertex(int v);
Graph *make_graph(int num);
void add_vertex(Graph *graph, int src, int dest);
void destroy_graph(Graph *graph);
void print_graph(Graph *graph);

#endif