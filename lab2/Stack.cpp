#include <stdlib.h>
#include "Stack.h"


static Node* create_node(Node* next, int value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->next = next;
	new_node->value = value;

	return new_node;
}

static void free_node(Node* node) {
	free(node);
}

 Stack* init_stack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->head = NULL;
	stack->size = 0;

	return stack;
}

 void free_stack(Stack* stack) {
	Node* node = stack->head;
	while (node != NULL) {
		Node* f_node = node;
		node = node->next;
		free_node(f_node);
	}

	free(stack);
}

 void push_stack(Stack* stack, int value) {
	Node* new_node = create_node(stack->head, value);
	stack->head = new_node;

	stack->size++;
}

 int pop_stack(Stack* stack) {
	if (stack->head == NULL) return 0;
	
	int value = stack->head->value;

	Node* f_node = stack->head;
	stack->head = stack->head->next;
	free_node(f_node);

	stack->size--;

	return value;
}