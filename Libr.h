#pragma once


// ќпредел€ем структуру узла
typedef struct Node {
    char* data;              // ”казатель на ASCIIZ строку
    struct Node* next;       // ”казатель на следующий узел
} Node;

Node* createNode(const char* data);
void append(Node** head, const char* data);
void split(Node* source, Node** fir, Node** sec);
Node* merge(Node* a, Node* b);
void mergeSort(Node** headRef);
void printList(Node* node);
void append_forward(Node** head, const char* data);