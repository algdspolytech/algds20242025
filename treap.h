#pragma once
#ifndef TREAP_H
#define TREAP_H

typedef struct TreapNode {
    int key;
    int value;
    int priority;
    int max_value;
    struct TreapNode* left;
    struct TreapNode* right;
} TreapNode;
TreapNode* create_node(int key, int value, int priority);
void split(TreapNode* root, int key, TreapNode** left, TreapNode** right);
TreapNode* merge(TreapNode* left, TreapNode* right);
TreapNode* insert(TreapNode* root, TreapNode* node);
int range_max_query(TreapNode* root, int x, int y);
void free_treap(TreapNode* root);

#endif