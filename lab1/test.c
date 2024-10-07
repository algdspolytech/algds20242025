#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "pch.h"

#define n 10 // Максимальное количество элементов в очереди

typedef struct {
    int elements[n];
    int front;
    int back;
} MQueue;

void InitQueue(MQueue* mqueue) {
    mqueue->front = 0;
    mqueue->back = 0;
}

int IsEmpty(MQueue* mqueue) {
    return mqueue->front == mqueue->back;
}

int enel(MQueue* mqueue, int x) {

    if ((mqueue->back + 1) % n == mqueue->front) {
        return 0;
    }
    mqueue->elements[mqueue->back] = x;
    mqueue->back = (mqueue->back + 1) % n;
    return 1;
}

int deel(MQueue* mqueue) {

    if (IsEmpty(mqueue)) {
        return -1;
    }
    int x = mqueue->elements[mqueue->front];
    mqueue->front = (mqueue->front + 1) % n;
    return x;
}

int size(MQueue* mqueue) {
    if (mqueue->front <= mqueue->back) {
        return mqueue->back - mqueue->front;
    }
    else {
        return n - mqueue->front + mqueue->back;
    }
}


struct Node {
    int data;
    struct Node* next;
};

struct LQueue {
    struct Node* front;
    struct Node* back;
};

struct LQueue* createLQueue() {
    struct LQueue* queue = (struct LQueue*)malloc(sizeof(struct LQueue));
    queue->front = queue->back = NULL;
    return queue;
}

void Lenqueue(struct LQueue* queue, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->back == NULL) {
        queue->front = queue->back = newNode;
        return;
    }

    queue->back->next = newNode;
    queue->back = newNode;
}

int Ldequeue(struct LQueue* queue) {
    if (queue->front == NULL) {
        return -1;
    }

    struct Node* temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->back = NULL;
    }

    free(temp);
    return data;
}

struct LQueue* lqueue;

void Create() {
    lqueue = (struct LQueue*)malloc(sizeof(struct LQueue));
    lqueue->front = lqueue->back = NULL;
}

void Clean() {
    struct Node* current = lqueue->front;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    free(lqueue);
}

// Тест: Добавление элемента в пустую очередь-список
TEST(QueueTest, ListAddToEmptyQueue_no1) {
    Create();

    Lenqueue(lqueue, 1);

    ASSERT_NE(lqueue->front, nullptr);
    ASSERT_NE(lqueue->back, nullptr);
    ASSERT_EQ(lqueue->front->data, 1);
    ASSERT_EQ(lqueue->back->data, 1);
    ASSERT_EQ(lqueue->front->next, nullptr);

    Clean();
}

// Тест: Добавление нескольких элементов в очередь-список
TEST(QueueTest, ListAddMultipleElements_no2) {
    Create();

    Lenqueue(lqueue, 1);
    Lenqueue(lqueue, 2);
    Lenqueue(lqueue, 3);

    ASSERT_EQ(lqueue->front->data, 1);
    ASSERT_EQ(lqueue->back->data, 3);
    ASSERT_EQ(lqueue->front->next->data, 2);
    ASSERT_EQ(lqueue->front->next->next->data, 3);
    ASSERT_EQ(lqueue->back->next, nullptr);

    Clean();
}

// Тест: dequeue из пустой очереди-списка
TEST(QueueTest, ListDequeueFromEmptyQueue_no3) {
    Create();
    EXPECT_EQ(Ldequeue(lqueue), -1);
    Clean();
}

// Тест: dequeue после добавления элемента в очередь-список
TEST(QueueTest, ListDequeueAfterEnqueue_no4) {
    Create();
    Lenqueue(lqueue, 1);
    EXPECT_EQ(Ldequeue(lqueue), 1);
    EXPECT_EQ(Ldequeue(lqueue), -1); 
    Clean();
}

MQueue mqueue;

// Тест: добавление элемента в очередь-массив
TEST(QueueTest, MassAddToEmptyQueue_no5) {
    InitQueue(&mqueue);
    enel(&mqueue, 1);
    
    ASSERT_EQ(mqueue.front, 0);
    ASSERT_EQ(mqueue.back, 1);
    
}

// Тест: Добавление элементов в непустую очередь-массив
TEST(QueueTest, MassDequeueFromEmptyQueue_no6) {
    InitQueue(&mqueue);
    enel(&mqueue, 1);
    enel(&mqueue, 2);
    ASSERT_EQ(mqueue.front, 0);
    ASSERT_EQ(mqueue.back, 2);
    ASSERT_EQ(mqueue.elements[mqueue.front], 1);
    ASSERT_EQ(mqueue.elements[mqueue.back - 1], 2);
}

// Тест: Удаление из пустой очереди-массива
TEST(QueueTest, MassDequeueFromEmptyQueue_no7) {
    InitQueue(&mqueue);
    ASSERT_EQ(deel(&mqueue), -1);
}

// Тест: Удаление из непустой очереди-массива
TEST(QueueTest, MassDequeueFromNonEmptyQueue_no8) {
    InitQueue(&mqueue);
    enel(&mqueue, 1);
    ASSERT_EQ(deel(&mqueue), 1);
    ASSERT_EQ(deel(&mqueue), -1);
}

// Тест: Добавление элемента в полную очередь-массив
TEST(QueueTest, MassDequeueFromFullQueue_no9) {
    InitQueue(&mqueue);
    for (int i = 0; i < n; ++i) {
        enel(&mqueue, i);
    }
    
    ASSERT_EQ(enel(&mqueue, 10), 0);
}

// Тест: Проверка функции IsEmpty
TEST(QueueTest, MassIsEmptyQueue_no10) {
    InitQueue(&mqueue);
    ASSERT_EQ(IsEmpty(&mqueue), 1);
}

// Тест: Проверка функции IsEmpty на не пустой очереди
TEST(QueueTest, MassIsEmptyQueue_no11) {
    InitQueue(&mqueue);
    enel(&mqueue, 1);
    ASSERT_EQ(IsEmpty(&mqueue), 0);
}
int main(int argc, char** argv) {
    setlocale(LC_CTYPE, "Russian");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}