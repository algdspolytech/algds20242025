#include <stdio.h>
#include <stdlib.h>
#include "LibC.h"

#define MAX_VERTICES 50

Graph* createGraph(int num_vertices) {
  Graph* graph = malloc(sizeof(Graph));
  graph->num_vertices = num_vertices;
  for (int i = 0; i < num_vertices; i++) {
    graph->vertices[i].degree = 0;
  }
  return graph;
}

void addEdge(Graph* graph, int src, int dest) {
  graph->vertices[src].adj[graph->vertices[src].degree++] = dest;
  graph->vertices[dest].adj[graph->vertices[dest].degree++] = src;
}

Graph* readGraphFile(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: can't open the file\n");
    return NULL;
  }

  int num_vertices;
  fscanf(fp, "%d", &num_vertices);

  Graph* graph = createGraph(num_vertices);

  int dest;
  int src;
  while (fscanf(fp, "%d %d", &src, &dest) != EOF) {
    addEdge(graph, src, dest);
  }

  fclose(fp);
  return graph;
}

int* findPath(Graph* graph, int start, int end) {
  int visited[MAX_VERTICES] = {0};
  int distance[MAX_VERTICES] = {0};
  int previous[MAX_VERTICES] = {-1};
  int queue[MAX_VERTICES];
  int r = 0;
  int front = 0;

  queue[r++] = start;
  visited[start] = 1;

  while (front != r) {
    int current = queue[front++];

    if (current == end) {
      int* path = malloc(sizeof(int) * MAX_VERTICES);
      int path_index = 0;
      int node = end;

      while (node != -1) {
        path[path_index++] = node;
        node = previous[node];
      }

      return path;
    }

    for (int i = 0; i < graph->vertices[current].degree; i++) {
      int neighbor = graph->vertices[current].adj[i];
      if (!visited[neighbor]) {
        visited[neighbor] = 1;
        distance[neighbor] = distance[current] + 1;
        previous[neighbor] = current;
        queue[r++] = neighbor;
      }
    }
  }

  return NULL;
}
