#include <stdio.h>
#include <stdlib.h>
#include "labA.h"

// Реализация очереди на связном списке

LinkedQueue* createLinkedQueue() {
    LinkedQueue* q = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueueLinked(LinkedQueue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (isEmptyLinked(q)) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeueLinked(LinkedQueue* q) {
    if (isEmptyLinked(q)) return -1; // Ошибка: очередь пуста
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) q->rear = NULL;
    return value;
}

int isEmptyLinked(LinkedQueue* q) {
    return q->front == NULL;
}

void destroyLinkedQueue(LinkedQueue* q) {
    while (!isEmptyLinked(q)) {
        dequeueLinked(q);
    }
    free(q);
}

// Реализация очереди на массиве

ArrayQueue* createArrayQueue(int capacity) {
    ArrayQueue* q = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    q->capacity = capacity;
    q->front = 0;
    q->size = 0; // текущий размер 
    q->rear = capacity - 1; // последний элемент
    q->arr = (int*)malloc(q->capacity * sizeof(int));
    return q;
}

int isFull(ArrayQueue* q) {
    return (q->size == q->capacity);
}

int isEmpty(ArrayQueue* q) {
    return (q->size == 0);
}

void enqueueArray(ArrayQueue* q, int item) {
    if (isFull(q)) {
        printf("Ошибка: очередь переполнена\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity; // циклическая очередь
    q->arr[q->rear] = item;
    q->size++;
}

int dequeueArray(ArrayQueue* q) {
    if (isEmpty(q)) {
        printf("Ошибка: очередь пуста\n");
        return -1; // возвращает значение ошибки
    }
    int item = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity; // циклическая очередь
    q->size--;
    return item;
}

void destroyArrayQueue(ArrayQueue* q) {
    free(q->arr);
    free(q);
}