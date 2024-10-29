#include "priority_queue.h"

Node* createNode(int data, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

void enqueue(PriorityQueue* pq, int data, int priority) {
    Node* newNode = createNode(data, priority);

    if (pq->head == NULL || pq->head->priority > priority) {
        newNode->next = pq->head;
        pq->head = newNode;
    }
    else {
        Node* current = pq->head;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int dequeue(PriorityQueue* pq) {
    if (pq->head == NULL) {
        printf("Очередь пуста.\n");
        return -1;
    }
    int data = pq->head->data;
    Node* temp = pq->head;
    pq->head = pq->head->next;
    free(temp);
    return data;
}

void display(PriorityQueue* pq) {
    Node* current = pq->head;
    while (current != NULL) {
        printf("Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }
}

void freeQueue(PriorityQueue* pq) {
    Node* current = pq->head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(pq);
}
