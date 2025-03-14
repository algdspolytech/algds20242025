#include "splay_tree.h"
#include <stdio.h>
#include <stdlib.h>


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


Node* rRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}


Node* lRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}


Node* splay(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        if (root->left == NULL) {
            return root;
        }


        if (data < root->left->data) {
            root->left->left = splay(root->left->left, data);
            root = rRotate(root);
        }

        else if (data > root->left->data) {
            root->left->right = splay(root->left->right, data);
            if (root->left->right != NULL) {
                root->left = lRotate(root->left);
            }
        }

        return (root->left == NULL) ? root : rRotate(root);
    } else {
        if (root->right == NULL) {
            return root;
        }


        if (data > root->right->data) {
            root->right->right = splay(root->right->right, data);
            root = lRotate(root);
        }

        else if (data < root->right->data) {
            root->right->left = splay(root->right->left, data);
            if (root->right->left != NULL) {
                root->right = rRotate(root->right);
            }
        }

        return (root->right == NULL) ? root : lRotate(root);
    }
}


Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    root = splay(root, data);

    if (root->data == data) {
        return root;
    }

    Node* newNode = createNode(data);
    if (data < root->data) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    return newNode;
}


Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    root = splay(root, data);

    if (root->data != data) {
        return root;
    }

    Node* temp;
    if (root->left == NULL) {
        temp = root->right;
    } else {
        temp = splay(root->left, data);
        temp->right = root->right;
    }

    free(root);
    return temp;
}


bool search(Node* root, int data) {
    root = splay(root, data);
    return root != NULL && root->data == data;
}


void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}