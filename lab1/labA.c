#include "labA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// вычисление xor для указателей (строго внутри этого файла)
static inline Node* xor_node(Node* a, Node* b) {
    return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}

void init_list(XORList* list) {
    list->head = NULL;
    list->tail = NULL;
}

bool add_element(XORList* list, const char* data) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return false; // без юнит теста :(

    new_node->data = _strdup(data); 
    new_node->np = NULL;

    if (!list->head) { // добавляемый элемент - первый
        list->head = list->tail = new_node;
    }
    else {
        new_node->np = xor_node(NULL, list->tail);
        list->tail->np = xor_node(new_node, xor_node(list->tail->np, NULL));
        list->tail = new_node;
    }
    return true;
}

bool remove_by_key(XORList* list, const char* key) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current) {
        next = xor_node(prev, current->np);
        if (strcmp(current->data, key) == 0) {
            if (prev) {
                prev->np = xor_node(xor_node(prev->np, current), next);
            }
            else {
                list->head = next;
            }
            if (next) {
                next->np = xor_node(prev, xor_node(next->np, current));
            }
            else {
                list->tail = prev;
            }
            free(current->data);
            free(current);
            return true;
        }
        prev = current;
        current = next;
    }
    return false;
}

bool remove_by_address(XORList* list, Node* address) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current) {
        next = xor_node(prev, current->np);
        if (current == address) {
            if (prev) {
                prev->np = xor_node(xor_node(prev->np, current), next);
            }
            else {
                list->head = next;
            }
            if (next) {
                next->np = xor_node(prev, xor_node(next->np, current));
            }
            else {
                list->tail = prev;
            }
            free(current->data);
            free(current);
            return true;
        }
        prev = current;
        current = next;
    }
    return false;
}

// Поиск элемента по ключу
Node* find_by_key(const XORList* list, const char* key) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current) {
        next = xor_node(prev, current->np);
        if (strcmp(current->data, key) == 0) {
            return current;
        }
        prev = current;
        current = next;
    }
    return NULL;
}

// Итерирование по списку
Node* iterate_list(Node* prev, Node* current) {
    return xor_node(prev, current->np);
}