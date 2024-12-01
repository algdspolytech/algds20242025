#include <gtest/gtest.h>

extern "C"
{
    #include "btree.h"
}


TEST(BTree, normal_case_n1)
{
    btree* tree = NULL;
    pushBack(&tree, 6);
    pushBack(&tree, 4);
    pushBack(&tree, 7);
    pushBack(&tree, 3);
    pushBack(&tree, 5);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, normal_case_n2)
{
    btree* tree = NULL;
    pushBack(&tree, 1);
    pushBack(&tree, 2);
    pushBack(&tree, 3);
    pushBack(&tree, 4);
    pushBack(&tree, 5);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, same_vals_n3)
{
    btree* tree = NULL;
    pushBack(&tree, 1);
    pushBack(&tree, 1);
    pushBack(&tree, 1);
    pushBack(&tree, 1);
    pushBack(&tree, 1);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, empty_tree_n4)
{
    btree* tree = NULL;
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, one_value_n5)
{
    btree* tree = NULL;
    pushBack(&tree, 6);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, all_zeros_n6)
{
    btree* tree = NULL;
    pushBack(&tree, 0);
    pushBack(&tree, 0);
    pushBack(&tree, 0);
    pushBack(&tree, 0);
    pushBack(&tree, 0);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, two_vals_n7)
{
    btree* tree = NULL;
    pushBack(&tree, 6);
    pushBack(&tree, 4);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}


TEST(BTree, big_tree_n8)
{
    btree* tree = NULL;
    pushBack(&tree, 6);
    pushBack(&tree, 4);
    pushBack(&tree, 7);
    pushBack(&tree, 3);
    pushBack(&tree, 5);
    pushBack(&tree, 1);
    pushBack(&tree, 2);
    pushBack(&tree, 8);
    pushBack(&tree, 10);
    pushBack(&tree, 13);
    pushBack(&tree, 100);
    pushBack(&tree, 74);
    pushBack(&tree, 54);
    pushBack(&tree, 22);
    pushBack(&tree, 97);
    pushBack(&tree, 112);
    pushBack(&tree, 27);
    pushBack(&tree, 35);
    pushBack(&tree, 48);
    pushBack(&tree, 34);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, negative_vals_n9)
{
    btree* tree = NULL;
    pushBack(&tree, -1);
    pushBack(&tree, -4);
     pushBack(&tree, -2);
    pushBack(&tree, -5);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}

TEST(BTree, big_vals_n10)
{
    btree* tree = NULL;
    pushBack(&tree, 1003984983748378);
    pushBack(&tree, 327482384789323489);
    pushBack(&tree, 156121231315154523);
    pushBack(&tree, 5456421324487445454);
    unsigned int height = 0, width = 0;
    countLeafs(tree);
    int** matrix = getMatrix(tree, &height, &width);
    deleteTree(tree);
}


