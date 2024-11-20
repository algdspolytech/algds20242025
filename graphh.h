#ifndef GRAPH_H
#define GRAPH_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEXES 10

typedef struct {
    int items[MAX_VERTEXES];
    int front, last;
} Queue;

void initQueue(Queue* q);
int isEmpty(Queue* q);
void add_queue(Queue* q, int value);
int out_queue(Queue* q);

int bfs(int graph[MAX_VERTEXES][MAX_VERTEXES], int n, int start, int end);
void dfs(int graph[MAX_VERTEXES][MAX_VERTEXES], int n, int current, int end, int visited[MAX_VERTEXES], int depth, int* minDepth, int path[MAX_VERTEXES], int tempPath[MAX_VERTEXES], int tempIndex);

#endif
