#ifndef CODE_H
#define CODE_H

#include <stdio.h>

// Структура узла дерева
typedef struct Node {
    int value;            // Значение узла
    struct Node* left;    // Указатель на левое поддерево
    struct Node* right;   // Указатель на правое поддерево
} Node;

// Функции для работы с деревом
Node* create(int value);
void free(Node* node);
Node* read(FILE* file);
void Tree1(FILE* out, const Node* tree);
void Tree2(FILE* out, const Node* tree);

#endif // CODE_H