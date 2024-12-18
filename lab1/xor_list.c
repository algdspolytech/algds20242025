#include "xor_list.h"

// XOR двух указателей
Node* XOR(Node* a, Node* b) {
    return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Добавление элемента в конец списка
void add(Node** head, char* str) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    new_node->data = strdup(str); // Копируем строку
    new_node->np = NULL;

    if (*head == NULL) { // Список пуст
        *head = new_node;
    }
    else {
        Node* prev = NULL;
        Node* current = *head;

        // Переходим к последнему узлу
        while (XOR(prev, current->np) != NULL) {
            Node* next = XOR(prev, current->np);
            prev = current;
            current = next;
        }

        // Обновляем указатели
        current->np = XOR(prev, new_node);
        new_node->np = XOR(current, NULL);
    }
}

// Найти элемент по ключу
Node* find(Node* head, char* key) {
    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        if (strcmp(current->data, key) == 0) {
            return current;
        }
        Node* next = XOR(prev, current->np);
        prev = current;
        current = next;
    }
    return NULL;
}

// Удаление элемента по ключу
void deleteByKey(Node** head, char* key) {
    Node* prev = NULL;
    Node* current = *head;

    while (current != NULL) {
        if (strcmp(current->data, key) == 0) {
            Node* next = XOR(prev, current->np);

            if (prev != NULL) {
                prev->np = XOR(XOR(prev->np, current), next);
            }
            if (next != NULL) {
                next->np = XOR(prev, XOR(next->np, current));
            }
            if (current == *head) {
                *head = next;
            }

            free(current->data);
            free(current);
            return;
        }
        Node* next = XOR(prev, current->np);
        prev = current;
        current = next;
    }
}

// Удаление элемента по адресу
void deleteByAddress(Node** head, Node* node) {
    if (node == NULL) return;

    Node* prev = NULL;
    Node* current = *head;

    while (current != NULL) {
        if (current == node) {
            Node* next = XOR(prev, current->np);

            if (prev != NULL) {
                prev->np = XOR(XOR(prev->np, current), next);
            }
            if (next != NULL) {
                next->np = XOR(prev, XOR(next->np, current));
            }
            if (current == *head) {
                *head = next;
            }

            free(current->data);
            free(current);
            return;
        }
        Node* next = XOR(prev, current->np);
        prev = current;
        current = next;
    }
}

// Печать списка
void printList(Node* head) {
    Node* prev = NULL;
    Node* current = head;

    printf("Список: ");
    while (current != NULL) {
        printf("%s -> ", current->data);
        Node* next = XOR(prev, current->np);
        prev = current;
        current = next;
    }
    printf("NULL\n");
}

// Освобождение памяти
void freeList(Node* head) {
    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        Node* next = XOR(prev, current->np);
        free(current->data);
        free(current);
        prev = current;
        current = next;
    }
}