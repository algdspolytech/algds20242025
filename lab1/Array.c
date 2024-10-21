#pragma warning(disable:4996)
#include "Array.h" 

// ������������� �������
void InitQueue(MQueue* queue) {
    queue->head = 0;
    queue->tail = 0;
}

// �������� �� ������� �������
int empty(MQueue* queue) {
    return queue->head == queue->tail;
}

// ���������� �������� � �������
int enel(MQueue* queue, int x) {

    if ((queue->tail + 1) % k == queue->head) {
        return 0;
    }
    queue->elements[queue->tail] = x;
    queue->tail = (queue->tail + 1) % k;
    return 1;
}

// �������� �������� �� �������
int deel(MQueue* queue) {

    if (empty(queue)) {
        return -1;
    }
    int x = queue->elements[queue->head];
    queue->head = (queue->head + 1) % k;
    return x;
}

// ��������� ���������� ��������� � �������
int size(MQueue* queue) {
    if (queue->head <= queue->tail) {
        return queue->tail - queue->head;
    }
    else {
        return k - queue->head + queue->tail;
    }
}
