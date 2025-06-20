#ifndef LABH_H
#define LABH_H

typedef struct Node Node;

Node* insert(Node* root, int x, int c);
void free_tree(Node* root);
int range_sum(Node* root, int x, int y);

#endif // LABH_H
