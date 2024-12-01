#ifndef BTREE_H
#define BTREE_H

typedef struct Node {
    int value;
    int count;  // количество узлов в поддереве
    struct Node* left;
    struct Node* right;
} Node;

// Создание нового узла
Node* createNode(int value);

// Добавление узла в дерево
Node* insert(Node* root, int value);

// Удаление узла из дерева
Node* delete(Node* root, int value);

// Обновление количества узлов
void updateCount(Node* node);

// Поиск минимального значения в дереве
Node* findMin(Node* node);

// Освобождение памяти
void freeTree(Node* root);

#endif // BTREE_H
