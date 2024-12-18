#pragma once
#ifndef GRAPH_SORT_H
#define GRAPH_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Макс. количество слов и символов в слове
#define MAX_WORDS 100
#define MAX_LEN 50

// Структура для хранения графа
typedef struct {
    char words[MAX_WORDS][MAX_LEN];
    int adjMatrix[MAX_WORDS][MAX_WORDS];
    int wordCount;
} Graph;

// Функции
void initializeGraph(Graph* graph);
int findWordIndex(Graph* graph, const char* word);
void addEdge(Graph* graph, const char* word1, const char* word2);
bool topologicalSort(Graph* graph, char output[MAX_WORDS][MAX_LEN], int* outputSize);
void readInputFile(const char* filename, Graph* graph);
void writeOutputFile(const char* filename, char output[MAX_WORDS][MAX_LEN], int outputSize, bool hasError);

#endif // GRAPH_SORT_H