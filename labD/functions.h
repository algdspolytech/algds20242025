#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H


typedef struct {
    int v;
    int d;
} node;

typedef struct {
    int V;
    int s;
    int t;
    int K;
    int** matrix;
    int* visited;
    int* path;
    int len;
} graph;


int** create_matrix(int n);
graph* create_graph(char* name);

int find_path(graph* graph);

void print_matrix(int** matrix, int n);
void write_res(graph* g, char* name);

#endif