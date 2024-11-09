#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <stdio.h>
#include "Header.h""
#include <stdlib.h>
#include <locale.h>  
#pragma warning (disable : 4996)

#define MAX 100 // ������������ ������ ������� ��� ��������� ����������


// ������� ��� ������� �� ������ �������� ������

 // ������� ��� �������� ������ ����
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// ������� ��� �������� ������� �� ������ �������� ������
struct QueueLinkedList* createQueueLinkedList() {
    struct QueueLinkedList* q = (struct QueueLinkedList*)malloc(sizeof(struct QueueLinkedList));
    q->front = q->rear = NULL;
    return q;
}

// ������� ��� ���������� �������� � ������� �� ������ �������� ������
void enqueueLinkedList(struct QueueLinkedList* q, int data) {
    struct Node* temp = newNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// ������� ��� ���������� �������� �� ������� �� ������ �������� ������
int dequeueLinkedList(struct QueueLinkedList* q) {
    if (q->front == NULL) {
        return -1; // ������� �����
    }
    struct Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

// ������� ��� ��������, ����� �� ������� �� ������ �������� ������
int isEmptyLinkedList(struct QueueLinkedList* q) {
    return q->front == NULL;
}

// ������� ��� ������� �� ������ �������

// ������� ��� �������� ������� �� ������ �������
struct QueueArray* createQueueArray() {
    struct QueueArray* q = (struct QueueArray*)malloc(sizeof(struct QueueArray));
    q->front = -1;
    q->rear = -1;
    return q;
}

// ������� ��� ��������, ����� �� ������� �� ������ �������
int isEmptyArray(struct QueueArray* q) {
    return q->front == -1;
}

// ������� ��� ��������, ����� �� ������� �� ������ �������
int isFull(struct QueueArray* q) {
    return q->rear == MAX - 1;
}

// ������� ��� ���������� �������� � ������� �� ������ �������
void enqueueArray(struct QueueArray* q, int data) {
    if (isFull(q)) {
        printf("������� �����\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = data;
}

// ������� ��� ���������� �������� �� ������� �� ������ �������
int dequeueArray(struct QueueArray* q) {
    if (isEmptyArray(q)) {
        return -1; // ������� �����
    }
    int data = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = q->rear = -1; // ���� ������� ��������� �������
    }
    else {
        q->front++;
    }
    return data;
}