#include "UnrolledLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

ull *init() {
  ull *new_list = malloc(sizeof(ull));
  node *new_node = malloc(sizeof(node));
  int *arr = calloc(4, sizeof(int));
  new_node->arr = arr;
  new_node->capacity = 0;
  new_node->next = NULL;
  new_list->head = new_node;

  return new_list;
}

int *append(ull *list, int value) {
  node *current = list->head;
  int *res;
  while (current->next) {
    current = current->next;
  }
  if (current->capacity == 4) {
    node *new_node = malloc(sizeof(node));
    int *arr = calloc(4, sizeof(int));
    arr[0] = value;
    new_node->arr = arr;
    new_node->capacity = 1;
    new_node->next = NULL;
    current->next = new_node;
    res = arr;
  } else {
    current->arr[current->capacity] = value;
    res = current->arr + current->capacity;
    current->capacity++;
  }
  return res;
}

int *get_element_by_index(ull *list, int index) {
  node *current = list->head;
  int *res = NULL, len = get_len(list);
  if (len > index) {
    for (int i = 0; i < (int)(index / 4); i++) {
      current = current->next;
    }
    res = &(current->arr[index % 4]);
  }
  return res;
}

int get_index_by_key(ull *list, int value) {
  node *current = list->head;
  int counter = 0, res = -1, flag = 0;
  while (!flag) {
    for (int i = 0; i < current->capacity; i++) {
      if (current->arr[i] == value) {
        res = counter;
        flag = 1;
      }
      counter++;
    }
    if (current->next) {
      current = current->next;
    } else {
      flag = 1;
    }
  }
  return res;
}

int get_len(ull *list) {
  node *current = list->head;
  int len = 0, flag = 0;
  while (!flag) {
    len += current->capacity;
    if (current->next) {
      current = current->next;
    } else {
      flag = 1;
    }
  }
  return len;
}

int *get_next_element(ull *list, int value) {
  int index = get_index_by_key(list, value);
  int *res = NULL;
  if (index != -1) {
    res = get_element_by_index(list, index + 1);
  }
  return res;
}

void delet_element(ull *list, int index) {
  node *current = list->head;
  node *previous;
  int len = get_len(list);
  if (len - 1 >= index) {
    for (int i = 0; i < (int)(index / 4); i++) {
      previous = current;
      current = current->next;
    }
    if (len - 1 == index) {
      current->capacity--;
    } else {
      while (get_element_by_index(list, index + 1)) {
        current->arr[index % 4] = *(get_element_by_index(list, index + 1));
        if (index % 4 == 3) {
          previous = current;
          current = current->next;
        }
        index++;
      }
      current->capacity--;
      if (current->capacity == 0) {
        previous->next = NULL;
        free(current->arr);
        free(current);
      }
    }
  }
}

void destroy(ull *list) {
  node *current = list->head;
  while (current->next) {
    node *previous;
    previous = current;
    current = current->next;
    free(previous->arr);
    free(previous);
  }
  free(current->arr);
  free(current);
  free(list);
}
