#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

typedef struct {
    AVLNode* root;
} AVLTree;

void AVLTree_init(AVLTree* tree);
void AVLTree_insert(AVLTree* tree, int key);
int AVLTree_search(AVLTree* tree, int key);
void AVLTree_remove(AVLTree* tree, int key);
void AVLTree_free(AVLTree* tree);

#endif
