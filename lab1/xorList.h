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
void add(xorList*, const char*);
Node* find(xorList*, const char*);
void delByAd(xorList*, Node*);
void delByD(xorList*, const char*);
void iter(xorList*);
void freeList(xorList*);
