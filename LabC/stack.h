#pragma once
#include <stdlib.h>

typedef struct Node {
    int value;
    Node* next;
} Node;

typedef struct Stack {
    Node* head;
    size_t size;
} Stack;

Stack* initialize_stack(); // Функция создания стека
void push_to_stack(Stack* stack, int value); // Функция добавления элемента в стек
int pop_from_stack(Stack* stack); // Функция взятия элемента из стека
void release_stack(Stack* stack); // Функция очищения стека из памяти
