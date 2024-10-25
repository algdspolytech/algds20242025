#ifndef LABA_H
#define LABA_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

Node *createNode(int data);

Stack *createStack();

int isEmpty(Stack *stack);

void push(Stack *stack, int data);

int pop(Stack *stack);

int peek(Stack *stack);

void printStack(Stack *stack);

#endif //LABA_H
