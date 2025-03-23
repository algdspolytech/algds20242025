#ifndef SPLAY_THREE
#define SPLAY_THREE

#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left, *right, *parent;

} Node;

Node *insert(Node *root, int value);
Node *search(Node *root, int value);
Node *erase(Node *root, int value);

Node *_splay(Node *aim, Node *stPar);
void _rotate(Node *aim);
void _zigzig(Node *aim);
void _zigzag(Node *aim);

void _change_parent(Node *aim, Node *parent);
void _set_parent(Node *child, Node *parent);
Node *_merge(Node *left, Node *right);

#endif