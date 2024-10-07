#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front; 
    struct Node* back;  
};

struct Queue* CreateQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue -> front = queue -> back = NULL;
    return queue;
}


void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> data = data;
    newNode -> next = NULL;

    if (queue -> back == NULL) {
        queue -> front = queue -> back = newNode;
        return;
    }

    queue -> back -> next = newNode;
    queue -> back = newNode;
}


int dequeue(struct Queue* queue) {
    if (queue -> front == NULL) {
        printf("Очередь пуста!\n");
        return -1;
    }

    struct Node* temp = queue -> front;
    int data = temp -> data;

    queue -> front = queue -> front -> next;

    if (queue -> front == NULL) {
        queue -> back = NULL;
    }

    free(temp);
    return data;
}


int IsEmpty(struct Queue* queue) {
    return queue -> front == NULL;
}


void ShowQueue(struct Queue* queue) {
    struct Node* current = queue->front;
    printf("Элементы в очереди: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}


/*int main() {

    setlocale(LC_CTYPE, "Russian");

    struct Queue* queue = CreateQueue();

    int c, data;

    while (1) {
        printf("1. Добавить элемент в очередь\n");
        printf("2. Удалить элемент из очереди\n");
        printf("3. Показать все элементы очереди\n");
        printf("4. Выйти\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &c);

        switch (c) {
        case 1:
            printf("Введите элемент для добавления: ");
            scanf("%d", &data);
            enqueue(queue, data);
            break;
        case 2:
            data = dequeue(queue);
            if (data != -1) {
                printf("Удаленный элемент: %d\n", data);
            }
            break;
        case 3:
            ShowQueue(queue);
            if (IsEmpty(queue)) {
                printf("Очередь пуста!\n");
            }
            break;
        case 4:
            printf("Выход из программы.\n");
            free(queue);
            return 0;
        default:
            printf("Неверный выбор, попробуйте еще раз.\n");
        }
        printf("\n");
    }

    return 0;
}
*/