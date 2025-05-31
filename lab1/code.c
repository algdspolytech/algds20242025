#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "code.h"

// ������� ��� ������������ ������, ������� �������
void destroy_tree(node* root) {
    if (root == NULL) {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// ���������� ��� ������ � ����
node* merge(node* a, node* b) {
    if (a == NULL) { 
        return b; 
    }
    if (b == NULL) {
        return a; 
    }

    if (a->priority > b->priority) {
        a->right = merge(a->right, b);
        return a;
    }
    else {
        b->left = merge(a, b->left);
        return b;
    }
}

// ��������� ������ n �� �����: ��� ������� ����� � a, ��������� � b
void split(node* n, int key, node** a, node** b) {
    if (n == NULL) {
        if (a) *a = NULL;
        if (b) *b = NULL;
        return;
    }

    if (n->key < key) {
        split(n->right, key, &n->right, b);
        *a = n; 
    }
    else {
        split(n->left, key, a, &n->left);
        *b = n; 
    }
}

// ������� ������ �������� � �������� ������ � ������ root
void add(node** root, int key) {
    node* less;  
    node* great; 

    split(*root, key, &less, &great);
    int priority = rand();
    node* new_node = (node*)malloc(sizeof(node));
    new_node->key = key;
    new_node->priority = priority;
    new_node->left = NULL;
    new_node->right = NULL;
    *root = merge(merge(less, new_node), great);
}

// ������� ������� � �������� ������ �� ������ root
void del(node** root, int key) {
    node* less;
    node* equal;
    node* great;

    split(*root, key, &less, &great);
    split(great, key + 1, &equal, &great);
    *root = merge(less, great);
    destroy_tree(equal);
}

// �������� ������� �������� � �������� ������ � ������ root
int check(node** root, int key) {
    node* less;
    node* equal;
    node* great;

    split(*root, key, &less, &great);
    split(great, key + 1, &equal, &great);

    int result = 0;

    if (equal != NULL) {
        result = 1;
    }
    *root = merge(merge(less, equal), great);
    return result;
}
