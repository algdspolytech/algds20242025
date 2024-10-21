#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
struct Node {
    int data;
    Node *next;
};

typedef struct {
    struct Node *front;
    struct Node *back;
} Queue;

Queue *CreateQueue();
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
int IsEmpty(Queue *queue);
void ShowQueue(Queue *queue);