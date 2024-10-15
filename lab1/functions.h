#pragma once
#include "functions.h"

typedef struct Node {
    char* str;
    struct Node* next;
} Node;

Node* createNode(const char* s);

void appendNode(Node** head, const char* s);

void freeList(Node* head);

size_t calculateTotalLength(Node* head);

char* concatenateStrings(Node* head);