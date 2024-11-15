#include <stdio.h>
#include <stdlib.h>
#include "Unrolled_linked_list.h"

/*//#define BLOCK_SIZE 4 // Размер блока в узле списка

// Определение структуры Node
struct Node {
    int values[BLOCK_SIZE]; // Массив значений в узле
    int count;              // Количество элементов в массиве values
    struct Node* next;      // Указатель на следующий узел
};

typedef struct Node Node;

// Определение структуры UnrolledLinkedList
struct UnrolledLinkedList {
    Node* head;  // Начало списка
    int size;    // Общее количество элементов в списке
};

typedef struct UnrolledLinkedList UnrolledLinkedList;
*/
// Создать новый узел
Node* createNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) { // Проверка успешного выделения памяти
        printf("Ошибка выделения памяти для узла.\n");
        return NULL;
    }
    node->count = 0;
    node->next = NULL;
    return node;
}

// Инициализация списка
UnrolledLinkedList* createList() {
    UnrolledLinkedList* list = (UnrolledLinkedList*)malloc(sizeof(UnrolledLinkedList));
    if (!list) { // Проверка успешного выделения памяти
        printf("Ошибка выделения памяти для списка.\n");
        return NULL;
    }
    list->head = createNode();
    if (!list->head) { // Проверка, если не удалось создать начальный узел
        free(list);
        return NULL;
    }
    list->size = 0;
    return list;
}

// Добавить элемент
void add(UnrolledLinkedList* list, int value) {
    if (!list) return; // Проверка указателя списка

    Node* current = list->head;
    // Переход к последнему узлу
    while (current->next != NULL) {
        current = current->next;
    }

    // Если текущий узел полон, создаем новый узел
    if (current->count == BLOCK_SIZE) {
        current->next = createNode();
        if (!current->next) return; // Проверка успешного выделения памяти
        current = current->next;
    }
    current->values[current->count++] = value;
    list->size++;
}

// Найти номер элемента по ключу
int findIndexByKey(UnrolledLinkedList* list, int key) {
    if (!list) return -1; // Проверка указателя списка

    Node* current = list->head;
    int index = 0;

    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (current->values[i] == key) {
                return index;
            }
            index++;
        }
        current = current->next;
    }
    return -1; // Если элемент не найден
}

// Найти элемент по номеру
int findByIndex(UnrolledLinkedList* list, int index) {
    if (!list || index < 0 || index >= list->size) return -1; // Проверка указателя списка

    Node* current = list->head;
    int count = 0;

    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (count == index) {
                return current->values[i];
            }
            count++;
        }
        current = current->next;
    }
    return -1;
}

// Удалить элемент по номеру
void deleteByIndex(UnrolledLinkedList* list, int index) {
    if (!list || index < 0 || index >= list->size) return; // Проверка указателя списка

    Node* current = list->head;
    int count = 0;

    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (count == index) {
                for (int j = i; j < current->count - 1; j++) {
                    current->values[j] = current->values[j + 1];
                }
                current->count--;
                list->size--;
                return;
            }
            count++;
        }
        current = current->next;
    }
}

// Подсчитать количество элементов
int getSize(UnrolledLinkedList* list) {
    return list ? list->size : 0; // Проверка указателя списка
}

// Найти следующий элемент
int getNext(UnrolledLinkedList* list, int value) {
    if (!list) return -1; // Проверка указателя списка

    Node* current = list->head;
    while (current != NULL) {
        for (int i = 0; i < current->count; i++) {
            if (current->values[i] == value) {
                if (i + 1 < current->count) {
                    return current->values[i + 1];
                }
                else if (current->next != NULL && current->next->count > 0) {
                    return current->next->values[0];
                }
                return -1; // Нет следующего элемента
            }
        }
        current = current->next;
    }
    return -1;
}

// Удалить список и освободить память
void freeList(UnrolledLinkedList* list) {
    if (!list) return; // Проверка указателя списка

    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

/*int main() {
    UnrolledLinkedList* list = createList();
    if (!list) return -1;

    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40);
    add(list, 50);

    printf("Size: %d\n", getSize(list));
    printf("Index of 30: %d\n", findIndexByKey(list, 30));
    printf("Element at index 2: %d\n", findByIndex(list, 2));

    deleteByIndex(list, 1);
    printf("Size after deletion: %d\n", getSize(list));

    printf("Next element after 40: %d\n", getNext(list, 40));

    freeList(list);

    return 0;
}*/