#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int count;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

int getCount(Node* node) {
    return (node == NULL) ? 0 : node->count;
}

void updateCount(Node* node) {
    while (node != NULL) {
        node->count = 1 + getCount(node->left) + getCount(node->right);
        node = node->parent;
    }
}

Node* insertNode(Node* root, int data) {
    Node* newNode = createNode(data);

    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (getCount(current->left) <= getCount(current->right)) {
            if (data < current->data) {
                current = current->left;
            } else {
                if(current->left != NULL && current->right != NULL && current->data == data) {
                    printf("Узел с таким значением уже существует.\n");
                    free(newNode);
                    return root;
                }
                current = current->left;
            }
        } else {
            if (data > current->data) {
                current = current->right;
            } else {
                if(current->left != NULL && current->right != NULL && current->data == data) {
                    printf("Узел с таким значением уже существует.\n");
                    free(newNode);
                    return root;
                }
                current = current->right;
            }
        }
    }

    newNode->parent = parent;

    if (getCount(parent->left) <= getCount(parent->right)) {
        if (data < parent->data) {
            parent->left = newNode;
        }
        else{
            parent->left = newNode;
        }
    }
    else {
        if (data > parent->data) {
            parent->right = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

    updateCount(parent);
    return root;
}


Node* findMin(Node* node) {
    if (node == NULL) return NULL;
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int data) {
    Node* current = root;
    Node* parent = NULL;

    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Узел со значением %d не найден.\n", data);
        return root;
    }

    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            free(current);
            return NULL;
        }

        if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        updateCount(parent);
        free(current);
    }
    else if (current->left == NULL || current->right == NULL) {
        Node* child = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            child->parent = NULL;
            free(current);
            return child;
        }

        if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        updateCount(parent);
        free(current);
    }
    else {
        Node* successor = findMin(current->right);
        current->data = successor->data;
        root = deleteNode(root, successor->data);
    }

    return root;
}


void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d (%d) ", root->data, root->count);
        inorderTraversal(root->right);
    }
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
