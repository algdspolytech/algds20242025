#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Lab_C.h"
#include "tests.h"

Queue *createQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return -1; 
    }

    Node *temp = queue->front;
    int data = temp->data;
    queue->front = temp->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

int isEmpty(Queue *queue) {
    return queue->front == NULL;
}


int *findShortestPath(int graph[MAX_NODES][MAX_NODES], int start, int end, int num_nodes, int *path_length) {
    int visited[MAX_NODES] = {0}; 
    int distance[MAX_NODES]; 
    int parent[MAX_NODES]; 

    for (int i = 0; i < num_nodes; i++) {
        distance[i] = INT_MAX; 
        parent[i] = -1; 
    }

    distance[start] = 0; 
    Queue *queue = createQueue(); 
    enqueue(queue, start); 

    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        visited[current] = 1;

        for (int i = 0; i < num_nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                if (distance[i] > distance[current] + 1) { 
                    distance[i] = distance[current] + 1; 
                    parent[i] = current; 
                    enqueue(queue, i); 
                }
            }
        }
    }

    if (distance[end] == INT_MAX) {
        *path_length = 0;
        free(queue);
        return NULL; // Путь не найден
    }

    // Создание массива для пути
    int *path = (int *)malloc(MAX_NODES * sizeof(int));
    if (path == NULL) {
        *path_length = 0;
        free(queue);
        return NULL; // Не удалось выделить память
    }

    *path_length = 0; 
    int current = end;

    while (current != -1) {
        path[*path_length] = current; 
        (*path_length)++;
        current = parent[current];
    }

    free(queue);
    return path; 
}


int readGraphFromFile(const char *filename, int graph[MAX_NODES][MAX_NODES], int *num_nodes) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Ошибка открытия файла: %s\n", filename);
        return 1;
    }

    fscanf(file, "%d", num_nodes); 

    
    if (*num_nodes <= 0 || *num_nodes > MAX_NODES) {
        printf("Некорректное количество вершин в файле.\n");
        fclose(file);
        return 1;
    }


    for (int i = 0; i < *num_nodes; i++) {
        for (int j = 0; j < *num_nodes; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
    return 0;
}

int main() {
  run_tests();
  
  return 0;
}