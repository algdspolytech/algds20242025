#pragma once
#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void push(Stack* stack, char value);
char pop(Stack* stack);
char peek(Stack* stack);
int precedence(char op);
void infixToPostfix(char* infix, char* postfix);