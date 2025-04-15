#include "tree.h"
#include <stdbool.h>

Node* build_test_tree_1_empty() {
    return NULL;
}

Node* build_test_tree_2_single_node() {
    return createNode(10);
}

Node* build_test_tree_3_root_two_leaves() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    return root;
}

Node* build_test_tree_4_left_skewed() {
    Node* root = createNode(50);
    root->left = createNode(40);
    root->left->left = createNode(30);
    root->left->left->left = createNode(20);
    root->left->left->left->left = createNode(10);
    return root;
}

Node* build_test_tree_5_right_skewed() {
    Node* root = createNode(10);
    root->right = createNode(20);
    root->right->right = createNode(30);
    root->right->right->right = createNode(40);
    root->right->right->right->right = createNode(50);
    return root;
}

Node* build_test_tree_6_full_binary() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(2);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(18);
    return root;
}

Node* build_test_tree_7_incomplete_last_level() {
    Node* root = createNode(20);
    root->left = createNode(10);
    root->right = createNode(30);
    root->left->left = createNode(5);
    return root;
}

Node* build_test_tree_8_zigzag() {
    Node* root = createNode(10);
    root->right = createNode(20);
    root->right->left = createNode(15);
    root->right->right = createNode(30);
    root->right->right->left = createNode(25);
    return root;
}

Node* build_test_tree_9_internal_one_child() {
    Node* root = createNode(100);
    root->left = createNode(50);
    root->left->left = createNode(25);
    root->right = createNode(150);
    return root;
}

Node* build_test_tree_10_complex() {
    Node* root = createNode(50);
    root->left = createNode(20);
    root->right = createNode(80);
    root->left->left = createNode(10);
    root->left->right = createNode(30);
    root->left->right->left = createNode(25);
    root->left->right->right = createNode(35);
    root->right->left = createNode(70);
    root->right->right = createNode(90);
    root->right->right->right = createNode(100);
    return root;
}
void run_test(int test_num, Node* (*build_func)(), const char* description) {
    printf("\n--- test %d: %s ---\n", test_num, description);
    Node* root = build_func();

    printf("input tree (struct):\n");
    if (root == NULL) {
        printf(" (empty tree)\n");
    }
    else {
        printf(" koren: %d\n", root->data);
    }


    printf("\nfind min hight list...\n");
    calculateAndSetMinLeafHeight(root);

    printf("\ntree (prefic find: uzel(data)[MinLeafHeight]):\n");
    printTreePreOrder(root);
    printf("\n");

    freeTree(root);
    printf("--- test %d end ---\n", test_num);
}