#include <iostream>
#include "RandomBinaryTree.h"


Node* find(Node* node, int key) {
    if (!node)
        return NULL;

    if (node->key > key)
        return find(node->left, key);
    else if (node->key < key)
        return find(node->right, key);

    return node;
}

int get_size(Node* node) {
    if (!node)
        return 0;
    return node->size;
}

void fix_size(Node* node) {
    if (!node)
        return;

    node->size = get_size(node->left) + get_size(node->right) + 1;
}

Node* rotate_right(Node* node) {
    Node* child = node->left;
    if (!child)
        return node;

    node->left = child->right;
    child->right = node;

    child->size = node->size;
    fix_size(node);
    fix_size(child);

    return child;
}

Node* rotate_left(Node* node) {
    Node* child = node->right;
    if (!child)
        return node;

    node->right = child->left;
    child->left = node;

    child->size = node->size;
    fix_size(node);
    fix_size(child);

    return child;
}

Node* insert_root(Node* root, Node* node) {
    if (!root) return node;

    if (root->key < node->key) {
        root->right = insert_root(root->right, node);
        return rotate_left(root);
    }
    else {
        root->left = insert_root(root->left, node);
        return rotate_right(root);
    }
}

Node* insert(Node* root, Node* node) {
    if (!root) return node;

    if (rand() % (root->size + 1) == 0)
        return insert_root(root, node);

    if (root->key < node->key)
        root->right = insert(root->right, node);
    else
        root->left = insert(root->left, node);
    fix_size(root);

    return root;
}


Node* join(Node* node1, Node* node2) // объединение двух деревьев
{
    if (!node1) return node2;
    if (!node2) return node1;

    if (rand() % (node1->size + node2->size) < node1->size)
    {
        node1->right = join(node1->right, node2);
        fix_size(node1);
        return node1;
    }
    else
    {
        node2->left = join(node1, node2->left);
        fix_size(node2);
        return node2;
    }
}

Node* _remove(Node* p, int k) // удаление из дерева p первого найденного узла с ключом k 
{
    if (!p) return p;

    if (p->key == k)
    {
        Node* q = join(p->left, p->right);
        delete p;
        fix_size(q);
        return q;
    }
    else if (k < p->key) {
        p->left = _remove(p->left, k);
        fix_size(p);
    }
    else {
        p->right = _remove(p->right, k);
        fix_size(p);
    }
    return p;
}

// Возвращает значение по ключу
double get(Node* tree, int key) {
    Node* node = find(tree, key);
    if (!node)
        return 0;
    return node->data;
}

// Добавляет узел 
Node* add(Node* tree, int key, double data) {
    return insert(tree, new Node(key, data));
}

// Удаляет узел
Node* remove(Node* tree, int key) {
    return _remove(tree, key);
}

// Высота дерева
int height(Node* node) {
    if (!node)
        return 0;
    return std::max(height(node->left), height(node->right)) + 1;
}

// Размер дерева
int size(Node* tree) {
    return get_size(tree);
}