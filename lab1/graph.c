#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

#define MAX_VERTICES 100

//граф списком смежности
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


//граф матрицей смежности
typedef struct GraphAdjMatrix {
  int V;
  int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphAdjMatrix;


//новый узел списка смежности
AdjListNode* newAdjListNode(int dest) {
  AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
  newNode->dest = dest;
  newNode->next = NULL;
  return newNode;
}

//создание графа списком смежности
GraphAdjList* createGraphAdjList(int V) {
  GraphAdjList* graph = (GraphAdjList*)malloc(sizeof(GraphAdjList));
  graph->V = V;
  graph->array = (AdjList*)malloc(V * sizeof(AdjList));
  for (int i = 0; i < V; ++i) {
    graph->array[i].head = NULL;
  }
  return graph;
}

//добавление ребра в граф через список смежности
void addEdgeAdjList(GraphAdjList* graph, int src, int dest) {
  AdjListNode* newNode = newAdjListNode(dest);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  //неориентированный
  newNode = newAdjListNode(src);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;
}


//создание графа матрицей смежности
GraphAdjMatrix* createGraphAdjMatrix(int V) {
  GraphAdjMatrix* graph = (GraphAdjMatrix*)malloc(sizeof(GraphAdjMatrix));
  graph->V = V;
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      graph->adjMatrix[i][j] = 0;
    }
  }
  return graph;
}

//добавление ребра в граф через матрицу смежности
void addEdgeAdjMatrix(GraphAdjMatrix* graph, int src, int dest) {
  graph->adjMatrix[src][dest] = 1;

  // Для неориентированного графа:
  graph->adjMatrix[dest][src] = 1;
}

// чтение графа из файла списком смежности
GraphAdjList* readGraphAdjListFromFile(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Ошибка открытия файла списка смежности");
    return NULL;
  }

  int V, E;
  fscanf(file, "%d %d", &V, &E); //количество вершин и ребер

  GraphAdjList* graph = createGraphAdjList(V);

  for (int i = 0; i < E; ++i) {
    int src, dest;
    fscanf(file, "%d %d", &src, &dest); //ребро
    addEdgeAdjList(graph, src, dest);
  }

  fclose(file);
  return graph;
}

//чтение графа из файла матрицей смежности
GraphAdjMatrix* readGraphAdjMatrixFromFile(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Ошибка открытия файла матрицы смежности");
    return NULL;
  }

  int V, E;
  fscanf(file, "%d %d", &V, &E); //количество вершин и ребер

  GraphAdjMatrix* graph = createGraphAdjMatrix(V);

  for (int i = 0; i < E; ++i) {
    int src, dest;
    fscanf(file, "%d %d", &src, &dest); //ребро
    addEdgeAdjMatrix(graph, src, dest);
  }

  fclose(file);
  return graph;
}

//сравнение двух графов
bool areGraphsEqual(GraphAdjList* graphAdjList, GraphAdjMatrix* graphAdjMatrix) {
    if (graphAdjList->V != graphAdjMatrix->V) {
        return false;
    }

    int V = graphAdjList->V;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            bool found_in_list = false;
            AdjListNode* current = graphAdjList->array[i].head;
            while (current != NULL) {
                if (current->dest == j) {
                    found_in_list = true;
                    break;
                }
                current = current->next;
            }
            if ((graphAdjMatrix->adjMatrix[i][j] == 1 && !found_in_list) ||
                (graphAdjMatrix->adjMatrix[i][j] == 0 && found_in_list)) {
                return false;
            }
        }
    }

    return true;
}

//освобождение памяти (список смежности)
void freeGraphAdjList(GraphAdjList* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            AdjListNode* current = graph->array[i].head;
            while (current) {
                AdjListNode* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->array);
        free(graph);
    }
}

//освобождение памяти (матрица смежности)
void freeGraphAdjMatrix(GraphAdjMatrix* graph) {
    if (graph) {
        free(graph);
    }
}
