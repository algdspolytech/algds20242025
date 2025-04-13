#define MAX 127
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


typedef struct Graph_l {
    Node* list[MAX];
    int num_v;
} Graph_l;


typedef struct Graph_m {
    int matrix[MAX][MAX];
    int num_v;
} Graph_m;


Graph_l* createGraph_l(int vertices);


void add_l(Graph_l* graph, int src, int dest);


Graph_l* read_l(const char* filename);


Graph_m* createGraph_m(int vertices);


void add_m(Graph_m* graph, int src, int dest);


Graph_m* read_m(const char* filename);


bool compareGraphs(Graph_l* adjListGraph, Graph_m* adjMatrixGraph);
#endif