#pragma once


typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct {
    Node* root; // корень дерева
    Node* nil;  // пустой элемент
} RBTree;

// инициализация дерева
void init_rbtree(RBTree* tree);

// поиск элемента
Node* search(const RBTree* tree, int data);

// вставка элемента
void insert(RBTree* tree, int data);

// удаление элемента
void delete(RBTree* tree, int data);

// освобождение памяти
void free_tree(RBTree* tree);

void print_tree(const RBTree* tree);

