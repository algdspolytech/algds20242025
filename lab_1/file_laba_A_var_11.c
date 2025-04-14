#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)  

#define MAX_SIZE 2

// ---- очередь с помощью связного списка ----

struct Node {
    int data;
    struct Node* next;
};

struct QueueLinkedList {
    struct Node* front;
    struct Node* rear;
};

void initQueueLinkedList(struct QueueLinkedList* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueueLinkedList(struct QueueLinkedList* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeueLinkedList(struct QueueLinkedList* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    struct Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int isEmptyLinkedList(struct QueueLinkedList* q) {
    return (q->front == NULL);
}

void printQueueLinkedList(struct QueueLinkedList* q) {
    struct Node* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// ---- очередь с помощью массива ----

struct QueueArray {
    int arr[MAX_SIZE];
    int front;
    int rear;
};

void initQueueArray(struct QueueArray* q) {
    q->front = -1;
    q->rear = -1;
}

void enqueueArray(struct QueueArray* q, int value) {
    if (q->rear == MAX_SIZE - 1) {
        printf("Queue is full\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;
    }

    q->rear++;
    q->arr[q->rear] = value;
}

int dequeueArray(struct QueueArray* q) {
    if (q->front == -1) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->arr[q->front];
    q->front++;

    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }

    return value;
}

int isEmptyArray(struct QueueArray* q) {
    return (q->front == -1);
}

void printQueueArray(struct QueueArray* q) {
    if (q->front == -1) {
        printf("Queue is empty\n");
        return;
    }

    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

// ---- Main ----

int main() {
    int choice, value;
    struct QueueLinkedList qLinkedList;
    struct QueueArray qArray;

    printf("Choose the type of queue implementation:\n");
    printf("1. Linked List Queue\n");
    printf("2. Array Queue\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        initQueueLinkedList(&qLinkedList);
        printf("\nQueue initialized as Linked List.\n");

        while (1) {
            printf("\n1. Enqueue\n2. Dequeue\n3. Print Queue\n4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueueLinkedList(&qLinkedList, value);
                break;
            case 2:
                value = dequeueLinkedList(&qLinkedList);
                if (value != -1) {
                    printf("Dequeued: %d\n", value);
                }
                break;
            case 3:
                printf("Queue: ");
                printQueueLinkedList(&qLinkedList);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
            }
        }
    }
    else if (choice == 2) {
        initQueueArray(&qArray);
        printf("\nQueue initialized as Array.\n");

        while (1) {
            printf("\n1. Enqueue\n2. Dequeue\n3. Print Queue\n4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueueArray(&qArray, value);
                break;
            case 2:
                value = dequeueArray(&qArray);
                if (value != -1) {
                    printf("Dequeued: %d\n", value);
                }
                break;
            case 3:
                printf("Queue: ");
                printQueueArray(&qArray);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
            }
        }
    }
    else {
        printf("Invalid choice\n");
    }

    return 0;
}

// test Lab A 
#include <gtest/gtest.h>

extern "C" {
    #include "../include/queue.h"
}


TEST(QueueLinkedListTest, EnqueueDequeueSingle) {
    struct QueueLinkedList q;
    initQueueLinkedList(&q);

    enqueueLinkedList(&q, 42);
    EXPECT_EQ(dequeueLinkedList(&q), 42);
    EXPECT_TRUE(isEmptyLinkedList(&q));
}

TEST(QueueLinkedListTest, EnqueueDequeueMultiple) {
    struct QueueLinkedList q;
    initQueueLinkedList(&q);

    enqueueLinkedList(&q, 10);
    enqueueLinkedList(&q, 20);
    enqueueLinkedList(&q, 30);

    EXPECT_EQ(dequeueLinkedList(&q), 10);
    EXPECT_EQ(dequeueLinkedList(&q), 20);
    EXPECT_EQ(dequeueLinkedList(&q), 30);
    EXPECT_TRUE(isEmptyLinkedList(&q));
}

TEST(QueueLinkedListTest, DequeueFromEmptyQueue) {
    struct QueueLinkedList q;
    initQueueLinkedList(&q);
    EXPECT_EQ(dequeueLinkedList(&q), -1);
}

TEST(QueueLinkedListTest, IsEmptyAfterOperations) {
    struct QueueLinkedList q;
    initQueueLinkedList(&q);
    enqueueLinkedList(&q, 1);
    dequeueLinkedList(&q);
    EXPECT_TRUE(isEmptyLinkedList(&q));
}

TEST(QueueArrayTest, EnqueueDequeueSingle) {
    struct QueueArray q;
    initQueueArray(&q);

    enqueueArray(&q, 77);
    EXPECT_EQ(dequeueArray(&q), 77);
    EXPECT_TRUE(isEmptyArray(&q));
}

TEST(QueueArrayTest, EnqueueDequeueMultiple) {
    struct QueueArray q;
    initQueueArray(&q);

    enqueueArray(&q, 5);
    enqueueArray(&q, 15);

    EXPECT_EQ(dequeueArray(&q), 5);
    EXPECT_EQ(dequeueArray(&q), 15);
    EXPECT_TRUE(isEmptyArray(&q));
}

TEST(QueueArrayTest, OverflowQueue) {
    struct QueueArray q;
    initQueueArray(&q);

    enqueueArray(&q, 1);
    enqueueArray(&q, 2);
    enqueueArray(&q, 3);  
    EXPECT_EQ(q.rear, 1); 
}

TEST(QueueArrayTest, DequeueEmptyQueue) {
    struct QueueArray q;
    initQueueArray(&q);
    EXPECT_EQ(dequeueArray(&q), -1);
}

TEST(QueueArrayTest, IsEmptyAfterReset) {
    struct QueueArray q;
    initQueueArray(&q);

    enqueueArray(&q, 11);
    dequeueArray(&q); 
    EXPECT_TRUE(isEmptyArray(&q));

    enqueueArray(&q, 22);
    EXPECT_EQ(dequeueArray(&q), 22);
}

//Сравнение двух реализаций
//1. очередь со связанным списком
//Льготы :
//Размер хвоста не ограничен, так как он динамичный.
//Операции enqueue и dequeue могут выполняться за постоянное время O(1) для каждой операции.
//Издержки :
  //  Требуется динамическое распределение памяти, что может привести к накладным расходам и более сложному управлению памятью.
    //Обработка указателей в связанных структурах может усложнить обслуживание кода.
    //2. очередь с помощью массива
  //  Льготы :
//Реализация проще и не требует динамического управления памятью.
//Доступ к элементам осуществляется напрямую с помощью подсказки, что в определенных ситуациях может быть быстрее.
//Издержки :
    //Размер массива ограничен определенным значением(здесь MAX_SIZE), и после заполнения очередь больше не может принимать новые элементы.
    //Если элемент в передней части хвоста удален, все последующие элементы должны быть смещены, если хвост используется классическим способом, что делает операцию менее эффективной в этом случае(сложность O(n), если такие операции, как dequeue или enqueue, часто выполняются со статическим массивом).
    //Вывод
    //Используйте очередь со связанным списком, когда вам нужна динамическая и гибкая структура данных с размером, который может варьироваться.
    //Используйте очередь с массивом, если вы заранее знаете максимальный размер и вам нужна производительность, оптимизированная для небольших и средних очередей.
