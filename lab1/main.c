#include <stdio.h>
#include <stdlib.h>
#include "labC.h"

#define MAX_VERTICES 50

Graph* createGraph(int num_vertices) {
  Graph* graph = malloc(sizeof(Graph));
  graph->num_vertices = num_vertices;
  for (int i = 0; i < num_vertices; i++) {
    graph->vertices[i].degree = 0;
  }
  return graph;
}

void addEdge(Graph* graph, int source, int destination) {
  graph->vertices[source].adj[graph->vertices[source].degree++] = destination;
  graph->vertices[destination].adj[graph->vertices[destination].degree++] = source;
}

Graph* readGraphFromFile(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Ошибка открытия файла.\n");
    return NULL;
  }

  int num_vertices;
  fscanf(fp, "%d", &num_vertices);

  Graph* graph = createGraph(num_vertices);

  int source;
  int destination;
  while (fscanf(fp, "%d %d", &source, &destination) != EOF) {
    addEdge(graph, source, destination);
  }

  fclose(fp);
  return graph;
}

int* findShortestPath(Graph* graph, int start, int end) {
  int visited[MAX_VERTICES] = {0};
  int distance[MAX_VERTICES] = {0};
  int previous[MAX_VERTICES] = {-1};
  int queue[MAX_VERTICES];
  int front = 0;
  int rear = 0;

  queue[rear++] = start;
  visited[start] = 1;

  while (front != rear) {
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
        queue[rear++] = neighbor;
      }
    }
  }

  return NULL;
}
