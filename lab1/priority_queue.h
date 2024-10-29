#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

Node* createNode(int data, int priority);
PriorityQueue* createPriorityQueue();
void enqueue(PriorityQueue* pq, int data, int priority);
int dequeue(PriorityQueue* pq);
void display(PriorityQueue* pq);
void freeQueue(PriorityQueue* pq);
