#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "treap.h"

// Тест create_node
void test_create_node_validNode_returnValidVal() {
    TreapNode* node = create_node(10, 20, 5);
    assert(node->key == 10);
    assert(node->value == 20);
    assert(node->priority == 5);
    assert(node->max_value == 20);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
}

// Тест split на срединном значении
void test_split_middle_returnValidVal() {
    TreapNode* root = NULL;
    root = insert(root, create_node(10, 20, 100));
    root = insert(root, create_node(5, 15, 90));
    root = insert(root, create_node(15, 25, 80));

    TreapNode* left = NULL, * right = NULL;
    split(root, 10, &left, &right);

    assert(get_max(left) == 15);  // ключи <= 10
    assert(get_max(right) == 25); // ключи > 10

    free_treap(left);
    free_treap(right);
}

// Тест merge двух деревьев
void test_merge_twoTrees_returnValidVal() {
    TreapNode* a = create_node(5, 10, 50);
    TreapNode* b = create_node(15, 20, 40);

    TreapNode* root = merge(a, b);
    assert(get_max(root) == 20);
    free_treap(root);
}

// Тест insert: вставка нескольких значений
void test_insert_multipleValues_returnValidVal() {
    TreapNode* root = NULL;
    root = insert(root, create_node(10, 5, 30));
    root = insert(root, create_node(20, 15, 40));
    root = insert(root, create_node(5, 25, 35));

    assert(get_max(root) == 25);
    free_treap(root);
}

// Тест range_max_query на подотрезке
void test_range_max_query_middleRange_returnValidVal() {
    TreapNode* root = NULL;
    root = insert(root, create_node(1, 10, 90));
    root = insert(root, create_node(5, 30, 80));
    root = insert(root, create_node(10, 20, 70));
    root = insert(root, create_node(15, 40, 60));

    int maxVal = range_max_query(root, 5, 15); // [5, 15)
    assert(maxVal == 30);

    free_treap(root);
}

// Точка входа: запуск всех тестов
int main() {
    test_create_node_validNode_returnValidVal();
    test_split_middle_returnValidVal();
    test_merge_twoTrees_returnValidVal();
    test_insert_multipleValues_returnValidVal();
    test_range_max_query_middleRange_returnValidVal();
    printf("All tests passed!\n");
    return 0;
}