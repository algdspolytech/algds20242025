#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

typedef struct {
    int* data;
    int front;
    int rear;
    int capacity;
} Queue;
void initQueue(Queue* q, int capacity);
int isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
void freeQueue(Queue* q);
int greedy_coloring(int** adjacency_matrix, int num_vertices, int k, int* colors);
void read_input(FILE* input, int* n, int* k, int*** adjacency_matrix);
void write_output(FILE* output, int num_vertices, int* colors);
int check_coloring(int num_vertices, int* colors);
void free_matrix(int** matrix, int n);