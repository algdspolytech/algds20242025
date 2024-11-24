// unrolled_linked_list.h
#pragma once
#ifndef UNROLLED_LINKED_LIST_H
#define UNROLLED_LINKED_LIST_H


#include <stdlib.h>
#include  <stdbool.h>

#define BLOCK_SIZE 4

typedef struct Node {
    int values[BLOCK_SIZE];
    int count;
    struct Node* next;
} Node;

typedef struct UnrolledLinkedList {
    Node* head;
    int size;
} UnrolledLinkedList;

UnrolledLinkedList* createList();
void add(UnrolledLinkedList* list, int value);
int findIndexByKey(UnrolledLinkedList* list, int key);
int findByIndex(UnrolledLinkedList* list, int index);
void deleteByIndex(UnrolledLinkedList* list, int index);
int getSize(UnrolledLinkedList* list);
int getNext(UnrolledLinkedList* list, int value);
void freeList(UnrolledLinkedList* list);

#endif // UNROLLED_LINKED_LIST_H
