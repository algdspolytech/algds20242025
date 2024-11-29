#define MAIN_H

#include <stdbool.h>

#define MAX_SIZE 100 // Максимальный размер очереди для реализации на массиве

// Очередь на основе связного списка

// Узел связного списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура очереди на основе связного списка
typedef struct {
    Node* front;
    Node* rear;
} LinkedQueue;

// Функции для работы с очередью на основе связного списка
LinkedQueue* createLinkedQueue();
void destroyLinkedQueue(LinkedQueue* queue);
bool isEmptyLinkedQueue(LinkedQueue* queue);
void enqueueLinkedQueue(LinkedQueue* queue, int value);
bool dequeueLinkedQueue(LinkedQueue* queue, int* value);

// Очередь на основе массива 

// Структура очереди на основе массива
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
} ArrayQueue;

// Функции для работы с очередью на основе массива
ArrayQueue* createArrayQueue();
void destroyArrayQueue(ArrayQueue* queue);
bool isEmptyArrayQueue(ArrayQueue* queue);
bool isFullArrayQueue(ArrayQueue* queue);
void enqueueArrayQueue(ArrayQueue* queue, int value);
bool dequeueArrayQueue(ArrayQueue* queue, int* value);


