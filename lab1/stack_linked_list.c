#include "stack_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

//инициализация стека
Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        perror("Ошибка выделения памяти для стека");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

//пуст ли стек
int isEmpty(Stack *stack) {
    return (stack->top == NULL);
}

//добавление элемента в стек
void push(Stack *stack, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Ошибка выделения памяти для нового узла");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    printf("Добавлен элемент: %d\n", data);
}

//удаление элемента из стека
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст.\n");
        return -1; 
    }

    Node *temp = stack->top;
    int popped = temp->data;
    stack->top = temp->next;
    free(temp);
    printf("Удален элемент: %d\n", popped);
    return popped;
}

//просмотр верхнего элемента стека
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст.\n");
        return -1;
    }
    return stack->top->data;
}

//очистка стека и освобождения памяти
void deleteStack(Stack *stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
    printf("Стек удален.\n");
}