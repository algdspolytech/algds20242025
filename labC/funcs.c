#include "funcs.h"

Node *create_node(int v) {

  Node *newNode = malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;

  return newNode;
}

Graph *create_graph(int vertices) {

  Graph *graph = malloc(sizeof(Graph));
  graph->n_vertices = vertices;

  for (int i = 0; i < vertices; i++) {
    graph->adj_lists[i] = NULL;
    graph->visited[i] = 0;
  }

  return graph;
}

void add_edge(Graph *graph, int src, int dest) {

  Node *New = create_node(dest);
  New->next = graph->adj_lists[src];
  graph->adj_lists[src] = New;

  New = create_node(src);
  New->next = graph->adj_lists[dest];
  graph->adj_lists[dest] = New;
}

int DFS(Graph *graph, int start, int target) {
  graph->visited[start] = 1;

  if (start == target) {
    return 1;
  }

  Node *adj_list = graph->adj_lists[start];
  Node *p = adj_list;

  while (p) {
    int connected = p->vertex;
    if (!graph->visited[connected]) {
      if (DFS(graph, connected, target)) {
        return 1;
      }
    }
    p = p->next;
  }
  return 0;
}

void parse_line(char *line, int *src, int *dest, int edges[MAX_VERTICES][2],
                int *max_vertex, int *edge_count) {

  int parsed = sscanf_s(line, "%d %d", src, dest);

  if (parsed == 2) {

    edges[*edge_count][0] = *src;
    edges[*edge_count][1] = *dest;
    (*edge_count)++;

    if (*src > *max_vertex)
      *max_vertex = *src;
    if (*dest > *max_vertex)
      *max_vertex = *dest;
  }
}

Graph *read_file(char *filename) {

  int src, dest;
  int max_vertex = 0;
  char line[10];

  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("No file!\n");
    return NULL;
  }

  int edges[MAX_VERTICES][2];
  int edge_count = 0;
  while (fgets(line, sizeof(line), file)) {
    parse_line(line, &src, &dest, edges, &max_vertex, &edge_count);
  }

  int n_vertices = max_vertex + 1;
  Graph *graph = create_graph(n_vertices);

  for (int i = 0; i < edge_count - 1; i++) {
    add_edge(graph, edges[i][0], edges[i][1]);
  }

  fclose(file);

  return graph;
}