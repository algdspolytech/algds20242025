#ifndef TREE_H
#define TREE_H

typedef struct Node {
    int value;             
    int count;        
    struct Node* left;      
    struct Node* right;     
    struct Node* parent;
} Node;

Node* createNode(int value, Node* parent);

void insert(Node** root, int value);

void delete(Node** root, int value);

Node* findMin(Node* node);

void inorderTraversal(Node* node);

#endif // TREE_H
