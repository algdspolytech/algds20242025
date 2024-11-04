#pragma once
#include <stdlib.h>


typedef struct Node {
	int value;
	Node* next;
} Node;


typedef struct Stack {
	Node* head;
	size_t size;
};

Stack* init_stack(); // Функция создания стека

void push_stack(Stack* stack, int value); // Функция добавления элемента в стек
int pop_stack(Stack* stack); // Функция взятия элемента из стека

void free_stack(Stack* stack); // Функция очищения стека из памяти
