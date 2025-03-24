#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

// Функция создания нового узла
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Правый поворот
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Левый поворот
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Операция Splay (перемещение ключа к корню)
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Ключ в левом поддереве
    if (key < root->key) {
        if (root->left == NULL) return root;

        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }

    // Ключ в правом поддереве
    else {
        if (root->right == NULL) return root;

        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Функция поиска (и сплэйинга найденного элемента)
Node* search(Node* root, int key) {
    return splay(root, key);
}

// Вставка узла в Splay Tree
Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);

    root = splay(root, key);

    if (root->key == key) return root; // Ключ уже есть, не вставляем дубликаты

    Node* new_node = newNode(key);
    if (key < root->key) {
        new_node->right = root;
        new_node->left = root->left;
        root->left = NULL;
    }
    else {
        new_node->left = root;
        new_node->right = root->right;
        root->right = NULL;
    }
    return new_node;
}

// Удаление узла из Splay Tree
Node* delete(Node* root, int key) {
    if (root == NULL) return NULL;

    root = splay(root, key);

    if (root->key != key) return root; // Ключ не найден

    Node* newRoot;
    if (root->left == NULL)
        newRoot = root->right;
    else {
        newRoot = splay(root->left, key);
        newRoot->right = root->right;
    }
    free(root);
    return newRoot;
}

// Обход дерева (симметричный)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}