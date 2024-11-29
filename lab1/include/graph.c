#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
    int vertexNumber;
    size_t countAdjVertices;
    int* vertices;
    struct Node* next;
} Node;

typedef struct AdjacencyList{
    Node* head;
} AdjacencyList;

typedef struct Graph{
    size_t countVertices;
    AdjacencyList* adjList; //pointer to list (not array!)
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
    node->countAdjVertices=countVertices;
    node->vertices=(int*)malloc(countVertices*sizeof(int));
    if(!node->vertices)
        return NULL;

    for( size_t i=0;i<countVertices;++i)
        node->vertices[i]=vertices[i];

    node->next=NULL;
    return node;
}

void freeNode(Node* node) {
    /**
     * Frees the memory allocated for a node in the adjacency list.
     *
     * @param node A pointer to the Node to be freed. If the pointer is NULL, the function does nothing.
     */
    if (node) {
        free(node->vertices);
        free(node);
    }
}

bool addNode(AdjacencyList* list,Node* node){
    /**
     * Adds a node to the end of the adjacency list.
     *
     * This function appends the specified node to the end of the given adjacency list.
     * If the list is empty, the node becomes the head of the list.
     *
     * @param list A pointer to the AdjacencyList where the node will be added.
     *             If the pointer is NULL, the function returns false.
     * @param node A pointer to the Node.
     *             If the pointer is NULL, the function returns false.
     *
     * @return true if the node was successfully added to the list;
     *         false if the list or node pointer is NULL.
     */
    if(!list || !node)
           return false;

    if(!list->head){
        list->head=node;
        return true;
    }

    Node* tmp = list->head;
    while(tmp->next)
        tmp=tmp->next;
    tmp->next=node;
    return true;
}

int** readAdjacencyMatrix(const char* filename, size_t* size) {
    /**
     * Reads an adjacency matrix from a file.
     *
     * @param filename A pointer to a string containing the name of the file.
     * @param size A pointer to a size_t variable where the size of the matrix.
     *
     * @return A pointer to a dynamically allocated 2D array representing the
     *         adjacency matrix, or NULL if the file could not be opened or
     *         if memory allocation fails.
     */
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
    /**
     * Frees the memory allocated for a matrix.
     *
     * @param matrix A pointer to the matrix to be freed. If the pointer is NULL, the function does nothing.
     * @param size  A size of matrix.
     */
    if(matrix){
        for (size_t i = 0; i < size; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

void printNode(const Node* node) {
    /**
     * Print a node.
     *
     * @param node A pointer to the node to be printed. If the pointer is NULL, the function does nothing.
     */
    if (node) {
        printf("Vertex %d: ", node->vertexNumber);
        for (size_t i = 0; i < node->countAdjVertices; ++i)
            printf("%d ", node->vertices[i]);
        printf("\n");
    }
}

Graph* initGraph(const char* filename){
    /**
     * Initializes a graph from an adjacency matrix stored in a file.
     *
     * @param filename A pointer to a string containing the name of the file.
     *
     * @return A pointer to a dynamically allocated Graph structure representing
     *         the graph, or NULL if the file could not be opened, if memory
     *         allocation fails, or if the adjacency matrix is invalid.
     */
    size_t size;
    int** adjacencyMatrix = readAdjacencyMatrix(filename,&size);
    if(!adjacencyMatrix)
        return NULL;

    Graph* graph=(Graph*)malloc(sizeof(Graph));
    graph->countVertices=size;
    graph->adjList=(AdjacencyList*)malloc(sizeof(AdjacencyList));
    if (!graph->adjList) {
            freeMatrix(adjacencyMatrix, size);
            free(graph);
            return NULL;
    }
    graph->adjList->head=NULL;

    for (size_t i = 0; i < size; ++i) {
        int* adjacentVertices = (int*)malloc(size * sizeof(int));
        size_t countVert = 0;

        for (size_t j = 0; j < size; ++j) {
            if (adjacencyMatrix[i][j] != 0)
                adjacentVertices[countVert++] = (int)j+1;
        }

        Node* newNode = initNode((int)i+1, countVert, adjacentVertices);
        if (newNode)
            addNode(graph->adjList, newNode);
        free(adjacentVertices);
    }

    freeMatrix(adjacencyMatrix, size);
    return graph;
}

void printAdjacencyList(const AdjacencyList* list){
    /**
     * Print a list.
     *
     * @param list A pointer to the list to be printed. If the pointer is NULL, the function does nothing.
     */
    if(list){
        Node* tmp=list->head;
        while(tmp){
            printNode(tmp);
            tmp=tmp->next;
        }
    }
}

void freeList(AdjacencyList* list) {
    /**
     * Frees the memory allocated for a list.
     *
     * @param list A pointer to the list to be freed. If the pointer is NULL, the function does nothing.
     */
    if (list) {
        Node* tmp = list->head;
        Node* nextNode;

        while (tmp) {
            nextNode = tmp->next;
            freeNode(tmp);
            tmp = nextNode;
        }
        list->head = NULL;
    }
}

void freeGraph(Graph* graph){
    /**
     * Frees the memory allocated for a graph.
     *
     * @param graph A pointer to the graph to be freed. If the pointer is NULL, the function does nothing.
     */
    freeList(graph->adjList);
    free(graph->adjList);
}
