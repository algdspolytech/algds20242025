#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node {
    int data;
    struct Node* next;
} Node;


typedef struct {
    Node* head;
    Node* tail;
    int size;
} Queue;

void Queue_Init(Queue* queue);
void push(Queue* queue, int x);
int pop(Queue* queue);
void Queue_Free(Queue* queue);
