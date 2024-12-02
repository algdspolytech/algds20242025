#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    int data;
} typedef TreeNode;

struct Tree{
    TreeNode* root;
} typedef Tree;

TreeNode* initNode(int data){
    TreeNode* node=(TreeNode*)malloc(sizeof(TreeNode));
    if(!node)
        return NULL;
    node->left=NULL;
    node->right=NULL;
    node->data=data;
    return node;
}

bool addNode(TreeNode** root, int data){
    if (!(*root)){
        *root = initNode(data);
        return true;
    }
    if ((*root)->data > data){
        return addNode(&(*root)->left, data);
    }
    else{
        return addNode(&(*root)->right, data);
    }
}
void freeTree(TreeNode* root){
    if(!root)  return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

bool deleteSubtree(TreeNode** root, int data){
    if (!(*root)){
        return false;
    }
    if((*root)->data==data){
        freeTree(*root);
        *root=NULL;
        return true;
    }
    else if ((*root)->data>data) {
        return deleteSubtree(&((*root)->left), data);
    }
    else{
        return deleteSubtree(&((*root)->right), data);
    }
}

void printTree(const TreeNode* root){
    if(!root) return;
    printf("%d ", root->data);
    printTree(root->left);
    printTree(root->right);
}
