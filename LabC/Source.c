#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>  
#include "Source.h"
#pragma warning (disable : 4996)

void writeAdjacencyList(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    FILE* file = fopen(filename, "w+");
    for (int i = 0; i < vertices; i++) {
        fprintf(file, "%d: ", i);
        for (int j = 0; j < vertices; j++) {
            if (graph[i][j]) {
                fprintf(file, "%d ", j);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void writeAdjacencyMatrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    FILE* file = fopen(filename, "w+");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fprintf(file, "%d ", graph[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph1[i][j] != graph2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void generateRandomGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, float density) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j) {
                graph[i][j] = (rand() / (float)RAND_MAX) < density ? 1 : 0;
            }
            else {
                graph[i][j] = 0;
            }
        }
    }
}