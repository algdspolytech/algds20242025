#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

#pragma warning(disable : 4996)

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->subtree_size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }

    root->subtree_size = 1 +
        (root->left ? root->left->subtree_size : 0) +
        (root->right ? root->right->subtree_size : 0);

    return root;
}

Node* findKthSmallest(Node* root, int k) {
    if (root == NULL) return NULL;

    int leftSize = (root->left ? root->left->subtree_size : 0);

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

void printElementsLessThanK(Node* root, int k, int* count) {
    if (root == NULL || *count >= k - 1) return;

    printElementsLessThanK(root->left, k, count);

    if (*count < k - 1) {
        printf("%d ", root->data);
        (*count)++;
    }

    printElementsLessThanK(root->right, k, count);
}

void processKthSmallest(Node* root, int k) {
    Node* kthNode = findKthSmallest(root, k);

    if (kthNode) {
        printf("K-й наименьший элемент: %d\n", kthNode->data);

        if (kthNode->data % 2 == 0) {
            printf("Элементы с номерами меньше K: ");
            int count = 0;
            printElementsLessThanK(root, k, &count);
            printf("\n");
        }
    }
    else {
        printf("K выходит за пределы количества элементов в дереве.\n");
    }
}
