#pragma once

#define MAX_VERTICES 100


void printGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices);

void readAdjMatrix(char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertices);

void readAdjList(char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertices);

int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertices);