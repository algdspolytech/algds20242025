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
    printf("Тесты для связной очереди\n\n");

    // Test_no1
    printf("Тест 1: Добавление в пустую очередь\n");
    enqueueLinked(q, 10);
    printf("Dequeued: %d\n", dequeueLinked(q));

    // Test_no2
    printf("Тест 2: Добавление двух элементов\n");
    enqueueLinked(q, 20);
    enqueueLinked(q, 30);
    printf("Dequeued: %d\n", dequeueLinked(q));
    printf("Dequeued: %d\n", dequeueLinked(q));

    // Test_no3
    printf("Тест 3: Дефицит из пустой очереди\n");
    printf("Dequeued: %d\n", dequeueLinked(q)); // Ожидаем -1

    // Test_no4
    printf("Тест 4: Добавление элемента после удаления\n");
    enqueueLinked(q, 40);
    printf("Dequeued: %d\n", dequeueLinked(q)); // Ожидаем 40

    // Test_no5
    printf("Тест 5: Множественное добавление элементов\n");
    for (int i = 50; i <= 70; i += 10) {
        enqueueLinked(q, i);
    }
    printf("Доставить все элементы:\n");
    for (int i = 0; i < 3; i++) {
        printf("Dequeued: %d\n", dequeueLinked(q));
    }

    destroyLinkedQueue(q);
}

void testArrayQueue() {
    printf("\nТесты для массивной очереди\n\n");
    ArrayQueue* q = createArrayQueue(4);

    // Test_no6
    printf("Тест 6: Добавление в пустую массивную очередь\n");
    enqueueArray(q, 10);
    printf("Dequeued: %d\n", dequeueArray(q));

    // Test_no7
    printf("Тест 7: Добавление двух элементов\n");
    enqueueArray(q, 20);
    enqueueArray(q, 30);
    printf("Dequeued: %d\n", dequeueArray(q));
    printf("Dequeued: %d\n", dequeueArray(q));

    // Test_no8
    printf("Тест 8: Переполнение массивной очереди\n");
    for (int i = 40; i <= 70; i += 10) {
        enqueueArray(q, i);
    }
    printf("Попытка добавить в очередь элемент (80):\n");
    enqueueArray(q, 80); // Ожидаем сообщение об ошибке

    // Test_no9
    printf("Тест 9: Достаем все элементы из массивной очереди\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeueArray(q)); // Достаем элементы из очереди
    }
    printf("Dequeued: %d\n", dequeueArray(q)); // Ожидаем -1

    // Test_no10
    printf("Тест 10: Добавление элементов после полного опустошения очереди\n");
    enqueueArray(q, 90);
    printf("Dequeued: %d\n", dequeueArray(q)); // Ожидаем 90

    destroyArrayQueue(q);
}