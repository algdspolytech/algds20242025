#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  
#include <time.h>

#define MAX_VERTICES 10

void writeAdjacencyList(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int vertices);

void writeAdjacencyMatrix(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int vertices);

int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertices);

void generateRandomGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, float density);