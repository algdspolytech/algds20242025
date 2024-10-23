#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для создания нового узла
Node *create_node(const char *str) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (!new_node)
    return NULL; // проверка malloc
  new_node->data = strdup(str);
  new_node->next = NULL;
  return new_node;
}

// Функция для добавления элемента в начало списка
void push_front(Node **head, const char *str) {
  Node *new_node = create_node(str);
  new_node->next = *head;
  *head = new_node;
}

// Функция для добавления элемента в конец списка
void push_back(Node **head, const char *str) {
  Node *new_node = create_node(str);
  if (*head == NULL) {
    *head = new_node;
  } else {
    Node *temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_node;
  }
}

// Функция для удаления элемента из начала списка
void pop_front(Node **head) {
  if (*head == NULL)
    return;
  Node *temp = *head;
  *head = (*head)->next;
  free(temp->data);
  free(temp);
}

// Функция для удаления элемента из конца списка
void pop_back(Node **head) {
  if (*head == NULL)
    return;
  if ((*head)->next == NULL) {
    free((*head)->data);
    free(*head);
    *head = NULL;
    return;
  }
  Node *temp = *head;
  while (temp->next->next != NULL) {
    temp = temp->next;
  }
  free(temp->next->data);
  free(temp->next);
  temp->next = NULL;
}

// Функция для разбиения списка на две половины
void split_list(Node *source, Node **front, Node **back) {
  Node *slow = source;
  Node *fast = source->next;

  // Используем быстрый и медленный указатели для нахождения середины списка
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  *front = source;
  *back = slow->next;
  slow->next = NULL;
}

// Функция для слияния двух отсортированных списков
Node *sorted_merge(Node *a, Node *b) {
  if (a == NULL)
    return b;
  if (b == NULL)
    return a;

  Node *result = NULL;
  if (strcmp(a->data, b->data) <= 0) {
    result = a;
    result->next = sorted_merge(a->next, b);
  } else {
    result = b;
    result->next = sorted_merge(a, b->next);
  }
  return result;
}

// Рекурсивная функция сортировки слиянием
void merge_sort(Node **head_ref) {
  if (*head_ref == NULL || (*head_ref)->next == NULL) {
    return;
  }

  Node *head = *head_ref;
  Node *a = NULL;
  Node *b = NULL;

  // Разбиваем список на две половины
  split_list(head, &a, &b);

  // Рекурсивно сортируем каждую половину
  merge_sort(&a);
  merge_sort(&b);

  // Сливаем две отсортированные половины
  *head_ref = sorted_merge(a, b);
}

// Функция для вывода списка
void print_list(Node *head) {
  while (head != NULL) {
    printf("%s -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}

// Очистка всего списка
void free_list(Node **head_ref) {
  Node *current = *head_ref;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current->data);
    free(current);
    current = next;
  }

  *head_ref = NULL;
}
