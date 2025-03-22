#ifndef BST_TREE_H
#define BST_TREE_H

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BSTree {
public:
    BSTree();
    void insert(int key);
    bool search(int key);
    void remove(int key);

private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int key);
    BSTNode* remove(BSTNode* node, int key);
    BSTNode* minValueNode(BSTNode* node);
    bool search(BSTNode* node, int key);
};

#endif
