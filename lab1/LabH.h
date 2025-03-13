#ifndef LABH_H
#define LABH_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Node {
    int key;
    int height;
    int size;
    struct Node* left, * right;
} Node;


Node* create_node(int key);

int getHeight(Node* node);

int getSize(Node* node);

void update(Node* node);
Node* rightRotate(Node* y); .
Node* leftRotate(Node* x);

int getBalance(Node* node);
Node* balance(Node* node);

Node* find_kth(Node* root, int k);

Node* search_by_key(Node* root, int key);

Node* insert_at(Node* root, int pos, int key);

Node* delete_at(Node* root, int pos);

Node* extract_max(Node* root, Node** max_node);

Node* join_trees(Node* t1, Node* t2);

void inorder_print(Node* root);

#endif // LABH_H