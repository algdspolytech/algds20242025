#ifndef BST_TREE_H
#define BST_TREE_H

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct {
    BSTNode* root;
} BSTree;

void BSTree_init(BSTree* tree);
void BSTree_insert(BSTree* tree, int key);
int BSTree_search(BSTree* tree, int key);
void BSTree_remove(BSTree* tree, int key);
void BSTree_free(BSTree* tree);

#endif
