#ifndef LABA_H
#define LABA_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

typedef struct {
    int *data;
    int top;
    int capacity;
} ArrayStack;

Node *createNode(int data);

Stack *createStack();

int isEmpty(Stack *stack);

void push(Stack *stack, int data);

int pop(Stack *stack);

int peek(Stack *stack);

void printStack(Stack *stack);

ArrayStack *createArrayStack(int capacity);

int isEmptyArrayStack(ArrayStack *stack);

int popArrayStack(ArrayStack *stack);

void pushArrayStack(ArrayStack *stack, int data);

int peekArrayStack(ArrayStack *stack);

void printArrayStack(ArrayStack *stack);


#endif //LABA_H
