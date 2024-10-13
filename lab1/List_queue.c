#pragma warning(disable : 4996)
#include "../includes/List_queue.h"
#include <stdio.h>
#include <stdlib.h>


Queue *CreateQueue() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->front = queue->back = NULL;
    return queue;
}

void enqueue(Queue *queue, int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->back == NULL) {
        queue->front = queue->back = newNode;
        return;
    }

    queue->back->next = newNode;
    queue->back = newNode;
}


int dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return -1;
    }

    Node *temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->back = NULL;
    }

    free(temp);
    return data;
}


int IsEmpty(Queue *queue) {
    return queue->front == NULL;
}


void ShowQueue(Queue *queue) {
    Node *current = queue->front;
    printf("Elements in queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}