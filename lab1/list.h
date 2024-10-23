#ifndef LIST_H
#define LIST_H

// Структура узла списка
typedef struct Node {
  char *data;
  struct Node *next;
} Node;

Node *create_node(const char *str);
void free_list(Node **head_ref);

void push_front(Node **head, const char *str);
void push_back(Node **head, const char *str);

void pop_front(Node **head);
void pop_back(Node **head);

void split_list(Node *source, Node **front, Node **back);
Node *sorted_merge(Node *a, Node *b);
void merge_sort(Node **head_ref);

void print_list(Node *head);

#endif
