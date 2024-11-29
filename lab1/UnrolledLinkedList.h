#ifndef UNROLLEDLINKEDLIST_H
#define UNROLLEDLINKEDLIST_H

typedef struct Node {
  int *arr;
  struct Node *next;
  int capacity;
} node;

typedef struct UnrolledLinkedList {
  node *head;
} ull;

ull *init();
int *append(ull *list, int value);
int *get_element_by_index(ull *list, int index);
int *get_next_element(ull *list, int value);
int get_index_by_key(ull *list, int value);
int get_len(ull *list);
void delet_element(ull *list, int index);
void destroy(ull *list);

#endif