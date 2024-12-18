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
    TREE_Node_t* root = NULL;

    fscanf(file, "%i", &n);
    nodes = malloc(n * sizeof(TREE_Node_t*));

    //n values of nodes
    for(int i = 0; i < n; i++) {
        nodes[i] = malloc(sizeof(TREE_Node_t));
        fscanf(file, "%i", &nodes[i]->data);
        nodes[i]->parent = NULL;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    //backward node relation (from leafs to root)
    for(int i = 0; i < n; i++) {
        int isLeft, parentID, ID;
        fscanf(file, "%i", &ID);
        fscanf(file, "%i", &isLeft);
        fscanf(file, "%i", &parentID);

        if(parentID != -1) {
            nodes[ID]->parent = nodes[parentID];
            if(isLeft) {
                nodes[parentID]->left = nodes[ID];
            } else {
                nodes[parentID]->right = nodes[ID];
            }
        } else
            root = nodes[ID];

        //free calculation of reqCnt
        nodes[ID]->reqCnt = sizeInteger(nodes[parentID]->data);
        if(nodes[ID]->left != NULL)
            nodes[ID]->reqCnt += nodes[ID]->left->reqCnt;
        if(nodes[ID]->right != NULL)
            nodes[ID]->reqCnt += nodes[ID]->right->reqCnt;
    }
}
