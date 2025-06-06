#ifndef STACK_H
#define STACK_H

typedef struct Node {
  int value;
  int index;
  struct Node *next;
} Node;

typedef struct Stack {
  int capacity;
  Node *node;
} Stack;

Stack *init();
void push(Stack *stack, double value);
int pop(Stack *stack, int index);
void destroy(Stack *stack);
void print_stack(Stack *stack);

#endif