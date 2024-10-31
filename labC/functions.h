#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX 50

typedef struct Node {
    int v;
    struct Node* next;
} Node;

typedef struct Graph {
    int size;
    Node* list[MAX];
} Graph;

Node* create_node(int v);
Graph* init_graph(int size);
void add_edge(Graph* g, int start, int finish);

void find_path(Graph* g, int startVertex, int endVertex);

Graph* read_graph(char* name);
void print_graph(Graph* g);

#endif



