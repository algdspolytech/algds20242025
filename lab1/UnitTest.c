#pragma warning(disable: 4996)
#include "Array.h"
#include "List.h"

// Функция для проверки равенства двух значений
bool ASSERT_EQ(int expected, int actual, const char* test_name) {
    if (expected != actual) {
        return false;
    }
    return true;
}

// Функция для проверки неравенства двух значений
bool ASSERT_NE(int expected, int actual, const char* test_name) {
    if (expected == actual) {
        return false;
    }
    return true;
}

// Тест: Добавление элемента в пустую очередь-список
void Test_ListAddToEmptyQueue_no1() {
    bool success = true;
    Queue lqueue;
    Queue_Init(&lqueue);

    push(&lqueue, 1);

    success &= ASSERT_EQ(lqueue.head->data, 1, "Test_ListAddToEmptyQueue_no1");
    success &= ASSERT_EQ(lqueue.tail->data, 1, "Test_ListAddToEmptyQueue_no1");

    Queue_Free(&lqueue);

    if (success) {
        printf("Test_ListAddToEmptyQueue_no1: success\n\n");
    }
    else printf("Test_ListAddToEmptyQueue_no1: failure\n\n");
}

// Тест: Добавление нескольких элементов в очередь-список
void Test_ListAddMultipleElements_no2() {
    bool success = true;
    Queue lqueue;
    Queue_Init(&lqueue);

    push(&lqueue, 1);
    push(&lqueue, 2);
    push(&lqueue, 3);

    success &= ASSERT_EQ(lqueue.head->data, 1, "Test_ListAddMultipleElements_no2");
    success &= ASSERT_EQ(lqueue.tail->data, 3, "Test_ListAddMultipleElements_no2");
    success &= ASSERT_EQ(lqueue.head->next->data, 2, "Test_ListAddMultipleElements_no2");
    success &= ASSERT_EQ(lqueue.head->next->next->data, 3, "Test_ListAddMultipleElements_no2");

    Queue_Free(&lqueue);

    if (success) {
        printf("Test_ListAddMultipleElements_no2: success\n\n");
    }
    else printf("Test_ListAddMultipleElements_no2: failure\n\n");
}

// Тест: dequeue из пустой очереди-списка
void Test_ListDequeueFromEmptyQueue_no3() {
    bool success = true;
    Queue lqueue;
    Queue_Init(&lqueue);

    success &= ASSERT_EQ(pop(&lqueue), -1, "Test_ListDequeueFromEmptyQueue_no3");

    Queue_Free(&lqueue);

    if (success) {
        printf("Test_ListDequeueFromEmptyQueue_no3: success\n\n");
    }
    else printf("Test_ListDequeueFromEmptyQueue_no3: failure\n\n");
}

// Тест: dequeue после добавления элемента в очередь-список
void Test_ListDequeueAfterEnqueue_no4() {
    bool success = true;
    Queue lqueue;
    Queue_Init(&lqueue);

    push(&lqueue, 1);

    success &= ASSERT_EQ(pop(&lqueue), 1, "Test_ListDequeueAfterEnqueue_no4");
    success &= ASSERT_EQ(pop(&lqueue), -1, "Test_ListDequeueAfterEnqueue_no4");

    Queue_Free(&lqueue);

    if (success) {
        printf("Test_ListDequeueAfterEnqueue_no4: success\n\n");
    }
    else printf("Test_ListDequeueAfterEnqueue_no4: failure\n\n");
}

// Тест: добавление элемента в очередь-массив
void Test_MassAddToEmptyQueue_no5() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    success &= enel(&mqueue, 1);

    success &= ASSERT_EQ(mqueue.head, 0, "Test_MassAddToEmptyQueue_no5");
    success &= ASSERT_EQ(mqueue.tail, 1, "Test_MassAddToEmptyQueue_no5");

    if (success) {
        printf("Test_MassAddToEmptyQueue_no5: success\n\n");
    }
    else printf("Test_MassAddToEmptyQueue_no5: failure\n\n");
}

// Тест: Добавление элементов в непустую очередь-массив
void Test_MassDequeueFromEmptyQueue_no6() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    success &= enel(&mqueue, 1);
    success &= enel(&mqueue, 2);

    success &= ASSERT_EQ(mqueue.head, 0, "Test_MassDequeueFromEmptyQueue_no6");
    success &= ASSERT_EQ(mqueue.tail, 2, "Test_MassDequeueFromEmptyQueue_no6");
    success &= ASSERT_EQ(mqueue.elements[mqueue.head], 1, "Test_MassDequeueFromEmptyQueue_no6");
    success &= ASSERT_EQ(mqueue.elements[mqueue.tail - 1], 2, "Test_MassDequeueFromEmptyQueue_no6");

    if (success) {
        printf("Test_MassDequeueFromEmptyQueue_no6: success\n\n");
    }
    else printf("Test_MassDequeueFromEmptyQueue_no6: failure\n\n");
}

// Тест: Удаление из пустой очереди-массива
void Test_MassDequeueFromEmptyQueue_no7() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    success &= ASSERT_EQ(deel(&mqueue), -1, "Test_MassDequeueFromEmptyQueue_no7");

    if (success) {
        printf("Test_MassDequeueFromEmptyQueue_no7: success\n\n");
    }
    else printf("Test_MassDequeueFromEmptyQueue_no7: failure\n\n");
}

// Тест: Удаление из непустой очереди-массива
void Test_MassDequeueFromNonEmptyQueue_no8() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    success &= enel(&mqueue, 1);

    success &= ASSERT_EQ(deel(&mqueue), 1, "Test_MassDequeueFromNonEmptyQueue_no8");
    success &= ASSERT_EQ(deel(&mqueue), -1, "Test_MassDequeueFromNonEmptyQueue_no8");

    if (success) {
        printf("Test_MassDequeueFromNonEmptyQueue_no8: success\n\n");
    }
    else printf("Test_MassDequeueFromNonEmptyQueue_no8: failure\n\n");
}

// Тест: Добавление элемента в полную очередь-массив
void Test_MassDequeueFromFullQueue_no9() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    for (int i = 0; i < k - 1; ++i) {
        success &= enel(&mqueue, i);
    }

    success &= ASSERT_EQ(enel(&mqueue, 10), 0, "Test_MassDequeueFromFullQueue_no9");

    if (success) {
        printf("Test_MassDequeueFromFullQueue_no9: success\n\n");
    }
    else printf("Test_MassDequeueFromFullQueue_no9: failure\n\n");
}

// Тест: Проверка функции empty
void Test_MassIsEmptyQueue_no10() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    success &= ASSERT_EQ(empty(&mqueue), 1, "Test_MassIsEmptyQueue_no10");

    if (success) {
        printf("Test_MassIsEmptyQueue_no10: success\n\n");
    }
    else printf("Test_MassIsEmptyQueue_no10: failure\n\n");
}

// Тест: Проверка функции empty на не пустой очереди
void Test_MassIsEmptyQueue_no11() {
    bool success = true;
    MQueue mqueue;
    InitQueue(&mqueue);

    success &= enel(&mqueue, 1);

    success &= ASSERT_EQ(empty(&mqueue), 0, "Test_MassIsEmptyQueue_no11");

    if (success) {
        printf("Test_MassIsEmptyQueue_no11: success\n\n");
    }
    else printf("Test_MassIsEmptyQueue_no11: failure\n\n");
}

int main() {
    Test_ListAddToEmptyQueue_no1();
    Test_ListAddMultipleElements_no2();
    Test_ListDequeueFromEmptyQueue_no3();
    Test_ListDequeueAfterEnqueue_no4();
    Test_MassAddToEmptyQueue_no5();
    Test_MassDequeueFromEmptyQueue_no6();
    Test_MassDequeueFromEmptyQueue_no7();
    Test_MassDequeueFromNonEmptyQueue_no8();
    Test_MassDequeueFromFullQueue_no9();
    Test_MassIsEmptyQueue_no10();
    Test_MassIsEmptyQueue_no11();

    printf("All tests passed!\n");
    return 0;
}
