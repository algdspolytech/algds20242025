#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node {
    const char* data;
    struct Node* link;
} Node;

typedef struct xorList {
    Node* head;
    Node* tail;
} xorList;

Node* xor (Node*, Node*);
Node* createNode(const char*);

xorList* createList();
xorList* add(xorList*, const char*);
Node* find(xorList*, const char*);
xorList* delByAd(xorList*, Node*);
xorList* delByD(xorList*, const char*);
void iter(xorList*);
xorList* freeList(xorList*);
