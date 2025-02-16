#include "stack_array.h" 

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100  

typedef struct Stack {
    int top;           
    int array[STACK_SIZE];
} Stack;

Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        perror("Ошибка выделения памяти для стека");
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    return stack;
}

//пуст ли стек
int isEmpty(Stack *stack) {
    return (stack->top == -1);
}

//полон ли стек
int isFull(Stack *stack) {
    return (stack->top == STACK_SIZE - 1);
}

//добавление элемента в стек
void push(Stack *stack, int data) {
    if (isFull(stack)) {
        printf("Стек полон.\n");
        return;
    }
    stack->array[++stack->top] = data;
    printf("Добавлен элемент: %d\n", data);
}

//удаление элемента из стека
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст.\n");
        return -1;
    }
    int popped = stack->array[stack->top--];
    printf("Удален элемент: %d\n", popped);
    return popped;
}

//просмотр верхнего элемента стека
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст.\n");
        return -1; 
    }
    return stack->array[stack->top];
}

//очистка стека
void clearStack(Stack *stack) {
    stack->top = -1;
    printf("Стек очищен.\n");
}

//освобождение памяти стека
void deleteStack(Stack *stack){
  free(stack);
  printf("Стек удален.\n");
}