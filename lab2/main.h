#pragma once
#ifndef MAIN_H
#define MAIN_H

typedef struct {
    int** matrix;
    int size;
} Graph;

void initMatrix(Graph* graph);
void freeMatrix(Graph* graph);
void copyRow(int* row, int* input, int size);
void printMatrix(Graph* graph, FILE* outputFile);
void readList(Graph* graph, FILE* file);

#endif
