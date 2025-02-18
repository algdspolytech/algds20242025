#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>    // бла-бла-бла чекаю гит работает не работает ёмаё 

#define MAX 100 

struct Node {
    int data;
    struct Node* next;
};

struct QueueList {
    struct Node* front;
    struct Node* rear;
};

struct QueueArray {
    int items[MAX];
    int front;
    int rear;
};

struct Node* newNode(int data);

struct QueueList* createQueueList();

void enqueueList(struct QueueList* q, int data);

int dequeueList(struct QueueList* q);

int isEmptyList(struct QueueList* q);

struct QueueArray* createQueueArray();

int isEmptyArray(struct QueueArray* q);

int isFull(struct QueueArray* q);

void enqueueArray(struct QueueArray* q, int data);

int dequeueArray(struct QueueArray* q);