#include "../headers/tree.h"

Node *CreateTree(int root_data) {
  Node *root = malloc(sizeof(Node));
  root->data = root_data;
  root->num_of_children = 0;
  root->nodes = NULL;
  return root;
}

void AddNode(Node *parent, int child_data) {
  Node **temp =
      realloc(parent->nodes, sizeof(Node *) * (parent->num_of_children + 1));
  if (temp == NULL) {
    printf("ERROR WHILE REALLOCING");
    return;
  }
  parent->nodes = temp;
  parent->num_of_children++;
  parent->nodes[parent->num_of_children - 1] = malloc(sizeof(Node));
  parent->nodes[parent->num_of_children - 1]->data = child_data;
  parent->nodes[parent->num_of_children - 1]->num_of_children = 0;
  parent->nodes[parent->num_of_children - 1]->nodes = NULL;
}

void PrintSpaces(int num) {
  for (int i = 0; i < num * 8; i++) {
    printf(" ");
  }
}

void PrintCurrentNode(Node *parent, int num) {
  PrintSpaces(num);
  printf("data: %d\n", parent->data);
  for (int i = 0; i < parent->num_of_children; i++) {
    PrintSpaces(num);
    printf("Child_%d  V\n", i + 1);
    PrintCurrentNode(parent->nodes[i], num + 1);
  }
}

void PrintTreeFromCurrentNode(Node *parent) {
  printf("Parent  V\n");
  PrintCurrentNode(parent, 1);
}