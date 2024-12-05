#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000 


typedef struct {
    int n;               
    int k;               
    int adj[MAX_VERTICES][MAX_VERTICES]; 
} Graph;

bool readGraph(const char* filename, Graph* graph);
bool isCovered(Graph* graph, bool included[MAX_VERTICES]);
bool findVertexCover(Graph* graph, bool included[MAX_VERTICES], int idx, int includedCount);
void writeResult(const char* filename, bool included[MAX_VERTICES], int n);


#endif