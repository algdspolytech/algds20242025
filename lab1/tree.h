#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX_PATH_LEN 255
#define MAX_FOLDER_NAME 8
#define MAX_FOLDERS 500

typedef struct Node {
    char name[MAX_FOLDER_NAME + 1];
    struct Node ** children;
    int children_count;
    int children_capacity;
}
Node;

Node * create_node(const char * name);
void add_path(Node * root,
    const char * path);
void sort_children(Node * node);
void write_tree_to_file(Node * root, FILE * file, int depth);
void free_tree(Node * root);

#endif