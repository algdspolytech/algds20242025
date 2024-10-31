#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    unsigned dataSize;
    struct Node* xor_addr;
} Node;


Node* XOR(Node* a, Node* b);
Node* add(Node* head, char* data);
Node* find(Node* head, char* key);
Node* deleteNode(Node* head, Node* node);
Node* deleteByKey(Node* head, char* key);
void iterate(Node* head);
