#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int data;
  int num_of_children;
  struct Node **nodes;
} Node;
#ifdef __cplusplus

extern "C" {

Node *CreateTree(int root_data);
void AddNode(Node *parent, int child_data);
void PrintTreeFromCurrentNode(Node *parent);
}
#endif