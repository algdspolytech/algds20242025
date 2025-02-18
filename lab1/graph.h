#pragma once 

#include <stdbool.h>

#define MAX_VERTICES 100 

typedef struct AdjListNode {
  int dest;
  struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
  AdjListNode* head;
} AdjList;

typedef struct GraphAdjList {
  int V;
  AdjList* array;
} GraphAdjList;

typedef struct GraphAdjMatrix {
  int V;
  int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphAdjMatrix;

//Функции для работы с графом (список смежности)
AdjListNode* newAdjListNode(int dest);
GraphAdjList* createGraphAdjList(int V);
void addEdgeAdjList(GraphAdjList* graph, int src, int dest);
GraphAdjList* readGraphAdjListFromFile(const char* filename);
void freeGraphAdjList(GraphAdjList* graph);

//Функции для работы с графом (матрица смежности)
GraphAdjMatrix* createGraphAdjMatrix(int V);
void addEdgeAdjMatrix(GraphAdjMatrix* graph, int src, int dest);
GraphAdjMatrix* readGraphAdjMatrixFromFile(const char* filename);
void freeGraphAdjMatrix(GraphAdjMatrix* graph);

//Функция для сравнения графов
bool areGraphsEqual(GraphAdjList* graphAdjList, GraphAdjMatrix* graphAdjMatrix);