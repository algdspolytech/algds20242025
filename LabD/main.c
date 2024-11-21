#include "funcs.h"

int main() {
  const char *input_file = "test.txt";
  const char *output_file = "output.txt";

  int V, s, t, K;
  Node graph[MAX_VERTICES + 1];
  int visited[MAX_VERTICES + 1] = {0};
  int current_path_visited[MAX_VERTICES + 1] = {0};
  int path[MAX_VERTICES + 1];
  int path_length = 0;

  read_graph(input_file, graph, &V, &s, &t, &K);

  path_length = dfs(graph, visited, current_path_visited, path, s, t, 0, K, 0);

  write_output(output_file, path, path_length);

  for (int i = 1; i <= V; i++)
    free(graph[i].neighbors);

  return 0;
}