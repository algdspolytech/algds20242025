#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

#define MAX 100 // Максимальный размер очереди для массивной реализации

// Структура узла для связного списка
struct Node {
    int data;
    struct Node* next;
};

// Структура очереди на основе связного списка
struct QueueLinkedList {
    struct Node* front;
    struct Node* rear; 
};

// Структура очереди на основе массива
struct QueueArray {
    int items[MAX];
    int front;
    int rear;
};

// Функции для очереди на основе связного списка
struct Node* newNode(int data);

struct QueueLinkedList* createQueueLinkedList();

void enqueueLinkedList(struct QueueLinkedList* q, int data);

int dequeueLinkedList(struct QueueLinkedList* q);

int isEmptyLinkedList(struct QueueLinkedList* q);

// Функции для очереди на основе массива
struct QueueArray* createQueueArray();

int isEmptyArray(struct QueueArray* q);

int isFull(struct QueueArray* q);

void enqueueArray(struct QueueArray* q, int data);

int dequeueArray(struct QueueArray* q); 