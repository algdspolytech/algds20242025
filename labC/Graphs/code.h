#define MAX_VERTICES 100
#define _CRT_SECURE_NO_WARNINGS
#ifndef code_h
#define code_h
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct GraphAdjList {
    Node* adjLists[MAX_VERTICES];
    int numVertices;
} GraphAdjList;


typedef struct GraphAdjMatrix {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} GraphAdjMatrix;


GraphAdjList* createGraphAdjList(int vertices);


void addEdgeAdjList(GraphAdjList* graph, int src, int dest);


GraphAdjMatrix* createGraphAdjMatrix(int vertices);


void addEdgeAdjMatrix(GraphAdjMatrix* graph, int src, int dest);


int compareGraphs(GraphAdjList* adjListGraph, GraphAdjMatrix* adjMatrixGraph);


GraphAdjList* readAdjList(const char* filename);


GraphAdjMatrix* readAdjMatrix(const char* filename);
#endif