#include "functions.h"


void test_avl_insert_ascending() {
    AVLNode* root = NULL;
    for (int i = 1; i <= 5; i++) {
        root = avl_insert(root, i);
        assert(balance_factor(root) >= -1 && balance_factor(root) <= 1);
    }
    assert(height(root) == 4);
    free_avl_tree(root);
}
void test_avl_insert_random() {
    AVLNode* root = NULL;
    int data[] = { 5, 3, 7, 2, 4, 6, 8 };
    for (int i = 0; i < 7; i++) {
        root = avl_insert(root, data[i]);
        assert(balance_factor(root) >= -1 && balance_factor(root) <= 1);
    }
    assert(height(root) == 3);
    free_avl_tree(root);
}
void test_avl_delete_leaf() {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_insert(root, 5);
    root = avl_delete(root, 5);
    assert(root != NULL && root->key == 10);
    free_avl_tree(root);
}
void test_avl_delete_node_with_two_children() {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_insert(root, 5);
    root = avl_insert(root, 15);
    root = avl_insert(root, 3);
    root = avl_insert(root, 7);
    root = avl_delete(root, 5);
    assert(avl_search(root, 5) == NULL);
    free_avl_tree(root);
}
void test_avl_search_existing() {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_insert(root, 20);
    assert(avl_search(root, 20) != NULL);
    free_avl_tree(root);
}
void test_avl_search_non_existing() {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_insert(root, 20);
    assert(avl_search(root, 30) == NULL);
    free_avl_tree(root);
}
void test_avl_balance_after_insertions() {
    AVLNode* root = NULL;
    int data[] = { 30, 20, 40, 10, 25, 35, 50 };
    for (int i = 0; i < 7; i++) {
        root = avl_insert(root, data[i]);
        assert(balance_factor(root) >= -1 && balance_factor(root) <= 1);
    }
    free_avl_tree(root);
}
void test_avl_duplicate_insert() {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_insert(root, 10); // ��������
    assert(root->left == NULL && root->right == NULL);
    free_avl_tree(root);
}
void test_avl_complex_operations() {
    AVLNode* root = NULL;
    root = avl_insert(root, 50);
    root = avl_insert(root, 30);
    root = avl_insert(root, 70);
    root = avl_insert(root, 20);
    root = avl_insert(root, 40);
    root = avl_delete(root, 30);
    assert(avl_search(root, 30) == NULL);
    assert(avl_search(root, 40) != NULL);
    free_avl_tree(root);
}
