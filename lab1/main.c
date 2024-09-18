#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;             
    struct Node* next;    
    struct Node* prev;    
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

int main() {
    Node* head = NULL;
    return 0;
}