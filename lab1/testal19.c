#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include<stdlib.h>



// Функция для создания нового узла
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = _strdup(data);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Функция для разделения списка на две половины
void split(Node* head, Node** firstHalf, Node** secondHalf) {
    Node* fast = head;
    Node* slow = head;
    *firstHalf = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    *secondHalf = slow->next;
    slow->next = NULL;
}

// Функция для слияния двух отсортированных списков
Node* merge(Node* first, Node* second) {
    if (!first) return second;
    if (!second) return first;

    if (strcmp(first->data, second->data) < 0) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// Основная функция сортировки по слиянию
Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* firstHalf, * secondHalf;
    split(head, &firstHalf, &secondHalf);

    firstHalf = mergeSort(firstHalf);
    secondHalf = mergeSort(secondHalf);

    return merge(firstHalf, secondHalf);
}

// Функция для вывода списка
void printList(Node* node) {
    while (node) {
        printf("%s ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Освобождение памяти
void freeList(Node* node) {
    while (node) {
        Node* temp = node;
        node = node->next;
        free(temp->data);
        free(temp);
    }
}

