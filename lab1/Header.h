#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

#define MAX 100 // ������������ ������ ������� ��� ��������� ����������

// ��������� ���� ��� �������� ������
struct Node {
    int data;
    struct Node* next;
};

// ��������� ������� �� ������ �������� ������
struct QueueLinkedList {
    struct Node* front;
    struct Node* rear; 
};

// ��������� ������� �� ������ �������
struct QueueArray {
    int items[MAX];
    int front;
    int rear;
};

// ������� ��� ������� �� ������ �������� ������
struct Node* newNode(int data);

struct QueueLinkedList* createQueueLinkedList();

void enqueueLinkedList(struct QueueLinkedList* q, int data);

int dequeueLinkedList(struct QueueLinkedList* q);

int isEmptyLinkedList(struct QueueLinkedList* q);

// ������� ��� ������� �� ������ �������
struct QueueArray* createQueueArray();

int isEmptyArray(struct QueueArray* q);

int isFull(struct QueueArray* q);

void enqueueArray(struct QueueArray* q, int data);

int dequeueArray(struct QueueArray* q); 