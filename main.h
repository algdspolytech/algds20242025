// main.h

#ifndef MAIN_H
#define MAIN_H
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Структура узла списка смежности
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Структура графа
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Прототипы функций
int** read_adjacency_matrix(const char* filename, int* size);
void free_adjacency_matrix(int** matrix, int size);

Graph* build_adjacency_list(int** matrix, int size);
void write_adjacency_list(const char* filename, Graph* graph);
void free_graph(Graph* graph);

Node* create_node(int vertex); // Добавьте это, если используете create_node в тестах

#endif // MAIN_H
