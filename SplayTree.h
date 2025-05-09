#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Node {
        int key;
        struct Node* left, * right;
    } Node;

    Node* newNode(int key);
    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);
    Node* splay(Node* root, int key);
    Node* search(Node* root, int key);
    Node* insert(Node* root, int key);
    Node* deleteNode(Node* root, int key);
    void inorder(Node* root);
    void freeTree(Node* root);

#ifdef __cplusplus
}
#endif

#endif // SPLAY_TREE_H