#pragma once
#define k 10 
typedef struct {
    int elements[k];
    int head;
    int tail;
} MQueue;
void InitQueue(MQueue* queue);
int empty(MQueue* queue);
int enel(MQueue* queue, int x);
int deel(MQueue* queue);
int size(MQueue* queue);