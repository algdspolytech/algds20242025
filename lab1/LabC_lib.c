#include "LabC_lib.h"
#pragma warning(disable : 4996) 


Node* create_node(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode)
        return NULL;
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph)
        return NULL;
    if (vertices < 0) {
        printf("Вершин не может быть отрицательное количество");
        return NULL;
    }
    graph->numVertices = vertices;

    graph->list = (AdjList*)malloc(vertices * sizeof(AdjList));

    for (int i = 0; i < vertices; i++) {
        graph->list[i].head = NULL;
    }

    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* newNode = create_node(dest);
    if (!newNode)
        printf("Не удалось создать граф.\n");
    newNode->next = graph->list[src].head;
    graph->list[src].head = newNode;
}

int** read_adjacency_matrix(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл для чтения.\n");
        return NULL;
    }

    fscanf(file, "%d", size);

    int** matrix = (int**)malloc((*size) * sizeof(int*));
    for (int i = 0; i < *size; i++) {
        matrix[i] = (int*)malloc((*size) * sizeof(int));
    }

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

Graph* build_adjacency_list(int** matrix, int size) {
    Graph* graph = create_graph(size);
    if (!graph)
        return NULL;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                add_edge(graph, i, j);
            }
        }
    }

    return graph;
}

void write_adjacency_list(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        fprintf(file, "%d: ", i);
        Node* temp = graph->list[i].head;
        while (temp) {
            fprintf(file, "%d ", temp->vertex);
            temp = temp->next;
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->list[i].head;
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->list);
    free(graph);
}

void free_adjacency_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
