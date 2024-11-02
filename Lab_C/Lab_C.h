#ifndef LAB_C_H
#define LAB_C_H

#define MAX_NODES 50


typedef struct Node {
    int data;
    struct Node *next;
} Node;


typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue();
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int isEmpty(Queue *queue);
int *findShortestPath(int graph[MAX_NODES][MAX_NODES], int start, int end, int num_nodes, int *path_length);
int readGraphFromFile(const char *filename, int graph[MAX_NODES][MAX_NODES], int *num_nodes);




#endif