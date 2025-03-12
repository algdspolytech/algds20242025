#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // только в AVL
} Node;

// ======= функции для работы с BST-деревом =======

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* insertBST(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);
    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteBST(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteBST(root->left, key);
    else if (key > root->key)
        root->right = deleteBST(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteBST(root->right, temp->key);
    }
    return root;
}

// ======= функции для работы с AVL-деревом =======

int height(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    return y;
}


Node* insertAVL(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
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


Node* deleteAVL(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteAVL(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL) return root;
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void benchmark() {
    Node* bst = NULL;
    Node* avl = NULL;
    int n = 100000;
    clock_t start, end;

    start = clock();
    for (int i = 0; i < n; i++)
        bst = insertBST(bst, rand());
    end = clock();
    printf("BST Insert Time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < n; i++)
        avl = insertAVL(avl, rand());
    end = clock();
    printf("AVL Insert Time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < n; i++)
        bst = deleteBST(bst, rand());
    end = clock();
    printf("BST Delete Time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < n; i++)
        avl = deleteAVL(avl, rand());
    end = clock();
    printf("AVL Delete Time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);
}


