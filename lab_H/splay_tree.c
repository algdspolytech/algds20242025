#include <stdio.h>
#include <stdlib.h>
#include "splay_tree.h"
#pragma warning(disable:4996)

// Создание нового узла
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

// Функция splay – перемещает узел с ключом key к корню или, если его нет, последний посещённый узел
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Если ключ меньше корневого, то он находится в левом поддереве
    if (key < root->key) {
        if (root->left == NULL) return root;
        // Zig-Zig (левый левый случай)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (левый правый случай)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else { // Если ключ больше корневого, то он находится в правом поддереве
        if (root->right == NULL) return root;
        // Zag-Zig (правый левый случай)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        // Zag-Zag (правый правый случай)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Поиск: splay-операция перемещает искомый элемент (если он найден) к корню
Node* search(Node* root, int key) {
    return splay(root, key);
}

// Вставка: сначала выполняем splay, затем добавляем новый узел, если ключ отсутствует
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    root = splay(root, key);
    if (root->key == key)
        return root; // Дубликат – не вставляем
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

// Удаление: splay-операция поднимает узел с key к корню (если он существует)
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return NULL;
    root = splay(root, key);
    if (root->key != key)
        return root; // Элемент не найден
    Node* temp;
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    }
    else {
        temp = root;
        // Перемещаем максимум из левого поддерева в корень
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);
    return root;
}

// Обход дерева (inorder) для вывода элементов
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Освобождение памяти, выделенной под дерево
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}