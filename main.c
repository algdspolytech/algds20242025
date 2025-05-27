#include "main.h"

// Создание нового узла
Node* createNode(int x, int c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->c = c;
    newNode->max_c = c; 
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Обновление max_c для узла
void updateMax(Node* node) {
    if (node == NULL)
        return;
    node->max_c = node->c;
    if (node->left != NULL && node->left->max_c > node->max_c)
        node->max_c = node->left->max_c;
    if (node->right != NULL && node->right->max_c > node->max_c)
        node->max_c = node->right->max_c;
}

// Слияние двух деревьев
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->c > right->c) {
        left->right = merge(left->right, right);
        updateMax(left); 
        return left;
    }
    else {
        right->left = merge(left, right->left);
        updateMax(right); 
        return right;
    }
}

// Разделение дерева по ключу x
void split(Node* root, int x, Node** left, Node** right) {
    if (!root) {
        *left = NULL;
        *right = NULL;
        return;
    }

    if (root->x < x) {
        split(root->right, x, &root->right, right);
        *left = root;
        updateMax(root); 
    }
    else {
        split(root->left, x, left, &root->left);
        *right = root;
        updateMax(root); 
    }
}

// Вставка нового элемента в дерево
Node* insert(Node* root, int x, int c) {
    Node* newNode = createNode(x, c);
    Node* left = NULL;
    Node* right = NULL;
    split(root, x, &left, &right);
    Node* newRoot = merge(merge(left, newNode), right);
    updateMax(newRoot); 
    return newRoot;
}

// Поиск максимума на интервале [x, y)
int queryMax(Node* root, int x, int y) {
    Node* left = NULL;
    Node* middle = NULL;
    Node* right = NULL;
    split(root, x, &left, &middle);
    split(middle, y, &middle, &right);
    int max_c = middle ? middle->max_c : -1;
    root = merge(merge(left, middle), right);
    return max_c;
}

// Освобождение памяти, занятой деревом
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}