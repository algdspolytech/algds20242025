#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"laba1.h"
#include<assert.h>

void test_Create_node_no1()
{
    Node* root = Create_node(10);
    assert(root != NULL);
    assert(root->key = 10);
    assert(root->left == NULL);
    assert(root->right == NULL);
    free(root);
}

void test_Insert_3nodes_no2()
{
    Node* tree = NULL;
    tree = Insert(10, tree);
    tree = Insert(20, tree);
    tree = Insert(30, tree);

    assert(contains(tree, 10) == true);
    assert(contains(tree, 20) == true);
    assert(contains(tree, 30) == true);
    assert(contains(tree, 40) == false); 
    free(tree->left);
    free(tree->right);
    free(tree);
}

void test_Split_3nodes_no3()
{
    Node* root = Create_node(5);
    root->left = Create_node(3);
    root->right = Create_node(7);

    Node* left = NULL;
    Node* right = NULL;
    Split(root, 5, &left, &right);

    assert(left != NULL);
    assert(left->key == 3);
    assert(right != NULL);
    assert(right->key == 5 || right->key == 7);

    free(root->left);
    free(root->right);
    free(root);
}

void test_Merge_2nodes_no4()
{
    Node* left = Create_node(3);
    Node* right = Create_node(7);

    Node* merged = Merge(left, right);

    assert(merged != NULL);
    assert(merged->key == 3 || merged->key == 7);

    free(left);
    free(right);
}

void test_Erase_3nodes_no5()
{
    Node* root = NULL;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);

    root = Erase(3, root);

    assert(root != NULL);
    assert(!contains(root, 3));
    assert(contains(root, 5));
    assert(contains(root, 7));

    free(root->left);
    free(root->right);
    free(root);
}

void test_contains_3nodes_no6()
{
    Node* root = NULL;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);

    assert(contains(root, 5));
    assert(contains(root, 3));
    assert(contains(root, 7));
    assert(!contains(root, 10));

    free(root->left);
    free(root->right);
    free(root);
}

void test_Split_emptytree_no7()
{
    Node* tree = NULL;
    Node* left;
    Node* right;
    Split(tree, 10, &left, &right);

    assert(left == NULL);
    assert(right == NULL);
}

void test_Insert_multipleNodes_no8()
{
    Node* root = NULL;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);
    root = Insert(2, root);
    root = Insert(4, root);
    root = Insert(6, root);
    root = Insert(8, root);

    assert(contains(root, 2));
    assert(contains(root, 4));
    assert(contains(root, 6));
    assert(contains(root, 8));

    free(root->left);
    free(root->right);
    free(root);
}

void test_Erase_MultipleNodes_no9()
{
    Node* root = NULL;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);
    root = Insert(2, root);
    root = Insert(4, root);
    root = Insert(6, root);
    root = Insert(8, root);

    root = Erase(3, root);
    root = Erase(7, root);
    root = Erase(5, root);

    assert(!contains(root, 3));
    assert(!contains(root, 7));
    assert(!contains(root, 5));
    assert(contains(root, 2));
    assert(contains(root, 4));
    assert(contains(root, 6));
    assert(contains(root, 8));

    free(root->left);
    free(root->right);
    free(root);
}

void test_Insert_priority_no10()
{
    Node* root = NULL;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);

    assert(root->priority >= (root->left ? root->left->priority : -1));
    assert(root->priority >= (root->right ? root->right->priority : -1));

    free(root->left);
    free(root->right);
    free(root);
}

void test_Split_MultipleNodes_no11()
{
    Node* root = NULL;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);
    root = Insert(2, root);
    root = Insert(4, root);
    root = Insert(6, root);
    root = Insert(8, root);
    Node* left;
    Node* right;
    Split(root, 5, &left, &right);

    assert(contains(left, 2));
    assert(contains(left, 3));
    assert(contains(left, 4));
    assert(contains(right, 5));
    assert(contains(right, 6));
    assert(contains(right, 7));
    assert(contains(right, 8));

    free(root->left);
    free(root->right);
    free(root);
}

void RunTests()
{
    test_Insert_3nodes_no2();
    test_Create_node_no1();
    test_Split_3nodes_no3();
    test_Merge_2nodes_no4();
    test_Erase_3nodes_no5();
    test_contains_3nodes_no6();
    test_Split_emptytree_no7();
    test_Insert_multipleNodes_no8();
    test_Erase_MultipleNodes_no9();
    test_Insert_priority_no10();
    test_Split_MultipleNodes_no11();

    printf("All tests were successful!\n");
}

