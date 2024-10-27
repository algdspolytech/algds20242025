#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

typedef struct {
    int numVertices;
    AdjList* list;
} Graph;

Node* create_node(int vertex);

Graph* create_graph(int vertices);

void add_edge(Graph* graph, int src, int dest);

int** read_adjacency_matrix(const char* filename, int* size);

Graph* build_adjacency_list(int** matrix, int size);

void write_adjacency_list(const char* filename, Graph* graph);

void free_graph(Graph* graph);

void free_adjacency_matrix(int** matrix, int size);