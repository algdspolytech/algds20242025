#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int height(AVLNode* node);
void update_height(AVLNode* node);
int balance_factor(AVLNode* node);
AVLNode* new_node(int key);
AVLNode* right_rotate(AVLNode* y);
AVLNode* left_rotate(AVLNode* x);
AVLNode* avl_insert(AVLNode* node, int key);
AVLNode* min_value_node(AVLNode* node);
AVLNode* avl_delete(AVLNode* root, int key);
AVLNode* avl_search(AVLNode* root, int key);
void free_avl_tree(AVLNode* root);



#endif