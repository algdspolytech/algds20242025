#ifndef structs_h
#define structs_h

#include <stdio.h>

// Структура узла дерева
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

#endif