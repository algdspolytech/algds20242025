#pragma once
#include <stdio.h>
#define MAX_VERT 100

#ifdef __cplusplus
extern "C" {
#endif

void readAdjList(const char* path, int graph[MAX_VERT][MAX_VERT], int* vertcount);
void readAdjMatrix(const char* path, int graph[MAX_VERT][MAX_VERT], int* vertcount);
int graphEquals(const char* pathlist, const char* pathmatrix);

#ifdef __cplusplus
}
#endif