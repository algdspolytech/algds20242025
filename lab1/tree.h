#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

// Структуру для узла дерева
typedef struct Node {
    char name[9];
    struct Node* subdirs[500];
    int subdir_count;
} Node;

Node* create_node(const char* name);

void add_subdir(Node* parent, Node* subdir);

int compare_nodes(const void* a, const void* b);

void print_tree(Node* node, int level, FILE* output);

void free_tree(Node* node);

void build_directory_tree(const char* input_file, const char* output_file);

#endif // TREE_H


