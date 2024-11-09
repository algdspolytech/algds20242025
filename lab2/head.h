#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjacencyList[MAX_VERTICES];
} Graph;

int readMatrixFromFile(const char* filename,
    int matrix[MAX_VERTICES][MAX_VERTICES],
    int* numVertices) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error openning file \n");
        return 1;
    }

    fscanf(file, "%d", numVertices);

    if (*numVertices > MAX_VERTICES) {
        fprintf(stderr, "Incorrect size \n");
        fclose(file);
        return 3;
    }

    for (int i = 0; i < *numVertices; i++) {
        for (int j = 0; j < *numVertices; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) == 1) {
                if (matrix[i][j] != 1 && matrix[i][j] != 0) {
                    fprintf(stderr, "Invalid data \n");
                    fclose(file);
                    return 4;
                }
            }
            else {
                fprintf(stderr, "Invalid data 2\n");
                fclose(file);
                return 5;
            }
        }
    }

    fclose(file);
    return 0;
}
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

int IsAdjacency(int matrix[MAX_VERTICES][MAX_VERTICES], Graph* graph, int i, int j) {
    if (matrix[i][j] == 1) {
        Node* newNode = createNode(j);
        newNode->next = graph->adjacencyList[i];
        graph->adjacencyList[i] = newNode;
        return 1;
    }
    else {
        return 0;
    }
}

Graph* createGraph(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            IsAdjacency(matrix, graph, i, j);
        }
    }

    return graph;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjacencyList[i];
        if (temp == NULL) {
            printf("No adjacencies for point %d\n", i);

        }
        else {
            printf("Point %d:", i);
            while (temp) {
                printf(" -> %d", temp->vertex);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjacencyList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph);
}