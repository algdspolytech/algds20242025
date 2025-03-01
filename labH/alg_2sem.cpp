#include "avl_list.h"

// Функция для вычисления высоты узла
int height(Node* n) {
    return n ? n->height : 0;
}

// Функция для вычисления размера поддерева
int size(Node* n) {
    return n ? n->size : 0;
}

// Функция для вычисления баланса узла
int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Функция создания нового узла
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    node->size = 1;
    return node;
}

// Обновление высоты и размера узла
void updateNode(Node* node) {
    if (node) {
        node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
    }
}

// Правый поворот
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateNode(y);
    updateNode(x);
    return x;
}

// Левый поворот
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateNode(x);
    updateNode(y);
    return y;
}

// Вставка элемента
Node* insert(Node* node, int key, int position) {
    if (!node) return createNode(key);
    int leftSize = size(node->left);
    if (position <= leftSize)
        node->left = insert(node->left, key, position);
    else
        node->right = insert(node->right, key, position - leftSize - 1);
    updateNode(node);
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// Поиск по ключу
Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Поиск k-го элемента
Node* findKth(Node* root, int k) {
    if (!root) return NULL;
    int leftSize = size(root->left);
    if (k == leftSize) return root;
    if (k < leftSize) return findKth(root->left, k);
    return findKth(root->right, k - leftSize - 1);
}

// Обход дерева (вывод значений)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Слияние двух деревьев
Node* mergeTrees(Node* root1, Node* root2) {
    if (!root1) return root2;
    if (!root2) return root1;
    root2 = insert(root2, root1->key, size(root2));
    root2->left = mergeTrees(root1->left, root2->left);
    root2->right = mergeTrees(root1->right, root2->right);
    updateNode(root2);
    return root2;
}
