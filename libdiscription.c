#include "Libr.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Функция для создания нового узла
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(data) + 1); // +1 для '\0'
    strcpy(newNode->data, data); // Копируем строку
    newNode->next = NULL; // Изначально следующий узел NULL
    return newNode;
}

// Функция для добавления узла в конец списка
void append(Node** head, const char* str) {
    Node* new_node = createNode(str);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Функция для добавления узла в начало списка
void append_forward(Node** head, const char* data) {
    Node* new = createNode(data);
    new->next = *head;
    *head = new;
}

// Функция для разделения списка на две половины
void split(Node* source, Node** fir, Node** sec) {
    if (source == NULL) {
        *fir = NULL;
        *sec = NULL;
        return; // Если список пуст, ничего не делаем
    }

    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    // Сдвигаем указатели, чтобы разбить список
    while (fast != NULL) {
        fast = fast->next; // Перемещаем fast на 1 узел
        if (fast != NULL) {
            slow = slow->next; // Перемещаем slow на 1 узел
            fast = fast->next; // Перемещаем fast на 1 узел
        }
    }

    *fir = source; // Первая половина
    *sec = slow->next; // Вторая половина
    slow->next = NULL; // Разрываем связь
}

// Функция для слияния двух отсортированных списков
Node* merge(Node* a, Node* b) {
    Node* result = NULL;

    // Базовый случай
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // Выбираем меньший элемент
    if (strcmp(a->data, b->data) <= 0) {
        result = a;
        result->next = merge(a->next, b); // Рекурсивный вызов
    }
    else {
        result = b;
        result->next = merge(a, b->next); // Рекурсивный вызов
    }
    return result;
}

// Функция сортировки списка
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    // Базовый случай
    if (head == NULL || head->next == NULL) {
        return;
    }
    // Разделяем списки
    split(head, &a, &b);

    // Сортируем обе половины
    mergeSort(&a);
    mergeSort(&b);

    // Сливаем отсортированные половины
    *headRef = merge(a, b);
}

// Функция для вывода списка
void printList(Node* node) {
    while (node != NULL) {
        printf("%s\n", node->data);
        node = node->next;
    }
}