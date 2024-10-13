
#pragma warning(disable : 4996)
#include "../includes/Arr_queue.h"
#include "../includes/List_queue.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для проверки равенства двух значений
int ASSERT_EQ(int expected, int actual, const char* message, char* test_name) {
    expected != actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %d, Actual: %d\n", expected, actual);
    return expected == actual;
}

// Функция для проверки неравенства двух значений
int ASSERT_NE(int expected, int actual, const char* message, char* test_name) {
    expected == actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %d, Actual: %d\n", expected, actual);
    return expected != actual;
}

// Функция для проверки неравенства указателей
int ASSERT_PTR_NE(void* expected, void* actual, const char* message, char* test_name) {
    expected == actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %p, Actual: %p\n", expected, actual);
    return expected != actual;
}

// Функция для проверки равенства указателей
int ASSERT_PTR_EQ(void* expected, void* actual, const char* message, char* test_name) {
    expected != actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %p, Actual: %p\n", expected, actual);
    return expected == actual;
}

void print_result_testing(int status, char* test_name) {
    status != 0 && printf("%s - Success\n", test_name) || printf("%s - Failed\n", test_name);
}

Queue* lqueue;
MQueue mqueue;

void Clean() {
    Node* current = lqueue->front;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(lqueue);
}

// Тест: Добавление элемента в пустую очередь-список
int Test_ListAddToEmptyQueue_no1() {
    lqueue = CreateQueue();
    int status = 1;
    enqueue(lqueue, 1);

    status *= ASSERT_PTR_NE(lqueue->front, NULL, "lqueue->front should not be NULL", "Test_ListAddToEmptyQueue_no1");
    status *= ASSERT_PTR_NE(lqueue->back, NULL, "lqueue->back should not be NULL", "Test_ListAddToEmptyQueue_no1");
    status *= ASSERT_EQ(lqueue->front->data, 1, "lqueue->front->data should be 1", "Test_ListAddToEmptyQueue_no1");
    status *= ASSERT_EQ(lqueue->back->data, 1, "lqueue->back->data should be 1", "Test_ListAddToEmptyQueue_no1");
    status *= ASSERT_PTR_EQ(lqueue->front->next, NULL, "lqueue->front->next should be NULL", "Test_ListAddToEmptyQueue_no1");
    print_result_testing(status, "Test_ListAddToEmptyQueue_no1");
    Clean();
    return status;
}

// Тест: Добавление нескольких элементов в очередь-список
int Test_ListAddMultipleElements_no2() {
    lqueue = CreateQueue();
    int status = 1;
    enqueue(lqueue, 1);
    enqueue(lqueue, 2);
    enqueue(lqueue, 3);

    status *= ASSERT_EQ(lqueue->front->data, 1, "lqueue->front->data should be 1", "Test_ListAddMultipleElements_no2");
    status *= ASSERT_EQ(lqueue->back->data, 3, "lqueue->back->data should be 3", "Test_ListAddMultipleElements_no2");
    status *= ASSERT_EQ(lqueue->front->next->data, 2, "lqueue->front->next->data should be 2", "Test_ListAddMultipleElements_no2");
    status *= ASSERT_EQ(lqueue->front->next->next->data, 3, "lqueue->front->next->next->data should be 3", "Test_ListAddMultipleElements_no2");
    status *= ASSERT_PTR_EQ(lqueue->back->next, NULL, "lqueue->back->next should be NULL", "Test_ListAddMultipleElements_no2");
    print_result_testing(status, "Test_ListAddMultipleElements_no2");
    Clean();
    return status;
}



// Тест: dequeue из пустой очереди-списка
int Test_ListDequeueFromEmptyQueue_no3() {
    lqueue = CreateQueue();
    int status = 1;
    status *= ASSERT_EQ(dequeue(lqueue), -1, "dequeue from empty queue should return -1", "Test_ListDequeueFromEmptyQueue_no3");
    print_result_testing(status, "Test_ListDequeueFromEmptyQueue_no3");
    Clean();
    return status;
}


// Тест: dequeue после добавления элемента в очередь-список
int Test_ListDequeueAfterEnqueue_no4() {
    lqueue = CreateQueue();
    int status = 1;
    enqueue(lqueue, 1);
    status *= ASSERT_EQ(dequeue(lqueue), 1, "dequeue after enqueue should return 1", "Test_ListDequeueAfterEnqueue_no4");
    status *= ASSERT_EQ(dequeue(lqueue), -1, "dequeue from empty queue should return -1", "Test_ListDequeueAfterEnqueue_no4");
    print_result_testing(status, "Test_ListDequeueAfterEnqueue_no4");
    Clean();
    return status;
}

// Тест: добавление элемента в очередь-массив
int Test_MassAddToEmptyQueue_no5() {
    InitQueue(&mqueue);
    int status = 1;
    enel(&mqueue, 1);

    status *= ASSERT_EQ(mqueue.head, 0, "mqueue.head should be 0", "Test_MassAddToEmptyQueue_no5");
    status *= ASSERT_EQ(mqueue.tail, 1, "mqueue.tail should be 1", "Test_MassAddToEmptyQueue_no5");
    print_result_testing(status, "Test_MassAddToEmptyQueue_no5");
    return status;
}

// Тест: Добавление элементов в непустую очередь-массив
int Test_MassDequeueFromEmptyQueue_no6() {
    InitQueue(&mqueue);
    int status = 1;
    enel(&mqueue, 1);
    enel(&mqueue, 2);
    status *= ASSERT_EQ(mqueue.head, 0, "mqueue.head should be 0", "Test_MassDequeueFromEmptyQueue_no6");
    status *= ASSERT_EQ(mqueue.tail, 2, "mqueue.tail should be 2", "Test_MassDequeueFromEmptyQueue_no6");
    status *= ASSERT_EQ(mqueue.elements[mqueue.head], 1, "mqueue.elements[mqueue.head] should be 1", "Test_MassDequeueFromEmptyQueue_no6");
    status *= ASSERT_EQ(mqueue.elements[mqueue.tail - 1], 2, "mqueue.elements[mqueue.tail - 1] should be 2", "Test_MassDequeueFromEmptyQueue_no6");
    print_result_testing(status, "Test_MassDequeueFromEmptyQueue_no6");
    return status;
}

// Тест: Удаление из пустой очереди-массива
int Test_MassDequeueFromEmptyQueue_no7() {
    InitQueue(&mqueue);
    int status = 1;
    status *= ASSERT_EQ(deel(&mqueue), -1, "deel from empty queue should return -1", "Test_MassDequeueFromEmptyQueue_no7");
    print_result_testing(status, "Test_MassDequeueFromEmptyQueue_no7");
    return status;
}

// Тест: Удаление из непустой очереди-массива
int Test_MassDequeueFromNonEmptyQueue_no8() {
    InitQueue(&mqueue);
    int status = 1;
    enel(&mqueue, 1);
    status *= ASSERT_EQ(deel(&mqueue), 1, "deel from non-empty queue should return 1", "Test_MassDequeueFromNonEmptyQueue_no8");
    status *= ASSERT_EQ(deel(&mqueue), -1, "deel from empty queue should return -1", "Test_MassDequeueFromNonEmptyQueue_no8");
    print_result_testing(status, "Test_MassDequeueFromNonEmptyQueue_no8");
    return status;
}

// Тест: Добавление элемента в полную очередь-массив
int Test_MassDequeueFromFullQueue_no9() {
    InitQueue(&mqueue);
    int status = 1;
    for (int i = 0; i < k; ++i) {
        enel(&mqueue, i);
    }

    status *= ASSERT_EQ(enel(&mqueue, 10), 0, "enel to full queue should return 0", "Test_MassDequeueFromFullQueue_no9");
    print_result_testing(status, "Test_MassDequeueFromFullQueue_no9");
    return status;
}

// Тест: Проверка функции IsEmpty
int Test_MassIsEmptyQueue_no10() {
    InitQueue(&mqueue);
    int status = 1;
    status *= ASSERT_EQ(empty(&mqueue), 1, "empty queue should return 1", "Test_MassIsEmptyQueue_no10");
    print_result_testing(status, "Test_MassIsEmptyQueue_no10");
    return status;
}

// Тест: Проверка функции IsEmpty на не пустой очереди
int Test_MassIsEmptyQueue_no11() {
    InitQueue(&mqueue);
    int status = 1;
    enel(&mqueue, 1);
    status *= ASSERT_EQ(empty(&mqueue), 0, "non-empty queue should return 0", "Test_MassIsEmptyQueue_no11");
    print_result_testing(status, "Test_MassIsEmptyQueue_no11");
    return status;
}


int main() {
    int result_testing = 1;
    result_testing *= Test_ListAddToEmptyQueue_no1();
    result_testing *= Test_ListAddMultipleElements_no2();
    result_testing *= Test_ListDequeueFromEmptyQueue_no3();
    result_testing *= Test_ListDequeueAfterEnqueue_no4();
    result_testing *= Test_MassAddToEmptyQueue_no5();
    result_testing *= Test_MassDequeueFromEmptyQueue_no6();
    result_testing *= Test_MassDequeueFromEmptyQueue_no7();
    result_testing *= Test_MassDequeueFromNonEmptyQueue_no8();
    result_testing *= Test_MassDequeueFromFullQueue_no9();
    result_testing *= Test_MassIsEmptyQueue_no10();
    result_testing *= Test_MassIsEmptyQueue_no11();

    result_testing == 1 && printf("All tests passed!\n") || printf("Some tests failed");
    return 0;
}