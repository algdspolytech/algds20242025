#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// ���������� ������� �� ������ �������� ������

// �������� ����� �������
LinkedQueue* createLinkedQueue() {
    LinkedQueue* queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    if (!queue) {
        perror("Failed to create queue");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// ����������� �������
void destroyLinkedQueue(LinkedQueue* queue) {
    Node* current = queue->front;
    while (current) {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
    free(queue);
}

// ��������, ����� �� �������
bool isEmptyLinkedQueue(LinkedQueue* queue) {
    return queue->front == NULL;
}

// ���������� �������� � �������
void enqueueLinkedQueue(LinkedQueue* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to enqueue");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;

    if (queue->rear)
        queue->rear->next = newNode;
    else
        queue->front = newNode;

    queue->rear = newNode;
}

// �������� �������� �� �������
bool dequeueLinkedQueue(LinkedQueue* queue, int* value) {
    if (isEmptyLinkedQueue(queue))
        return false;

    Node* tmp = queue->front;
    *value = tmp->data;
    queue->front = tmp->next;

    if (!queue->front)
        queue->rear = NULL;

    free(tmp);
    return true;
}

// ���������� ������� �� ������ �������

// �������� ����� �������
ArrayQueue* createArrayQueue() {
    ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    if (!queue) {
        perror("Failed to create queue");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

// ����������� �������
void destroyArrayQueue(ArrayQueue* queue) {
    free(queue);
}

// ��������, ����� �� �������
bool isEmptyArrayQueue(ArrayQueue* queue) {
    return queue->size == 0;
}

// ��������, ����� �� �������
bool isFullArrayQueue(ArrayQueue* queue) {
    return queue->size == MAX_SIZE;
}

// ���������� �������� � �������
void enqueueArrayQueue(ArrayQueue* queue, int value) {
    if (isFullArrayQueue(queue)) {
        perror("Queue is full");
        exit(EXIT_FAILURE);
    }
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->data[queue->rear] = value;
    queue->size++;
}

// �������� �������� �� �������
bool dequeueArrayQueue(ArrayQueue* queue, int* value) {
    if (isEmptyArrayQueue(queue))
        return false;
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;
    return true;
}
