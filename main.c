#include "main.h"
#include <locale.h>

// Функция для чтения матрицы смежности из файла
int** read_adjacency_matrix(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Считываем размер матрицы
    fscanf(file, "%d", size);

    // Выделяем память под матрицу
    int** matrix = (int**)malloc((*size) * sizeof(int*));
    for (int i = 0; i < *size; i++) {
        matrix[i] = (int*)malloc((*size) * sizeof(int));
    }

    // Считываем матрицу из файла
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

// Функция для освобождения памяти матрицы смежности
void free_adjacency_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для создания нового узла списка смежности
Node* create_node(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Функция для построения списка смежности из матрицы смежности
Graph* build_adjacency_list(int** matrix, int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = size;

    // Инициализируем массив списков смежности
    graph->adjLists = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        graph->adjLists[i] = NULL;
    }

    // Заполняем списки смежности
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--) {
            if (matrix[i][j] != 0) {
                Node* newNode = create_node(j);
                newNode->next = graph->adjLists[i];
                graph->adjLists[i] = newNode;
            }
        }
    }

    return graph;
}

// Функция для записи списка смежности в файл
void write_adjacency_list(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->numVertices; i++) {
        fprintf(file, "Вершина %d:", i);
        Node* temp = graph->adjLists[i];
        while (temp) {
            fprintf(file, " %d", temp->vertex);
            temp = temp->next;
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Функция для освобождения памяти графа
void free_graph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int size;
    int** matrix = read_adjacency_matrix("input.txt", &size);
    Graph* this_graph = build_adjacency_list(matrix, size);
    write_adjacency_list("output.txt", this_graph);

    free_adjacency_matrix(matrix, size);
    free_graph(this_graph);
    return 0;
}

