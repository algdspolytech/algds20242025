#pragma once
#define STACK_SIZE 100 

typedef struct Stack {
    int top;          
    int array[STACK_SIZE];
} Stack;

Stack* createStack();
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
void clearStack(Stack *stack);
void deleteStack(Stack *stack);