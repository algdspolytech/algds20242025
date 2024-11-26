#ifndef BST_H
#define BST_H

// Определение структуры для узла дерева
typedef struct Node {
    int key;
    int size;
    struct Node* left;
    struct Node* right;
} Node;

// Прототипы функций
Node* createNode(int key);
void updateSize(Node* node);
Node* insert(Node* root, int key);
Node* findKthSmallest(Node* root, int k);
int findOrderOfElement(Node* root, int key);
Node* findElementMinusK(Node* root, int key, int k);
void inorderPrint(Node* root);

#endif // BST_H
