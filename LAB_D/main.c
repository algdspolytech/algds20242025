#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "Header.h"

void setqueue(Queue* q, int capacity) {
    q->data = (int*)malloc(capacity * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == q->capacity - 1) {
        printf("Queue is full\n");
    }
    else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->data[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int value;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        value = -1;
    }
    else {
        value = q->data[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return value;
}

void freeQueue(Queue* q) {
    free(q->data);
}

int mainfunct(int** adjacency_matrix, int num_vertices, int k, int* colors) {
    for (int i = 0; i < num_vertices; i++) {
        colors[i] = -1;
    }
    colors[0] = 0;

    Queue bfs_queue;
    setqueue(&bfs_queue, num_vertices);
    enqueue(&bfs_queue, 0);

    while (!isEmpty(&bfs_queue)) {
        int current_vertex = dequeue(&bfs_queue);

        for (int neighbor = 0; neighbor < num_vertices; neighbor++) {
            if (adjacency_matrix[current_vertex][neighbor] == 1 && colors[neighbor] == -1) {
                enqueue(&bfs_queue, neighbor);

                int* used_colors = (int*)calloc(k, sizeof(int));
                if (used_colors == NULL) {
                    printf("Memory allocation failed\n");
                    exit(1);
                }

                for (int adj = 0; adj < num_vertices; adj++) {
                    if (adjacency_matrix[neighbor][adj] == 1 && colors[adj] != -1) {
                        used_colors[colors[adj]] = 1;
                    }
                }

                int color = 0;
                while (color < k && used_colors[color] == 1) {
                    color++;
                }
                free(used_colors);

                if (color < k) {
                    colors[neighbor] = color;
                }
            }
        }
    }

    freeQueue(&bfs_queue);

    for (int i = 0; i < num_vertices; i++) {
        if (colors[i] == -1) {
            return -1;
        }
    }

    return 0;
}

void read_input(FILE* input, int* n, int* k, int*** adjacency_matrix) {
    fscanf(input, "%d %d", n, k);

    *adjacency_matrix = (int**)malloc(*n * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        (*adjacency_matrix)[i] = (int*)calloc(*n, sizeof(int));
    }

    int a, b;
    while (fscanf(input, "%d %d", &a, &b) != EOF) {
        
        (*adjacency_matrix)[a - 1][b - 1] = 1;
        (*adjacency_matrix)[b - 1][a - 1] = 1;
    }
}

void write_output(FILE* output, int num_vertices, int* colors) {
    for (int i = 0; i < num_vertices; i++) {
        fprintf(output, "%d ", colors[i] + 1);
    }
    fprintf(output, "\n");
}

int check_coloring(int num_vertices, int* colors) {
    for (int i = 0; i < num_vertices; i++) {
        if (colors[i] == -1) {
            return 0;
        }
    }
    return 1;
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    int n, k;
    int** adj_matrix = NULL;
    int* colors = NULL;
    read_input(input, &n, &k, &adj_matrix);
    colors = (int*)malloc(n * sizeof(int));
    int result = mainfunct(adj_matrix, n, k, colors);
    if (!check_coloring(n, colors)) {
        fprintf(output, "Не удалось раскрасить граф с использованием %d цветов.\n", k);
    }
    else {
        write_output(output, n, colors);
    }
    free_matrix(adj_matrix, n);
    free(colors);
    fclose(input);
    fclose(output);
    return 0;
}
