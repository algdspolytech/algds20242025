#include <stdio.h>
#include "labA.h"
#include <locale.h>

void testLinkedQueue();
void testArrayQueue();

int main() {
    setlocale(LC_CTYPE, "Russian");
    testLinkedQueue();
    testArrayQueue();
    return 0;
}

void testLinkedQueue() {
    LinkedQueue* q = createLinkedQueue();
    printf("����� ��� ������� �������\n\n");

    // Test_no1
    printf("���� 1: ���������� � ������ �������\n");
    enqueueLinked(q, 10);
    printf("Dequeued: %d\n", dequeueLinked(q));

    // Test_no2
    printf("���� 2: ���������� ���� ���������\n");
    enqueueLinked(q, 20);
    enqueueLinked(q, 30);
    printf("Dequeued: %d\n", dequeueLinked(q));
    printf("Dequeued: %d\n", dequeueLinked(q));

    // Test_no3
    printf("���� 3: ������� �� ������ �������\n");
    printf("Dequeued: %d\n", dequeueLinked(q)); // ������� -1

    // Test_no4
    printf("���� 4: ���������� �������� ����� ��������\n");
    enqueueLinked(q, 40);
    printf("Dequeued: %d\n", dequeueLinked(q)); // ������� 40

    // Test_no5
    printf("���� 5: ������������� ���������� ���������\n");
    for (int i = 50; i <= 70; i += 10) {
        enqueueLinked(q, i);
    }
    printf("��������� ��� ��������:\n");
    for (int i = 0; i < 3; i++) {
        printf("Dequeued: %d\n", dequeueLinked(q));
    }

    destroyLinkedQueue(q);
}

void testArrayQueue() {
    printf("\n����� ��� ��������� �������\n\n");
    ArrayQueue* q = createArrayQueue(4);

    // Test_no6
    printf("���� 6: ���������� � ������ ��������� �������\n");
    enqueueArray(q, 10);
    printf("Dequeued: %d\n", dequeueArray(q));

    // Test_no7
    printf("���� 7: ���������� ���� ���������\n");
    enqueueArray(q, 20);
    enqueueArray(q, 30);
    printf("Dequeued: %d\n", dequeueArray(q));
    printf("Dequeued: %d\n", dequeueArray(q));

    // Test_no8
    printf("���� 8: ������������ ��������� �������\n");
    for (int i = 40; i <= 70; i += 10) {
        enqueueArray(q, i);
    }
    printf("������� �������� � ������� ������� (80):\n");
    enqueueArray(q, 80); // ������� ��������� �� ������

    // Test_no9
    printf("���� 9: ������� ��� �������� �� ��������� �������\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeueArray(q)); // ������� �������� �� �������
    }
    printf("Dequeued: %d\n", dequeueArray(q)); // ������� -1

    // Test_no10
    printf("���� 10: ���������� ��������� ����� ������� ����������� �������\n");
    enqueueArray(q, 90);
    printf("Dequeued: %d\n", dequeueArray(q)); // ������� 90

    destroyArrayQueue(q);
}