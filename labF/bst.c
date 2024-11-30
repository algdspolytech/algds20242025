#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// ������� ��� �������� ������ ����
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ���������� ������� ���������
void updateSize(Node* node) {
    if (node) {
        int leftSize = (node->left) ? node->left->size : 0;
        int rightSize = (node->right) ? node->right->size : 0;
        node->size = 1 + leftSize + rightSize;
    }
}

// ������� �������� � ������
Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    updateSize(root);
    return root;
}

// ����� ���� �� ������� (k-� ���������� �������)
Node* findKthSmallest(Node* root, int k) {
    if (root == NULL) return NULL;

    int leftSize = (root->left) ? root->left->size : 0;

    if (k == leftSize + 1) {
        return root;
    }
    else if (k <= leftSize) {
        return findKthSmallest(root->left, k);
    }
    else {
        return findKthSmallest(root->right, k - leftSize - 1);
    }
}

// ������� ��� ������ ���� � ������ ������ � ���������� ��� �������
int findOrderOfElement(Node* root, int key) {
    int order = 0;
    Node* current = root;

    while (current != NULL) {
        int leftSize = (current->left) ? current->left->size : 0;

        if (key == current->key) {
            order += leftSize + 1;
            return order;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            order += leftSize + 1;
            current = current->right;
        }
    }
    return -1;
}

// ������� ��� ������ ��������, ������� �������� ������ �� K
Node* findElementMinusK(Node* root, int key, int k) {
    int currentOrder = findOrderOfElement(root, key);

    if (currentOrder == -1 || currentOrder <= k) {
        return NULL;
    }
    return findKthSmallest(root, currentOrder - k);
}

// ������� ��� ������ ������ �� ������� (in-order)
void inorderPrint(Node* root) {
    if (root != NULL) {
        inorderPrint(root->left);
        printf("%d (size: %d) ", root->key, root->size);
        inorderPrint(root->right);
    }
}