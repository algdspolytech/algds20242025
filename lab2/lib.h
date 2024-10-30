#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 9999

typedef struct 
{
    int graph[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

typedef struct 
{
    int items[MAX_VERTICES];
    int front, rear;
} Queue;

void initQueue(Queue *q);

bool isEmpty(Queue *q);

void addToQueue(Queue *q, int value);

int removeFromQueue(Queue *q);

Graph readGraphFromFile(const char *filename);

int bfs(Graph *g, int startVertex, int endVertex);

#endif