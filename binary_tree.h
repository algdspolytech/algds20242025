#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 1000
#define MAX_QUEUE_SIZE 1000

    typedef struct StackNode {
        TreeNode* node;
        int visited;
    } StackNode;

    typedef struct TreeNode {
        int value;              // Значение узла
        int node_count;         // Количество узлов в поддереве
        struct TreeNode* left;  // Левый потомок
        struct TreeNode* right; // Правый потомок
    } TreeNode;

    // Прототипы функций
    TreeNode* create_new_node(int value);
    void insert(TreeNode** root, int value);
    void delete_node(TreeNode** root, int value);
    void print_tree(TreeNode* root);
    void free_tree(TreeNode* root);

#ifdef __cplusplus
}
#endif

#endif // BINARY_TREE_H