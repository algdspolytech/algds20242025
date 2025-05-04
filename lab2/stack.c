#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *init() {
  Stack *stack = malloc(sizeof(Stack));
  stack->capacity = 0;
  stack->node = NULL;
  return stack;
}

void push(Stack *stack, double _value) {
  Node *new_node = malloc(sizeof(Node));
  new_node->index = stack->capacity;
  new_node->value = _value;
  new_node->next = stack->node;
  stack->capacity++;
  stack->node = new_node;
}

int pop(Stack *stack, int _index) {
  double res = EOF;
  if (stack->capacity > 0) {
    if (_index >= 0) {
      Node *temp = stack->node;
      Node *prev = NULL;
      while (temp->index != _index) {
        temp->index--;
        prev = temp;
        temp = temp->next;
      }
      res = temp->value;
      if (prev != NULL) {
        prev->next = temp->next;
      } else {
        stack->node = temp->next;
      }
      free(temp);
    } else {
      Node *temp = stack->node;
      Node *prev = NULL;
      for (int i = 1; i < -_index; i++) {
        temp->index--;
        prev = temp;
        temp = temp->next;
      }
      res = temp->value;
      if (prev != NULL) {
        prev->next = temp->next;
      } else {
        stack->node = temp->next;
      }
      free(temp);
    }
    stack->capacity--;
  }
  return res;
}

void destroy(Stack *stack) {
  while (stack->node != NULL) {
    Node *temp = stack->node;
    stack->node = temp->next;
    free(temp);
  }
  free(stack);
}
