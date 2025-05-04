#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Vertex *make_vertex(int _v) {
  Vertex *new_vertex = malloc(sizeof(Vertex));
  new_vertex->next = NULL;
  new_vertex->v = _v;
  return new_vertex;
}

Graph *make_graph(int num) {
  Graph *new_graph = malloc(sizeof(Graph));
  new_graph->vertexes = num;
  new_graph->adjLists = malloc(sizeof(Vertex *) * num);
  for (int i = 0; i < num; i++) {
    new_graph->adjLists[i] = NULL;
  }
  return new_graph;
}

void add_vertex(Graph *graph, int src, int dest) {
  Vertex *new_node_1 = make_vertex(dest);
  new_node_1->next = graph->adjLists[src];
  graph->adjLists[src] = new_node_1;

  Vertex *new_node_2 = make_vertex(src);
  new_node_2->next = graph->adjLists[dest];
  graph->adjLists[dest] = new_node_2;
}

void destroy_graph(Graph *graph) {
  for (int i = 0; i < graph->vertexes; i++) {
    Vertex *temp = graph->adjLists[i];
    while (temp) {
      Vertex *buff = temp;
      temp = temp->next;
      free(buff);
    }
  }
  free(graph->adjLists);
  free(graph);
}
