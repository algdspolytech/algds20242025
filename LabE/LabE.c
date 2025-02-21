#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Tree{
    Node* root;
};

Node* initNode(int data){
    Node* node=(Node*)malloc(sizeof(Node));
    if (!node) { return NULL; }

    node->right = NULL;
    node->left=NULL;
    node->data=data;
    return node;
}

int addNode(Node** root, int data){
    if (!(*root)){ *root = initNode(data); return 1;}

    else if ((*root)->data > data){
        return addNode(&(*root)->left, data);
    }
    else{
        return addNode(&(*root)->right, data);
    }
}
void freeTree(Node* root){
    if (!root) { return; }
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

int deleteSubtree(Node** root, int data){
    if (!(*root)){ return 0;}

    if((*root)->data==data){
        freeTree(*root);
        *root=NULL;
        return 1;
    }
    else if ((*root)->data>data) {
        return deleteSubtree(&((*root)->left), data);
    }
    else{
        return deleteSubtree(&((*root)->right), data);
    }
}

void printTree(const Node* root){
    if (!root) { return; }
    printf("%d ", root->data);
    printTree(root->right);
    printTree(root->left);
}
