#include "funcs.h"

void create_graph(Node *graph, int *V) {
  for (int i = 1; i <= *V; i++) {
    graph[i].neighbors = (int *)malloc(MAX_NEIGHBORS * sizeof(int));
    graph[i].count = 0;
  }
}

void add_edge(Node *graph, int u, int v) {
  graph[u].neighbors[graph[u].count++] = v;
  if (u != v)
    graph[v].neighbors[graph[v].count++] = u;
}

int dfs(Node *graph, int *visited, int *current_path_visited, int *path,
        int node, int t, int depth, int K, int path_length) {
  visited[node] = 1;
  current_path_visited[node] = 1;
  path[path_length] = node;

  if (node == t && depth >= K) {
    current_path_visited[node] = 0;
    return path_length + 1;
  }

  for (int i = 0; i < graph[node].count; i++) {
    int neighbor = graph[node].neighbors[i];
    if (!visited[neighbor] && !current_path_visited[neighbor]) {
      int new_path_length = dfs(graph, visited, current_path_visited, path,
                                neighbor, t, depth + 1, K, path_length + 1);
      if (new_path_length > 0) {
        current_path_visited[node] = 0;
        return new_path_length;
      }
    }
  }

  visited[node] = 0;
  current_path_visited[node] = 0;
  return 0;
}

void parse_line(char *line, int *src, int *dest, Node *graph) {
  int parsed = sscanf_s(line, "%d %d", src, dest);
  if (parsed == 2)
    add_edge(graph, *src, *dest);
}

void read_graph(const char *filename, Node *graph, int *V, int *s, int *t,
                int *K) {
  FILE *file = fopen(filename, "r");
  char line[10];
  int src, dest;

  fscanf_s(file, "%d %d %d %d", V, s, t, K);
  create_graph(graph, V);
  while (fgets(line, sizeof(line), file))
    parse_line(line, &src, &dest, graph);

  fclose(file);
}

void write_output(const char *filename, int *path, int path_length) {
  FILE *file = fopen(filename, "w");

  if (path_length > 0) {
    for (int i = 0; i < path_length; i++)
      fprintf(file, "%d ", path[i]);
    fprintf(file, "\n");
  } else
    fprintf(file, "0\n");

  fclose(file);
}