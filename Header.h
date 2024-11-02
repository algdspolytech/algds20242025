#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int vertex;
    struct Node* next;
} node;

typedef struct Graph{
    int numVertex;
    node** adjList;
    bool* visited;
} graph;

node* initNode(int vertex);
graph* initGraph(int vertex);
void addEdge(graph* gr, int cur, int end);
void DFS(graph* gr, int start, int end, int* found);
int pathExist(graph* gr, int start, int end);
graph* ReadFromFile(const char* filename);
graph* Free_graph(graph*);