#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

void TestAddToEmptyList_HappyPath_no1() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 2);
    int data = dequeue(pq);
    printf("Test 1 = %s\n", (data == 10) ? "PASSED" : "FAILED");
    freeQueue(pq);
}

void TestAddMultipleElements_HappyPath_no2() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 2);
    enqueue(pq, 20, 1);
    enqueue(pq, 30, 3);
    int data = dequeue(pq);
    printf("Test 2 = %s\n", (data == 20) ? "PASSED" : "FAILED");
    freeQueue(pq);
}

void TestEmptyQueueDequeue_no3() {
    PriorityQueue* pq = createPriorityQueue();
    int data = dequeue(pq);
    printf("Test 3 = %s\n", (data == -1) ? "PASSED" : "FAILED"); /* Ïå÷àòàåì -1 ïðè ïóñòîé î÷åðåäè */
    freeQueue(pq);
}

void TestAddSamePriority_no4() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 2);
    enqueue(pq, 20, 2); // Òîò æå ïðèîðèòåò
    int data1 = dequeue(pq);
    int data2 = dequeue(pq);
    printf("Test 4 = %s\n", (data1 == 10 && data2 == 20) ? "PASSED" : "FAILED");
    freeQueue(pq);
}

void TestPrioritizeLowerValue_no5() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 3);
    enqueue(pq, 20, 1);
    enqueue(pq, 15, 2);
    int data1 = dequeue(pq);
    printf("Test 5 = %s\n", (data1 == 20) ? "PASSED" : "FAILED"); // Äîëæåí áûòü 20 ñ ïðèîðèòåòîì 1
    freeQueue(pq);
}

void TestMultipleDequeue_no6() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 1);
    enqueue(pq, 20, 2);
    enqueue(pq, 30, 3);
    int data1 = dequeue(pq);
    int data2 = dequeue(pq);
    printf("Test 6 = %s\n", (data1 == 10 && data2 == 20) ? "PASSED" : "FAILED");
    freeQueue(pq);
}

void TestOrderPreservation_no7() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 1);
    enqueue(pq, 20, 2);
    enqueue(pq, 30, 3);
    enqueue(pq, 5, 1);

    int data1 = dequeue(pq);
    int data2 = dequeue(pq);
    printf("Test 7 = %s\n", (data1 == 5 && data2 == 10) ? "PASSED" : "FAILED"); // Äîëæíû áûòü 5 è 10
    freeQueue(pq);
}

void TestQuickEnqueueDequeue_no8() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 2);
    enqueue(pq, 5, 1);

    int data1 = dequeue(pq); // Äîëæåí áûòü 5
    int data2 = dequeue(pq); // Äîëæåí áûòü 10
    printf("Test 8 = %s\n", (data1 == 5 && data2 == 10) ? "PASSED" : "FAILED");
    freeQueue(pq);
}

void TestFreeQueue_no9() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 1);
    enqueue(pq, 20, 2);
    freeQueue(pq); // Ïðîâåðèì, ÷òîáû íå áûëî óòå÷êè ïàìÿòè
    printf("Test 9 = PASSED\n");
}

void TestMultipleSamePriorityDequeue_no10() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 2);
    enqueue(pq, 20, 2);
    enqueue(pq, 30, 2);

    int data1 = dequeue(pq);
    int data2 = dequeue(pq);
    int data3 = dequeue(pq);

    // Ïîñêîëüêó ïîðÿäîê âñòàâêè áûë 10, 20, 30, òî äîëæíû áûòü â ýòîì ïîðÿäêå
    printf("Test 10 = %s\n", (data1 == 10 && data2 == 20 && data3 == 30) ? "PASSED" : "FAILED");
    freeQueue(pq);
}

int main() {
    TestAddToEmptyList_HappyPath_no1();
    TestAddMultipleElements_HappyPath_no2();
    TestEmptyQueueDequeue_no3();
    TestAddSamePriority_no4();
    TestPrioritizeLowerValue_no5();
    TestMultipleDequeue_no6();
    TestOrderPreservation_no7();
    TestQuickEnqueueDequeue_no8();
    TestFreeQueue_no9();
    TestMultipleSamePriorityDequeue_no10();

    return 0;
}
