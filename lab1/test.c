#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <stdio.h>
#include "Header.h"
#include <stdlib.h>
#include <locale.h>  
#pragma warning (disable : 4996)

#define MAX 100


//�������� ���������� ��������� � ������� �� ������ �������� ������
void TestenqueueLinkedList_AddElement_no1() {
    struct QueueLinkedList* queue = (struct QueueLinkedList*)malloc(sizeof(struct QueueLinkedList));
    queue->front = queue->rear = NULL;

    // ��������� ��������
    enqueueLinkedList(queue, 5);
    enqueueLinkedList(queue, 10);
    enqueueLinkedList(queue, 15);

    printf("Test 1 = %i\n", queue->front->data == 5 && queue->front->next->data == 10 && queue->rear->data == 15);

    free(queue);
}

// �������� ���������� ������ ��������
void TestdequeueLinkedList_DeletElemente_no2() {
    struct QueueLinkedList* queue = (struct QueueLinkedList*)malloc(sizeof(struct QueueLinkedList));
    queue->front = queue->rear = NULL;

    enqueueLinkedList(queue, 42); // ��������� ���� �������

    // ���������, ��� ����������� ������� ��� �������� ���������
    printf("Test 2 = %i\n", dequeueLinkedList(queue) == 42);

    free(queue);
}


//���������� �� ������ ������� �������� ������
void TestdequeueLinkedList_DeletFromEmpty_no3() {
    struct QueueLinkedList* queue = (struct QueueLinkedList*)malloc(sizeof(struct QueueLinkedList));
    queue->front = queue->rear = NULL;

    printf("Test 3 = %i\n", dequeueLinkedList(queue) == -1);

    free(queue);
}

//�������� ��������� ������� �� ������ �������� ������ ����� ���������� ���� ���������
void TestdequeueLinkedList_AfterDelet_no4() {
    struct QueueLinkedList* queue = (struct QueueLinkedList*)malloc(sizeof(struct QueueLinkedList));
    queue->front = queue->rear = NULL;

    // ��������� ��������� ��������� � �������
    enqueueLinkedList(queue, 5);
    enqueueLinkedList(queue, 10);
    enqueueLinkedList(queue, 15);


    dequeueLinkedList(queue);
    dequeueLinkedList(queue);
    dequeueLinkedList(queue);

    printf("Test 4 = %i\n", dequeueLinkedList(queue) == -1);
 
    free(queue);
}

//�������� ������� ���������� ��������� �� ������� �������� ������
void TestdequeueLinkedList_OrderOfDeletion_no5() {
    struct QueueLinkedList* queue = (struct QueueLinkedList*)malloc(sizeof(struct QueueLinkedList));
    queue->front = queue->rear = NULL;

    // ��������� ��������� ��������� � �������
    enqueueLinkedList(queue, 5);
    enqueueLinkedList(queue, 10);
    enqueueLinkedList(queue, 15);

    printf("Test 5 = %i\n", dequeueLinkedList(queue) == 5 && dequeueLinkedList(queue) == 10 && dequeueLinkedList(queue) == 15);

    // ������������ ������
    free(queue);
}



struct QueueArray queue;

//�������� ��������� ���������� front � rear ����� ���������� �������� � ������� �������
void TestenqueueArray_Pointers_no6() {
    queue = *createQueueArray();

    // ���������� ��������
    enqueueArray(&queue, 5);

    printf("Test 6 = %i\n", (queue.front == 0) && (queue.rear == 0));
}

// ���������� �������� � ������� �������
void TestenqueueArray_AddElement_no7() {
    queue = *createQueueArray();

    enqueueArray(&queue, 10); // ���������� ��������

    printf("Test 7 = %i\n", queue.items[queue.rear] == 10);
}

//���������� �� ������ ������� �������
void TestdequeueArray_DeletFromEmpty_no8() {
    queue = *createQueueArray();

    // �������� ������� ������� �� ������ �������
    int result = dequeueArray(&queue);
    printf("Test 8 = %d\n", result == -1);
}

//�������� �������� �� ������� �������
void TestdequeueArray_DeletElemente_no9() {
    queue = *createQueueArray();

    enqueueArray(&queue, 20);
    int dequeued = dequeueArray(&queue);

    printf("Test 9 = %i\n", (dequeued == 20) && isEmptyArray(&queue));
}

//�������� ���������� ���������
void TestenqueuedequeueArray_Circular_no10() {
    queue = *createQueueArray();

    // ��������� 2 ��������
    enqueueArray(&queue, 10);
    enqueueArray(&queue, 20);

    // ������� ���� �������
    dequeueArray(&queue);

    // ��������� ��� �������
    enqueueArray(&queue, 30);

    printf("Test 10 = %i\n", (queue.front == 1) && (queue.rear == 2) && (queue.items[1] == 20) && (queue.items[2] == 30));
}


void runAllTests() {
    TestenqueueLinkedList_AddElement_no1();
    TestdequeueLinkedList_DeletElemente_no2();
    TestdequeueLinkedList_DeletFromEmpty_no3();
    TestdequeueLinkedList_AfterDelet_no4();
    TestdequeueLinkedList_OrderOfDeletion_no5();
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
