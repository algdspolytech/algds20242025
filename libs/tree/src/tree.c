#include "tree.h"

#include <stdlib.h>


int sizeInteger(int s) {
    int size = 0;
    size += (s < 0) ? 1 : 0;
    s = abs(s);

    while(s != 0) {
        s /= 10;
        size++;
    }

    return size;
}

TREE_Node_t* TREE_CreateTreeFromFile(FILE* file) {
    int n;
    TREE_Node_t** nodes;
    unsigned char* validation;
    unsigned char isInvalid = 0;
    TREE_Node_t* root = NULL;

    fscanf(file, "%i", &n);
    nodes = malloc(n * sizeof(TREE_Node_t*));
    validation = malloc(n * sizeof(unsigned char));

    //n values of nodes
    for(int i = 0; i < n; i++) {
        nodes[i] = malloc(sizeof(TREE_Node_t));
        fscanf(file, "%i", &nodes[i]->data);
        nodes[i]->parent = NULL;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
        nodes[i]->id = i;
        validation[i] = 0;
    }

    //backward node relation (from leafs to root)
    for(int i = 0; i < n; i++) {
        int isLeft, parentID, ID;
        fscanf(file, "%i", &ID);
        fscanf(file, "%i", &isLeft);
        fscanf(file, "%i", &parentID);

        if(validation[ID]) {
            isInvalid = 1;
            break;
        }

        if(parentID != -1 && !validation[parentID] &&
            (nodes[parentID]->left == NULL
                || nodes[parentID]->right == NULL)) {
            nodes[ID]->parent = nodes[parentID];
            if(isLeft) {
                nodes[parentID]->left = nodes[ID];
            } else {
                nodes[parentID]->right = nodes[ID];
            }
        } else if(parentID == -1 ) {
            root = nodes[ID];
        } else {
            isInvalid = 1;
            break;
        }

        //free calculation of reqCnt
        nodes[ID]->reqCnt = sizeInteger(nodes[ID]->data);
        if(nodes[ID]->left != NULL)
            nodes[ID]->reqCnt += nodes[ID]->left->reqCnt;
        if(nodes[ID]->right != NULL)
            nodes[ID]->reqCnt += nodes[ID]->right->reqCnt;

        validation[ID] = 1;
    }

    if(isInvalid) {
        for(int i = 0; i < n; i++)
            free(nodes[i]);
        root = NULL;
    }

    free(nodes);
    return root;
}

void TREE_DeleteTree(TREE_Node_t* root) {
    if(root == NULL)
        return;
    TREE_DeleteTree(root->left);
    TREE_DeleteTree(root->right);
    free(root);
}
