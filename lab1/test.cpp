#include "pch.h"
#include "../../RandomBinaryTree/RandomBinaryTree/RandomBinaryTree.h"


TEST(TestRandomBinaryTree, Add_ManyInts__1) {
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 98765;

    for (int i = 1;i <= n;i++)
        rtree.add(i, i);

    int counter = 0;
    for (int i = 1;i <= n;i++) {
        if (i == rtree.get(i))
            counter++;
    }

    EXPECT_EQ(n, counter);
}


TEST(TestRandomBinaryTree, Size_ManyInts__2) {
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 23451;

    for (int i = 1;i <= n;i++)
        rtree.add(i, i);

    EXPECT_EQ(n, rtree.size());
}


TEST(TestRandomBinaryTree, Height_ManyInts__3) {
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 34213;

    for (int i = 1;i <= n;i++) {
        rtree.add(i, i);
    }

    EXPECT_GT(100, rtree.height());
}

TEST(TestRandomBinaryTree, Remove_ManyInts__4) {
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 23451;
    const int k = 2132;

    for (int i = 1;i <= n;i++)
        rtree.add(i, i);

    for (int i = 1;i <= k;i++) {
        rtree.remove(i);
    }

    EXPECT_EQ(n-k, rtree.size());
}

TEST(TestRandomBinaryTree, Get_ManyInts__5) {
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 12342;

    for (int i = 1;i <= n;i++)
        rtree.add(i, i);

    int counter = 0;
    for (int i = 1;i <= n;i++) {
        if (i == rtree.get(i))
            counter++;
    }

    EXPECT_EQ(n, counter);
}


TEST(TestRandomBinaryTree, Get_EmptyTree__6) {
    RandomizedBinarySearchTree<int, int> rtree;

    int a = rtree.get(7);

    EXPECT_EQ(a, 0);
}


TEST(TestRandomBinaryTree, Size_EmptyTree__7) {
    RandomizedBinarySearchTree<int, int> rtree;

    EXPECT_EQ(0, rtree.size());
}


TEST(TestRandomBinaryTree, Height_EmptyTree__8) {
    RandomizedBinarySearchTree<int, int> rtree;

    EXPECT_EQ(0, rtree.height());
}


TEST(TestRandomBinaryTree, Remove_EmptyTree__9) {
    RandomizedBinarySearchTree<int, int> rtree;

    rtree.remove(6);

    EXPECT_EQ(0, rtree.size());
}


TEST(TestRandomBinaryTree, AddRemove_FewIntegers_EmptyTree__10) {
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 150;
    const int k = 150;

    for (int i = 1;i <= n;i++)
        rtree.add(i, i);

    for (int i = 1;i <= k;i++) {
        rtree.remove(i);
    }

    EXPECT_EQ(0, rtree.size());
}
