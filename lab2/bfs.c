#include "bfs.h"
#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int bfs(Graph *graph, int start, int end) {
  int len = 0;
  Stack *queue = init();
  int *distances = malloc(sizeof(int) * graph->vertexes);
  int *used = malloc(sizeof(int) * graph->vertexes);
  for (int i = 0; i < graph->vertexes; i++) {
    distances[i] = (i != start) ? 1000000 : 0;
    used[i] = 0;
  }
  used[start]++;
  push(queue, start);
  if (start != end) {
    while (queue->capacity > 0) {
      int top = pop(queue, 0);
      Vertex *neighbors = graph->adjLists[top];
      while (neighbors) {
        if (!used[neighbors->v]) {
          used[neighbors->v]++;
          push(queue, neighbors->v);
          distances[neighbors->v] = distances[neighbors->v] > distances[top] + 1
                                        ? distances[top] + 1
                                        : distances[neighbors->v];
        }
        neighbors = neighbors->next;
      }
    }
    len = distances[end];
  }
  free(distances);
  free(used);
  destroy(queue);
  return len;
}
