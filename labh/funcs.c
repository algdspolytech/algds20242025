//
//  funcs.c
//  LabH
//
//  Created by Фёдор Филь on 22.03.2025.
//

#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

Node* newNode(int key, long value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->sum = value;
    return node;
}

Node* insert(Node* root, int key, long value) {
    if (!root)
        return newNode(key, value);
    
    if (key < root->key) {
        root->left = insert(root->left, key, value);
    } else {
        root->right = insert(root->right, key, value);
    }
    
    root->sum = root->value + (root->left ? root->left->sum : 0) +
                            (root->right ? root->right->sum : 0);
    return root;
}

long rangeSum(Node* root, int l, int r) {
    if (!root || root->key >= r)
        return 0;
    
    if (l <= root->key && root->key < r) {
        long left_sum = rangeSum(root->left, l, r);
        long right_sum = rangeSum(root->right, l, r);
        
        return left_sum + right_sum + root->value;
    }
    
    if (root->key < l) {
        return rangeSum(root->right, l, r);
    } else { 
        return rangeSum(root->left, l, r);
    }
}
