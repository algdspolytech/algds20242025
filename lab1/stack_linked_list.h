#pragma once

typedef struct Node {
    int data;
    struct Node *next;
} Node;


typedef struct Stack {
    Node *top;
} Stack;


Stack* createStack();
int isEmpty(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
void deleteStack(Stack *stack);
