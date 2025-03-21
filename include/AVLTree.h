#include "BSTTreee.h"

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int getHeight(struct Node *node);

int Max(int a, int b);

struct Node* newNode(int key);

struct Node* rightRotate(struct Node* y);

struct Node* leftRotate(struct Node* x);

int getBalance(struct Node* node);

struct Node* insert(struct Node* node, int key);

struct Node* minValueNode(struct Node* node);

struct Node* deleteNode(struct Node* root, int key);

struct Node* search(struct Node* root, int key);

void preOrder(struct Node *root);
