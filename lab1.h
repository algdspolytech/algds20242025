#pragma once
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedQueue {
    Node* front;
    Node* rear;
} LinkedQueue;

typedef struct ArrayQueue {
    int* arr;
    int front;
    int rear;
    int size;
    int capacity;
} ArrayQueue;

// Функции для очереди на связном списке
LinkedQueue* createLinkedQueue();
void enqueueLinked(LinkedQueue* q, int value);
int dequeueLinked(LinkedQueue* q);
int isEmptyLinked(LinkedQueue* q);
void destroyLinkedQueue(LinkedQueue* q);

// Функции для очереди на массиве
ArrayQueue* createArrayQueue(int capacity);
void enqueueArray(ArrayQueue* q, int value);
int dequeueArray(ArrayQueue* q);
int isEmpty(ArrayQueue* q);
void destroyArrayQueue(ArrayQueue* q);