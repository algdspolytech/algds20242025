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

ArrayStack *createArrayStack(int capacity) {
    ArrayStack *newStack = malloc(sizeof(ArrayStack));
    if (newStack == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newStack->data = malloc(capacity * sizeof(int));
    if (newStack->data == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newStack->top = -1;
    newStack->capacity = capacity;
    return newStack;
}

int isEmptyArrayStack(ArrayStack *stack) {
    return stack->top == -1;
}

void pushArrayStack(ArrayStack *stack, int data) {
    if (stack->top == stack->capacity - 1) {
        printf("Стек переполнен!\n");
        return;
    }
    stack->top++;
    stack->data[stack->top] = data;
}

int popArrayStack(ArrayStack *stack) {
    if (isEmptyArrayStack(stack)) {
        return -1;
    }
    int data = stack->data[stack->top];
    stack->top--;
    return data;
}

int peekArrayStack(ArrayStack *stack) {
    if (isEmptyArrayStack(stack)) {
        return -1;
    }
    return stack->data[stack->top];
}

void printArrayStack(ArrayStack *stack) {
    if (isEmptyArrayStack(stack)) {
        printf("Стек пуст!\n");
        return;
    }
    printf("Стек: ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}
