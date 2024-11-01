//
//  main.c
//  Lab_A
//
//  Created by Фёдор Филь on 01.11.2024.
//

#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

#include <assert.h>

#define MAX_SIZE 100 // Максимальный размер очереди

// Структура очереди на массиве
typedef struct {
    int front;
    int rear;
    int size;
    int capacity;
    int * array;
}
QueueMassive;
QueueMassive * createQueueMassive(int capacity) {
    QueueMassive * queue = (QueueMassive * ) malloc(sizeof(QueueMassive));
    queue -> capacity = capacity;
    queue -> front = 0;
    queue -> size = 0;
    queue -> rear = capacity - 1;
    queue -> array = (int * ) malloc(queue -> capacity * sizeof(int));
    return queue;
}
int isFullQueueMassive(QueueMassive * queue) {
    return (queue -> size == queue -> capacity);
}
int isEmptyQueueMassive(QueueMassive * queue) {
    return (queue -> size == 0);
}
void enqueueMassive(QueueMassive * queue, int item) {
    if(isFullQueueMassive(queue)) return;
    queue -> rear = (queue -> rear + 1) % queue -> capacity;
    queue -> array[queue -> rear] = item;
    queue -> size += 1;
}
int dequeueMassive(QueueMassive * queue) {
    if(isEmptyQueueMassive(queue)) {
        printf("Queue is empty\n");
        return INT_MIN;
    }
    int item = queue -> array[queue -> front];
    queue -> front = (queue -> front + 1) % queue -> capacity;
    queue -> size -= 1;
    return item;
}
void printQueueMassive(QueueMassive * queue) {
    int i;
    for(i = queue -> front; i <= queue -> rear; i++) {
        printf("%d ", queue -> array[i]);
    }
    printf("\n");
}
// Структура узла списка
typedef struct Node {
    int data;
    struct Node * next;
}
Node;
// Структура очереди на списке
typedef struct QueueList {
    Node * head;
    Node * tail;
}
QueueList;
void initQueueList(QueueList * queue) {
    queue -> head = NULL;
    queue -> tail = NULL;
}
int isEmptyQueueList(QueueList * queue) {
    return (queue -> head == NULL);
}
void enqueueList(QueueList * queue, int value) {
    Node * newNode = (Node * ) malloc(sizeof(Node));
    newNode -> data = value;
    newNode -> next = NULL;
    if(isEmptyQueueList(queue)) {
        queue -> head = newNode;
        queue -> tail = newNode;
    } else {
        queue -> tail -> next = newNode;
        queue -> tail = newNode;
    }
}
int dequeueList(QueueList * queue) {
    if(isEmptyQueueList(queue)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    int value = queue -> head -> data;
    Node * temp = queue -> head;
    queue -> head = queue -> head -> next;
    free(temp);
    if(queue -> head == NULL) queue -> tail = NULL;
    return value;
}
void printQueueList(QueueList * queue) {
    Node * current = queue -> head;
    while(current != NULL) {
        printf("%d ", current -> data);
        current = current -> next;
    }
    printf("\n");
}
void testQueueIsEmptyMassive_no1(void) {
    QueueMassive * queue = createQueueMassive(MAX_SIZE);
    assert(isEmptyQueueMassive(queue));
    printf("Тест 1 пройден\n");
}
void testQueueEnqueueMassive_no2(void) {
    QueueMassive * queue = createQueueMassive(MAX_SIZE);
    enqueueMassive(queue, 10);
    assert(!isEmptyQueueMassive(queue));
    printf("Тест 2 пройден\n");
}
void testQueueEnqueueMassive_no3(void) {
    QueueMassive * queue = createQueueMassive(MAX_SIZE);
    enqueueMassive(queue, 10);
    enqueueMassive(queue, 20);
    enqueueMassive(queue, 30);
    assert(!isEmptyQueueMassive(queue));
    printf("Тест 3 пройден\n");
}
void testQueueDequeueMassive_no4(void) {
    QueueMassive * queue = createQueueMassive(MAX_SIZE);
    enqueueMassive(queue, 10);
    enqueueMassive(queue, 20);
    enqueueMassive(queue, 30);
    int dequeuedValue = dequeueMassive(queue);
    assert(dequeuedValue == 10);
    dequeuedValue = dequeueMassive(queue);
    assert(dequeuedValue == 20);
    dequeuedValue = dequeueMassive(queue);
    assert(dequeuedValue == 30);
    printf("Тест 4 пройден\n");
}
void testQueueIsFullMassive_no5(void) {
    QueueMassive * queue = createQueueMassive(MAX_SIZE);
    enqueueMassive(queue, 40);
    enqueueMassive(queue, 50);
    enqueueMassive(queue, 60);
    if(!isFullQueueMassive(queue)) {
        printf("Тест 5 пройден\n");
    } else {
        assert(isFullQueueMassive(queue));
        enqueueMassive(queue, 70);
    }
}
void testQueueIsEmptyList_no6(void) {
    QueueList queue;
    initQueueList(&queue);
    assert(isEmptyQueueList(&queue));
    printf("Тест 6 пройден\n");
}
void testQueueEnqueueList_no7(void) {
    QueueList queue;
    enqueueList(&queue, 10);
    assert(!isEmptyQueueList(&queue));
    printf("Тест 7 пройден\n");
}
void testQueueEnqueueList_no8(void) {
    QueueList queue;
    enqueueList(&queue, 10);
    enqueueList(&queue, 20);
    enqueueList(&queue, 30);
    assert(!isEmptyQueueList(&queue));
    printf("Тест 8 пройден\n");
}
void testQueueDequeueList_no9(void) {
    QueueList queue;
    enqueueList(&queue, 10);
    int dequeuedValue = dequeueList(&queue);
    assert(dequeuedValue == 10);
    printf("Тест 9 пройден\n");
}
void testQueueDequeueList_no10(void) {
    QueueList queue;
    enqueueList(&queue, 10);
    enqueueList(&queue, 20);
    enqueueList(&queue, 30);
    int dequeuedValue = dequeueList(&queue);
    assert(dequeuedValue == 10);
    dequeuedValue = dequeueList(&queue);
    assert(dequeuedValue == 20);
    dequeuedValue = dequeueList(&queue);
    assert(dequeuedValue == 30);
    printf("Тест 10 пройден\n");
}
int main(void) {
    printf("Queue with massive\n");
    QueueMassive * queueMassive = createQueueMassive(MAX_SIZE);
    enqueueMassive(queueMassive, 10);
    enqueueMassive(queueMassive, 20);
    enqueueMassive(queueMassive, 30);
    enqueueMassive(queueMassive, 40);
    printQueueMassive(queueMassive);
    int dequeuedItem = dequeueMassive(queueMassive);
    if(dequeuedItem != INT_MIN) printf("Dequeued: %d\n", dequeuedItem);
    printQueueMassive(queueMassive);
    printf("\n");
    printf("Queue with list\n");
    QueueList queueList;
    initQueueList(&queueList);
    enqueueList(&queueList, 10);
    enqueueList(&queueList, 20);
    enqueueList(&queueList, 30);
    enqueueList(&queueList, 40);
    printQueueList(&queueList);
    int dequeuedValue = dequeueList(&queueList);
    printf("Dequeued: %d\n", dequeuedValue);
    printQueueList(&queueList);
    testQueueIsEmptyMassive_no1();
    testQueueEnqueueMassive_no2();
    testQueueEnqueueMassive_no3();
    testQueueDequeueMassive_no4();
    testQueueIsFullMassive_no5();
    testQueueIsEmptyList_no6();
    testQueueEnqueueList_no7();
    testQueueEnqueueList_no8();
    testQueueDequeueList_no9();
    testQueueDequeueList_no10();
    return 0;
}
