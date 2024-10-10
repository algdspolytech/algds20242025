#pragma warning(disable:4996)
#include "Array.h" 

// Инициализация очереди
void InitQueue(MQueue* queue) {
    queue->head = 0;
    queue->tail = 0;
}

// Проверка на пустоту очереди
int empty(MQueue* queue) {
    return queue->head == queue->tail;
}

// Добавление элемента в очередь
int enel(MQueue* queue, int x) {

    if ((queue->tail + 1) % k == queue->head) {
        return 0;
    }
    queue->elements[queue->tail] = x;
    queue->tail = (queue->tail + 1) % k;
    return 1;
}

// Удаление элемента из очереди
int deel(MQueue* queue) {

    if (empty(queue)) {
        return -1;
    }
    int x = queue->elements[queue->head];
    queue->head = (queue->head + 1) % k;
    return x;
}

// Получение количества элементов в очереди
int size(MQueue* queue) {
    if (queue->head <= queue->tail) {
        return queue->tail - queue->head;
    }
    else {
        return k - queue->head + queue->tail;
    }
}
