#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
    int vertexNumber;
    int* vertices;
    struct Node* next;
} Node;

typedef struct AdjacencyList{
    Node* head;
} AdjacencyList;

typedef struct Graph{
    size_t countVertices;
    AdjacencyList* adjList;
} Graph;

Node* initNode(const int vertexNum, const size_t countVertices, const int* vertices){
    /**
     * Initializes a new node for an adjacency list.
     *
     * @param vertexNum The number of the vertex associated with the node.
     * @param countVertices The number of adjacent vertices to be stored in the node.
     * @param vertices A pointer to an array of integers representing the adjacent vertices.
     *
     * @return A pointer to the newly created Node, or NULL if memory allocation fails
     *         or if the input parameters are invalid.
     */
    if (!countVertices || !vertices)
        return NULL;
    Node* node=(Node*)malloc(sizeof(Node));
    if(!node)
        return NULL;

    node->vertexNumber=vertexNum;
    node->vertices=(int*)malloc(countVertices*sizeof(int));
    if(!node->vertices)
        return NULL;

    for( size_t i=0;i<countVertices;++i)
        node->vertices[i]=vertices[i];

    node->next=NULL;
    return node;
}

void freeNode(Node* node) {
    if (node) {
        free(node->vertices);
        free(node);
    }
}

bool addNode(AdjacencyList* list,Node* node){
    if(!list || !node)
           return false;

    if(!list->head){
        list->head=node;
        return true;
    }

    Node* tmp = list->head;
    while(tmp)
        tmp=tmp->next;
    tmp->next=node;
    return true;
}

int** readAdjacencyMatrix(const char* filename, size_t* size) {
    FILE* file = fopen(filename, "r");
    if (!file)
        return NULL;

    fscanf(file, "%zu", size);

    int** matrix = (int**)malloc((*size) * sizeof(int*));
    for (size_t i = 0; i < *size; ++i)
        matrix[i] = (int*)malloc((*size) * sizeof(int));

    for (size_t i = 0; i < *size; ++i) {
        for (size_t j = 0; j < *size; ++j)
            fscanf(file, "%d", &matrix[i][j]);
    }

    fclose(file);
    return matrix;
}

void freeMatrix(int** matrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
