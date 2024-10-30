#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "lib.h"

void initQueue(Queue *q) 
{
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(Queue *q) 
{
    return q->front == q->rear;
}

void addToQueue(Queue *q, int value) 
{
    q->items[q->rear++] = value;
}

int removeFromQueue(Queue *q) 
{
    if(isEmpty(q))
    {
        return -1;
    }
    return q->items[q->front++];
}

Graph readGraphFromFile(const char *filename) 
{
    Graph g;
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &g.numVertices);
    for (int i = 0; i < g.numVertices; i++) {
        for (int j = 0; j < g.numVertices; j++) {
            fscanf(file, "%d", &g.graph[i][j]);
        }
    }
    fclose(file);
    return g;
}

int bfs(Graph *g, int startVertex, int endVertex) 
{
    if(startVertex == endVertex && startVertex < g->numVertices) return 0;

    bool visited[MAX_VERTICES] = {false};
    int distance[MAX_VERTICES] = {0};
    Queue q;
    initQueue(&q);

    visited[startVertex] = true;
    addToQueue(&q, startVertex);

    while (!isEmpty(&q)) {
        int currentVertex = removeFromQueue(&q);
        
        for (int i = 0; i < g->numVertices; i++) {
            if (g->graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[currentVertex] + 1;
                addToQueue(&q, i);
                
                if (i == endVertex) {
                    return distance[i];
                }
            }
        }
    }
    return INF;
}