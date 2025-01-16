#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// Создание нового узла
Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

// Вставка узла в дерево
Node* insert(Node* root, int key) {
    if (root == NULL) return create_node(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    // Обновляем размер поддерева
    root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
    return root;
}

// Поиск узла по ключу
Node* find(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return find(root->left, key);
    }
    return find(root->right, key);
}

// Нахождение порядка текущего узла
int get_rank(Node* root, int key) {
    if (root == NULL) return 0;

    if (key < root->key) {
        return get_rank(root->left, key);
    }
    else if (key > root->key) {
        int left_size = root->left ? root->left->size : 0;
        return 1 + left_size + get_rank(root->right, key);
    }
    else {
        return (root->left ? root->left->size : 0) + 1;
    }
}

// Нахождение элемента, порядок которого на K меньше
Node* find_kth_predecessor(Node* root, int key, int k) {
    if (root == NULL) return NULL;

    // Определяем ранг текущего узла
    int rank = get_rank(root, key);
    int target_rank = rank - k;

    // Обходим дерево в порядке "inorder", чтобы найти нужный узел
    Node* current = root;
    Node* predecessor = NULL;
    int current_rank = 0;

    while (current != NULL) {
        int left_size = current->left ? current->left->size : 0;

        if (current_rank + left_size + 1 == target_rank) {
            return current;
        }
        else if (current_rank + left_size + 1 < target_rank) {
            current_rank += left_size + 1;
            current = current->right;
        }
        else {
            predecessor = current;
            current = current->left;
        }
    }

    return NULL;
}

// Освобождение памяти дерева
void free_tree(Node* root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}