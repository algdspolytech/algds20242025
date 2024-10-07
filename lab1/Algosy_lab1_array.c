#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define n 5 // Максимальное количество элементов в очереди

typedef struct {
    int elements[n];
    int head;
    int tail;
} MQueue;

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
    
    if ((queue->tail + 1) % n == queue->head) {
        printf("Очередь полна!\n");
        return 0;
    }
    queue->elements[queue->tail] = x;
    queue->tail = (queue->tail + 1) % n;
    return 1;
}

// Удаление элемента из очереди
int deel(MQueue* queue) {
    
    if (empty(queue)) {
        printf("Очередь пуста!\n");
        return -1; 
    }
    int x = queue->elements[queue->head];
    queue->head = (queue->head + 1) % n;
    return x;
}

// Получение количества элементов в очереди
int size(MQueue* queue) {
    if (queue->head <= queue->tail) {
        return queue->tail - queue->head;
    }
    else {
        return n - queue->head + queue->tail;
    }
}


void ShowQueue(MQueue* queue) {
    int current = queue->head;
    printf("Элементы в очереди: ");
    while (current < queue->tail) {
        
        printf("%d ", queue->elements[current]);
        current++;
    }
}


/*int main() {
    setlocale(LC_CTYPE, "Russian");
    MQueue queue;
    InitQueue(&queue);
    int c, value;

    while (1) {
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Показать элементы очереди\n");
        printf("4. Проверить пустоту очереди\n");
        printf("5. Получить количество элементов в очереди\n");
        printf("6. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &c);

        switch (c) {
        case 1:
            printf("Введите значение для добавления: ");
            scanf("%d", &value);
            if (enel(&queue, value)) {
                printf("Элемент %d успешно вставлен в очередь.\n", value);
            }
            break;

        case 2:
            value = deel(&queue);
            if (value != -1) {
                printf("Элемент %d был удалён из очереди.\n", value);
            }
            break;
        case 3:
            ShowQueue(&queue);
            printf("\n");
            if (empty(&queue)) {
                printf("Очередь пуста!\n");
            }
            break;

        case 4:
            printf("Очередь пуста: %s\n", empty(&queue) ? "Да" : "Нет");
            break;

        case 5:
            printf("Количество элементов в очереди: %d\n", size(&queue));
            break;

        case 6:
            printf("Выход из программы.\n");
            return 0;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}*/
