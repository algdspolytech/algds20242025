#include "LabH.h"

// Вспомогательная функция для поиска узла по ключу.
Node* find(Node* node, int key) {
    if (!node) return nullptr;
    if (key < node->key) return find(node->left, key);
    if (key > node->key) return find(node->right, key);
    return node;
}

// Получить размер поддерева.
int get_size(Node* node) {
    return node ? node->size : 0;
}

// Обновить размер узла.
void update_size(Node* node) {
    if (node) {
        node->size = get_size(node->left) + get_size(node->right) + 1;
    }
}

// Правый поворот.
Node* rotate_right(Node* root) {
    Node* new_root = root->left;
    if (!new_root) return root;

    root->left = new_root->right;
    new_root->right = root;

    new_root->size = root->size;
    update_size(root);
    update_size(new_root);

    return new_root;
}

// Левый поворот.
Node* rotate_left(Node* root) {
    Node* new_root = root->right;
    if (!new_root) return root;

    root->right = new_root->left;
    new_root->left = root;

    new_root->size = root->size;
    update_size(root);
    update_size(new_root);

    return new_root;
}

// Вставка узла в корень.
Node* insert_at_root(Node* root, Node* node) {
    if (!root) return node;

    if (node->key < root->key) {
        root->left = insert_at_root(root->left, node);
        return rotate_right(root);
    } else {
        root->right = insert_at_root(root->right, node);
        return rotate_left(root);
    }
}

// Обычная вставка узла.
Node* insert(Node* root, Node* node) {
    if (!root) return node;

    if (rand() % (root->size + 1) == 0)
        return insert_at_root(root, node);

    if (node->key < root->key)
        root->left = insert(root->left, node);
    else
        root->right = insert(root->right, node);

    update_size(root);
    return root;
}

// Объединение двух деревьев.
Node* merge(Node* left_tree, Node* right_tree) {
    if (!left_tree) return right_tree;
    if (!right_tree) return left_tree;

    if (rand() % (left_tree->size + right_tree->size) < left_tree->size) {
        left_tree->right = merge(left_tree->right, right_tree);
        update_size(left_tree);
        return left_tree;
    } else {
        right_tree->left = merge(left_tree, right_tree->left);
        update_size(right_tree);
        return right_tree;
    }
}

// Удаление узла по ключу.
Node* delete_node(Node* root, int key) {
    if (!root) return nullptr;

    if (key == root->key) {
        Node* merged_subtree = merge(root->left, root->right);
        delete root;
        return merged_subtree;
    }

    if (key < root->key)
        root->left = delete_node(root->left, key);
    else
        root->right = delete_node(root->right, key);

    update_size(root);
    return root;
}

// Реализация функций интерфейса.

double get(Node* tree, int key) {
    Node* found_node = find(tree, key);
    return found_node ? found_node->data : 0.0;
}

Node* add(Node* tree, int key, double data) {
    return insert(tree, new Node(key, data));
}

Node* remove(Node* tree, int key) {
    return delete_node(tree, key);
}

int height(Node* node) {
    if (!node) return 0;
    return std::max(height(node->left), height(node->right)) + 1;
}

int size(Node* tree) {
    return get_size(tree);
}
