#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head; // указывает на первый элемент списка
} LinkedList;

// Функции для работы со списком
LinkedList* create_list();
void add_to_list(LinkedList *list, const char *data);
void free_list(LinkedList *list);
void sort_list(LinkedList *list);
void print_list(LinkedList *list);

#endif