#include <stdlib.h>
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
