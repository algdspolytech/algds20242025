#include "Treap.h"

Node* createNode(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = rand();
    return new_node;
}

void split(Node* root, int key, Node** left, Node** right) {
    if (!root) {
        *left = NULL;
        *right = NULL;
    }
    else if (root->key <= key) {
        split(root->right, key, &root->right, right);
        *left = root;
    }
    else {
        split(root->left, key, left, &root->left);
        *right = root;
    }
}

Node* insert(Node* root, Node* newNode) {
    if (!root) {
        return newNode;
    }
    if (newNode->data > root->data) {
        split(root, newNode->key, &newNode->left, &newNode->right);
        return newNode;
    }
    if (newNode->key < root->key) {
        root->left = insert(root->left, newNode);
    }
    else {
        root->right = insert(root->right, newNode);
    }

    return root;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->data > right->data) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

Node* delete(Node* root, int key) {
    if (!root) {
        return NULL;
    }

    if (root->key == key) {
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    }
    else {
        root->right = delete(root->right, key);
    }

    return root;
}

Node* search(Node* root, int key) {
    if (!root || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

int height(Node* root) {
    if (!root) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    else {
        return rightHeight + 1;
    }
}

int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int generateRandomKey() {
    return rand() % 100; // Ключи от 0 до 99
}
