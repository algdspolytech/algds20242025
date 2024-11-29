#include "../headers/queue.h"

queue *CreateQueue() {
  queue *new = malloc(sizeof(queue));
  new->head = NULL;
  new->tail = NULL;
  return new;
}

Node *PopQueue(queue *q) {
  if (IsEmpty(q)) {
    perror("Pop from empty queue");
    exit(1);
  }
  Nodeq *t = q[0].head;
  Node *data = t->data;
  q[0].head = q[0].head->next;
  if (q[0].head == NULL) {
    q[0].tail = NULL;
  }
  free(t);
  return data;
}

char IsEmpty(queue *q) { return q[0].head == NULL; }

void PushQueue(queue *q, Node *data) {
  Nodeq *t = malloc(sizeof(Nodeq));
  t->data = data;
  t->next = NULL;
  if (IsEmpty(q)) {
    q[0].head = t;
    q[0].tail = t;
  } else {
    q[0].tail->next = t;
    q[0].tail = t;
  }
}

void FreeQueue(queue *q) {
  while (!IsEmpty(q)) {
    PopQueue(q);
  }
  free(q);
}
