#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#pragma warning (disable : 4996)
#include "Lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  

#define MAX 100


void TestenqueueList_AddElement_no1() {
    struct QueueList* queue = (struct QueueList*)malloc(sizeof(struct QueueList));
    queue->front = queue->rear = NULL;

    enqueueList(queue, 5);
    enqueueList(queue, 10);
    enqueueList(queue, 15);

    printf("Test 1 = %i\n", queue->front->data == 5 && queue->front->next->data == 10 && queue->rear->data == 15);

    free(queue);
}

void TestdequeueList_DeletElemente_no2() {
    struct QueueList* queue = (struct QueueList*)malloc(sizeof(struct QueueList));
    queue->front = queue->rear = NULL;

    enqueueList(queue, 42); 

    printf("Test 2 = %i\n", dequeueList(queue) == 42);

    free(queue);
}


void TestdequeueList_DeletFromEmpty_no3() {
    struct QueueList* queue = (struct QueueList*)malloc(sizeof(struct QueueList));
    queue->front = queue->rear = NULL;

    printf("Test 3 = %i\n", dequeueList(queue) == -1);

    free(queue);
}

void TestdequeueList_AfterDelet_no4() {
    struct QueueList* queue = (struct QueueList*)malloc(sizeof(struct QueueList));
    queue->front = queue->rear = NULL;

    enqueueList(queue, 5);
    enqueueList(queue, 10);
    enqueueList(queue, 15);


    dequeueList(queue);
    dequeueList(queue);
    dequeueList(queue);

    printf("Test 4 = %i\n", dequeueList(queue) == -1);

    free(queue);
}

void TestdequeueList_OrderOfDeletion_no5() {
    struct QueueList* queue = (struct QueueList*)malloc(sizeof(struct QueueList));
    queue->front = queue->rear = NULL;

    enqueueList(queue, 5);
    enqueueList(queue, 10);
    enqueueList(queue, 15);

    printf("Test 5 = %i\n", dequeueList(queue) == 5 && dequeueList(queue) == 10 && dequeueList(queue) == 15);

    free(queue);
}



struct QueueArray queue;

void TestenqueueArray_Pointers_no6() {
    queue = *createQueueArray();

    enqueueArray(&queue, 5);

    printf("Test 6 = %i\n", (queue.front == 0) && (queue.rear == 0));
}

void TestenqueueArray_AddElement_no7() {
    queue = *createQueueArray();

    enqueueArray(&queue, 10); 

    printf("Test 7 = %i\n", queue.items[queue.rear] == 10);
}

void TestdequeueArray_DeletFromEmpty_no8() {
    queue = *createQueueArray();

    int result = dequeueArray(&queue);
    printf("Test 8 = %d\n", result == -1);
}

void TestdequeueArray_DeletElemente_no9() {
    queue = *createQueueArray();

    enqueueArray(&queue, 20);
    int dequeued = dequeueArray(&queue);

    printf("Test 9 = %i\n", (dequeued == 20) && isEmptyArray(&queue));
}

void TestenqueuedequeueArray_Circular_no10() {
    queue = *createQueueArray();

    enqueueArray(&queue, 10);
    enqueueArray(&queue, 20);

    dequeueArray(&queue);

    enqueueArray(&queue, 30);

    printf("Test 10 = %i\n", (queue.front == 1) && (queue.rear == 2) && (queue.items[1] == 20) && (queue.items[2] == 30));
}


void runAllTests() {
    TestenqueueList_AddElement_no1();
    TestdequeueList_DeletElemente_no2();
    TestdequeueList_DeletFromEmpty_no3();
    TestdequeueList_AfterDelet_no4();
    TestdequeueList_OrderOfDeletion_no5();
    TestenqueueArray_Pointers_no6();
    TestenqueueArray_AddElement_no7();
    TestdequeueArray_DeletFromEmpty_no8();
    TestdequeueArray_DeletElemente_no9();
    TestenqueuedequeueArray_Circular_no10();
}

int main() {
    runAllTests();
    setlocale(LC_CTYPE, "Russian");
    return 0;
}
