#include <stdio.h>
#include <stdlib.h>

#include "labA.h"

Node *createNode(int data) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Stack *createStack() {
    Stack *newStack = malloc(sizeof(Stack));
    if (newStack == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newStack->top = NULL;
    return newStack;
}


int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, int data) {
    Node *newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    Node *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->top->data;
}

void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст!\n");
        return;
    }
    Node *temp = stack->top;
    printf("Стек: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
