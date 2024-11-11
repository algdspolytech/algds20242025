#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_WORDS 10
#define MAX_LENGTH 5


typedef struct {
    char words[MAX_WORDS][MAX_LENGTH];
    int adjMatrix[MAX_WORDS][MAX_WORDS]; // матрица упорядоченных пар
    int indegree[MAX_WORDS]; // сколько ребер входит в вершину
    int wordCount;
} Graph;


FILE* input_open(const char* filename);
FILE* output_open(const char* filenmae);
int findWordIndex(Graph* graph, const char* word);
int addWord(Graph* graph, const char* word);
void addEdge(Graph* graph, const char* word1, const char* word2);
bool topologicalSort(Graph* graph, char result[MAX_WORDS][MAX_LENGTH]);

#endif
