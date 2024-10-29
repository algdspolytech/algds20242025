#ifndef EXPANDED_LINKED_LIST_H
#define EXPANDED_LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#define NODE_CAPACITY 4 

typedef struct Node {
    int values[NODE_CAPACITY];
    int count;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int total_count;
} ExpandedLinkedList;

// Инициализация списка
void init_list(ExpandedLinkedList* list);

// Добавление элемента в список
void add_element(ExpandedLinkedList* list, int value);

// Поиск индекса элемента по значению
int find_element_by_key(ExpandedLinkedList* list, int value);

// Поиск элемента по индексу
int find_element_by_index(ExpandedLinkedList* list, int index);

// Удаление элемента по индексу
bool remove_element_by_index(ExpandedLinkedList* list, int index);

// Подсчет общего количества элементов
int get_total_count(ExpandedLinkedList* list);

// Поиск следующего элемента после заданного значения
int get_next_element(ExpandedLinkedList* list, int value);

#endif // EXPANDED_LINKED_LIST_H
