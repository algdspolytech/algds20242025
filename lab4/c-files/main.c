#include "../headers/main.h"

Node *FindNodeWithMostChildren(Node *root) {
  if (root == NULL) {
    return NULL;
  }
  queue *q = CreateQueue();
  PushQueue(q, root);
  int max_children = root->num_of_children;
  Node *max_Node = root;
  Node *t;
  while (!IsEmpty(q)) {
    t = PopQueue(q);
    for (int i = 0; i < t->num_of_children; i++) {
      PushQueue(q, t->nodes[i]);
    }
    if (t->num_of_children > max_children) {
      max_Node = t;
      max_children = t->num_of_children;
    }
  }

  return max_Node;
}