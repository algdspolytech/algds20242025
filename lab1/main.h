#define MAIN_H

#include <stdbool.h>

#define MAX_SIZE 100 // ������������ ������ ������� ��� ���������� �� �������

// ������� �� ������ �������� ������

// ���� �������� ������
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ��������� ������� �� ������ �������� ������
typedef struct {
    Node* front;
    Node* rear;
} LinkedQueue;

// ������� ��� ������ � �������� �� ������ �������� ������
LinkedQueue* createLinkedQueue();
void destroyLinkedQueue(LinkedQueue* queue);
bool isEmptyLinkedQueue(LinkedQueue* queue);
void enqueueLinkedQueue(LinkedQueue* queue, int value);
bool dequeueLinkedQueue(LinkedQueue* queue, int* value);

// ������� �� ������ ������� 

// ��������� ������� �� ������ �������
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
} ArrayQueue;

// ������� ��� ������ � �������� �� ������ �������
ArrayQueue* createArrayQueue();
void destroyArrayQueue(ArrayQueue* queue);
bool isEmptyArrayQueue(ArrayQueue* queue);
bool isFullArrayQueue(ArrayQueue* queue);
void enqueueArrayQueue(ArrayQueue* queue, int value);
bool dequeueArrayQueue(ArrayQueue* queue, int* value);


