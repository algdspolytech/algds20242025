#include "funcs.h"

int main() {

  Graph *graph = read_file("test.txt");

  if (DFS(graph, 1, 2))
    printf("True");
  else
    printf("False");

  return 0;
}