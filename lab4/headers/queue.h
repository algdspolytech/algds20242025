#pragma once
#include "tree.h"
#include <stdlib.h>

typedef struct Nodeq {
  Node *data;
  struct Nodeq *next;
} Nodeq;

typedef struct {
  Nodeq *head;
  Nodeq *tail;
} queue;

char IsEmpty(queue *q);
queue *CreateQueue();
Node *PopQueue(queue *q);
void PushQueue(queue *q, Node *data);
void FreeQueue(queue *q);