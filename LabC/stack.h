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

Stack* initialize_stack(); // ������� �������� �����
void push_to_stack(Stack* stack, int value); // ������� ���������� �������� � ����
int pop_from_stack(Stack* stack); // ������� ������ �������� �� �����
void release_stack(Stack* stack); // ������� �������� ����� �� ������
