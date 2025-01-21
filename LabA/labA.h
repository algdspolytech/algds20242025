#pragma once

// Node structure for linked queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// LinkedQueue structure
typedef struct LinkedQueue {
    Node* front; // Pointer to front node
    Node* rear;  // Pointer to rear node
} LinkedQueue;

// ArrayQueue structure
typedef struct ArrayQueue {
    int* arr;    // Array to hold the queue elements
    int front;   // Index of the front element
    int rear;    // Index of the rear element
    int size;    // Current number of elements in the queue
    int capacity; // Maximum capacity of the queue
} ArrayQueue;

// Functions for linked queue
LinkedQueue* createLinkedQueue();
void enqueueLinked(LinkedQueue* q, int value);
int dequeueLinked(LinkedQueue* q);
int isEmptyLinked(LinkedQueue* q);
void destroyLinkedQueue(LinkedQueue* q);

// Functions for array queue
ArrayQueue* createArrayQueue(int capacity);
void enqueueArray(ArrayQueue* q, int value);
int dequeueArray(ArrayQueue* q);
int isEmpty(ArrayQueue* q);
void destroyArrayQueue(ArrayQueue* q);