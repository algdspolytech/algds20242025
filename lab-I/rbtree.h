#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } NodeColor;

typedef struct RBTreeNode {
    int data;
    NodeColor color;
    struct RBTreeNode* left, * right, * parent;
} RBTreeNode;

typedef struct {
    RBTreeNode* root;
    RBTreeNode* nil; // Sentinel node
} RBTree;

// ������������� ������
void initRBTree(RBTree* tree);

// ������� ��������
void insertRBTree(RBTree* tree, int data);

// �������� ��������
void deleteRBTree(RBTree* tree, int data);

// ����� ��������
RBTreeNode* searchRBTree(RBTree* tree, int data);

// ������������ ������
void freeRBTree(RBTree* tree);

// ��������������� �������
void leftRotate(RBTree* tree, RBTreeNode* x);
void rightRotate(RBTree* tree, RBTreeNode* y);
void insertFixup(RBTree* tree, RBTreeNode* z);
void deleteFixup(RBTree* tree, RBTreeNode* x);
RBTreeNode* minimum(RBTree* tree, RBTreeNode* node);
void transplant(RBTree* tree, RBTreeNode* u, RBTreeNode* v);

#endif // RBTREE_H