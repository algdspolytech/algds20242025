#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "redblack.h"

// ����� ������� ���� �� ����-������ �� ��������� ����-������� �������� ���������� ����� ������ �����
int check_black_height(RBTree* tree, Node* node) {
    if (node == tree->nil) return 1; // ���������� �� �������� ���� - ������� �� ��������

    int left_height = check_black_height(tree, node->left);
    int right_height = check_black_height(tree, node->right);

    // ���� � ����� �� ������ �������� ������ -1
    // ��� ������ ������ ������ � ����� ����������� �� ������� ������, �� ������ ��������� ����� �� �������� -1
    if (left_height == -1 || right_height == -1 || left_height != right_height)
        return -1;

    return left_height + (node->color == BLACK);
}

// ��������� ��� ��� ������� � ���� ������� ����� - ������
int check_red_property(RBTree* tree, Node* node) {
    if (node == tree->nil) return 1; // ���� ������� �������� ������ ��������� (nil) ������ �� �������� �������������

    // ���� ���� �������, �� � ���� ���� �������� �������, �� ������ ������������ 
    if (node->color == RED) {
        if (node->left->color != BLACK || node->right->color != BLACK) {
            return 0; 
        }
    }

    return check_red_property(tree, node->left) && check_red_property(tree, node->right);
}

// ����� �������� ������������ ������-������� ������
int validate_rbtree(RBTree* tree) {

    int result;

    result = (tree->root->color == BLACK);                           // ������ ������ - ������
    result = result && (check_red_property(tree, tree->root));       // ��� ������� ������� �������� ���� � ������
    result = result && (check_black_height(tree, tree->root) != -1); // �������� ������������ ������ �����

    return result;
}

int elem_with_data_exists(RBTree* tree, int data) {
    return search(tree, data) != NULL;
}


void test_init_EmptyTree_RootIsNil() {
    RBTree tree;
    init_rbtree(&tree);
    assert(tree.root == tree.nil);
    free_tree(&tree);
}


void test_insert_SingleElement_ValidTree() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 1);
    assert(validate_rbtree(&tree));
    free_tree(&tree);
}


void test_search_ExistingElement_ReturnValid() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 1);
    Node* result = search(&tree, 1);
    assert(result != NULL && result->data == 1);
    free_tree(&tree);
}


void test_search_MissingElement_ReturnNull() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 1);
    assert(search(&tree, 2) == NULL);
    free_tree(&tree);
}


void test_delete_LeafNode_ValidTree() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 1);
    insert(&tree, 2);
    delete(&tree, 2);
    assert(validate_rbtree(&tree));
    free_tree(&tree);
}


void test_delete_NodeWithOneChild_ValidTree() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 1);
    insert(&tree, 2);
    insert(&tree, 3);
    delete(&tree, 2);
    assert(validate_rbtree(&tree));
    free_tree(&tree);
}


void test_delete_NodeWithTwoChildren_ValidTree() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 4);
    insert(&tree, 2);
    insert(&tree, 6);
    insert(&tree, 1);
    insert(&tree, 3);

    delete(&tree, 2);
    assert(validate_rbtree(&tree));
    free_tree(&tree);
}


void test_delete_RootNode_ValidTree() {
    RBTree tree;
    init_rbtree(&tree);
    insert(&tree, 1);
    insert(&tree, 2);

    delete(&tree, 1);
    assert(validate_rbtree(&tree));
    free_tree(&tree);
}

void test_insertdelete_MixedOperations_ValidTree() {
    RBTree tree;
    init_rbtree(&tree);
    for (int i = 0; i < 100; i++) insert(&tree, i);
    for (int i = 0; i < 100; i += 2) delete(&tree, i);
    assert(validate_rbtree(&tree));
    free_tree(&tree);
}

void test_search_AfterOperations_CorrectElements() {
    RBTree tree;
    init_rbtree(&tree); 
    int values[] = { 1, 4, 3, 2, 5, 7, 6 }; // ����� �� 1 �� 7 � ��������� �������
    int len = sizeof(values) / sizeof(values[0]);


    for (int i = 0; i < len; i++)  insert(&tree, values[i]); // ����������� ��� ��������
    for (int i = 1; i < len; i+=2) delete(&tree, values[i]); // �������� � �������� �������� ���������



    for (int i = 0; i < len; i++) {
        int should_exist = (i % 2==0); // ���� ������ ������, �� ������� ������ ������������, ����� - ���
        assert(elem_with_data_exists(&tree, values[i]) == should_exist);
    }

    free_tree(&tree);
}

int main() {

    test_init_EmptyTree_RootIsNil();

    test_insert_SingleElement_ValidTree();

    test_search_ExistingElement_ReturnValid();

    test_search_MissingElement_ReturnNull();

    test_delete_LeafNode_ValidTree();

    test_delete_NodeWithOneChild_ValidTree();

    test_delete_NodeWithTwoChildren_ValidTree();

    test_delete_RootNode_ValidTree();

    test_insertdelete_MixedOperations_ValidTree();

    test_search_AfterOperations_CorrectElements();

    return 0;
}