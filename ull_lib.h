#ifndef LAB1_H
#define LAB1_H

#include <stdio.h>
#include <stdlib.h>

#define NODE_CAPACITY 4

typedef struct node {
    struct node* next;
    int numElements;
    int elements[NODE_CAPACITY];
} node;

typedef struct unrolled_linked_list {
    node* head;
} unrolled_linked_list;

typedef struct unrolled_linked_list ull;

node* new_node();
ull* new_unrolled_list();
int findIndexByKey_unrolled_list(ull* list, int key);
int findValByIndex_unrolled_list(ull* list, int index);
void insertElement_unrolled_list(ull* list, int value);
void removeElement_unrolled_list(ull* list, int index);
int length_unrolled_list(ull* list);
int iterate_unrolled_list(ull* list, int index);
void print_unrolled_list(ull* list);
void delete_unrolled_list(ull* list);

#endif
