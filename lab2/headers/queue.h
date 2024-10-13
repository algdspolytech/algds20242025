#pragma once
#include <stdlib.h>

typedef struct Nodeq {
  int data;
  struct Nodeq *next;
} Nodeq;

typedef struct {
  Nodeq *head;
  Nodeq *tail;
} queue;

char IsEmpty(queue *q);
queue *CreateQueue();
int PopQueue(queue *q);
void PushQueue(queue *q, int data);
void FreeQueue(queue *q);