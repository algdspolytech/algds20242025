#ifndef LIST_H
#define LIST_H

typedef struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(const char* data);
void append(Node** head, const char* data);
Node* merge(Node* left, Node* right);
void split(Node* source, Node** front, Node** back);
void mergeSort(Node** headRef);
void printList(Node* node);
void freeList(Node* node);

#endif