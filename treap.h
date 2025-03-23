#ifndef TREAP_H
#define TREAP_H

#include <stdbool.h>
#include <stdio.h>
#pragma warning(disable:4996)

typedef struct TreapNode {
    int key;
    int priority;
    struct TreapNode* left, * right;
} TreapNode;

#ifdef __cplusplus
extern "C" {
#endif

TreapNode* treap_create_node(int key, int priority);

TreapNode* treap_insert(TreapNode* root, int key, int priority);

TreapNode* treap_delete(TreapNode* root, int key);

TreapNode* treap_merge(TreapNode* left, TreapNode* right);

void treap_split(TreapNode* root, int key, TreapNode** left, TreapNode** right);

void treap_destroy(TreapNode* root);

bool treap_search(TreapNode* root, int key);

void treap_inorder(TreapNode* root);

int treap_size(TreapNode* root);

#ifdef __cplusplus
}
#endif

#endif // TREAP_H