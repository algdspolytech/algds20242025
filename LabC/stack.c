#include <stdlib.h>
#include "stack.h"

static Node* create_new_node(Node* nextNode, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = nextNode;
    newNode->value = value;

    return newNode;
}

static void release_node(Node* node) {
    free(node);
}

Stack* initialize_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->size = 0;

    return stack;
}

void release_stack(Stack* stack) {
    Node* currentNode = stack->head;
    while (currentNode != NULL) {
        Node* tempNode = currentNode;
        currentNode = currentNode->next;
        release_node(tempNode);
    }

    free(stack);
}

void push_to_stack(Stack* stack, int value) {
    Node* newNode = create_new_node(stack->head, value);
    stack->head = newNode;

    stack->size++;
}

int pop_from_stack(Stack* stack) {
    if (stack->head == NULL) return 0;

    int value = stack->head->value;

    Node* tempNode = stack->head;
    stack->head = stack->head->next;
    release_node(tempNode);

    stack->size--;

    return value;
}
