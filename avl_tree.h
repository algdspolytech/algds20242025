#ifndef AVL_TREE_H
#define AVL_TREE_H

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree();
    void insert(int key);
    bool search(int key);
    void remove(int key);

private:
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, int key);
    AVLNode* remove(AVLNode* node, int key);
    AVLNode* minValueNode(AVLNode* node);
    bool search(AVLNode* node, int key);
};

#endif
