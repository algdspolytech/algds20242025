#include "tree.h"

// Создание нового узла
Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    node->value = value;
    node->balance = 0;
    node->left = node->right = NULL;
    return node;
}

// Вставка узла в дерево
Node* insert(Node* root, int value) {
    if (!root) return createNode(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value) // Добавляем проверку, чтобы не вставлять дубликаты
        root->right = insert(root->right, value);
    return root;
}

// Вычисление высоты поддерева
int getHeight(Node* node) {
    if (!node) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Обновление разности высот в узлах
int updateBalances(Node* root) {
    if (!root) return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    root->balance = leftHeight - rightHeight;
    updateBalances(root->left);
    updateBalances(root->right);
    return root->balance;
}

// Вывод дерева
void printTree(Node* root, int level) {
    if (!root) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    printf("%d (%d)\n", root->value, root->balance);
    printTree(root->left, level + 1);
}

// Освобождение памяти
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}