#include <stdio.h>
#include <assert.h>
#include "labA.h"
#include <locale.h>

void testLinkedQueue();
void testArrayQueue();

int main() {
    setlocale(LC_CTYPE, "Russian");
    testLinkedQueue();
    testArrayQueue();
    printf("Все тесты успешно пройдены!\n");
    return 0;
}

void testLinkedQueue() {
    LinkedQueue* q = createLinkedQueue();
    printf("Тесты для связной очереди\n\n");

    // Test_no1
    printf("Тест 1: Добавление в пустую очередь\n");
    enqueueLinked(q, 10);
    assert(dequeueLinked(q) == 10);

    // Test_no2
    printf("Тест 2: Добавление двух элементов\n");
    enqueueLinked(q, 20);
    enqueueLinked(q, 30);
    assert(dequeueLinked(q) == 20);
    assert(dequeueLinked(q) == 30);

    // Test_no3
    printf("Тест 3: Дефицит из пустой очереди\n");
    assert(dequeueLinked(q) == -1); // Ожидаем -1

    // Test_no4
    printf("Тест 4: Добавление элемента после удаления\n");
    enqueueLinked(q, 40);
    assert(dequeueLinked(q) == 40); // Ожидаем 40

    // Test_no5
    printf("Тест 5: Множественное добавление элементов\n");
    for (int i = 50; i <= 70; i += 10) {
        enqueueLinked(q, i);
    }
    for (int i = 50; i <= 70; i += 10) {
        assert(dequeueLinked(q) == i);
    }

    destroyLinkedQueue(q);
}

void testArrayQueue() {
    printf("\nТесты для массивной очереди\n\n");
    ArrayQueue* q = createArrayQueue(4);

    // Test_no6
    printf("Тест 6: Добавление в пустую массивную очередь\n");
    enqueueArray(q, 10);
    assert(dequeueArray(q) == 10);

    // Test_no7
    printf("Тест 7: Добавление двух элементов\n");
    enqueueArray(q, 20);
    enqueueArray(q, 30);
    assert(dequeueArray(q) == 20);
    assert(dequeueArray(q) == 30);

    // Test_no8
    printf("Тест 8: Переполнение массивной очереди\n");
    for (int i = 40; i <= 70; i += 10) {
        enqueueArray(q, i);
    }
    assert(!enqueueArray(q, 80));

    // Test_no9
    printf("Тест 9: Достаем все элементы из массивной очереди\n");
    for (int i = 40; i <= 70; i += 10) {
        assert(dequeueArray(q) == i);
    }
    assert(dequeueArray(q) == -1);

    // Test_no10
    printf("Тест 10: Добавление элементов после полного опустошения очереди\n");
    enqueueArray(q, 90);
    assert(dequeueArray(q) == 90);

    destroyArrayQueue(q);
}
