#include "pch.h"
#include "../../RandomBinaryTree/RandomBinaryTree/RandomBinaryTree.cpp"


TEST(TestRandomBinaryTree, Add_ManyInts__1) {

    Node* rtree = nullptr;

    const int n = 98765;

    for (int i = 1;i <= n;i++)
        rtree = add(rtree, i, i);

    int counter = 0;
    for (int i = 1;i <= n;i++) {
        if (i == get(rtree, i))
            counter++;
    }

    EXPECT_EQ(n, counter);
}


TEST(TestRandomBinaryTree, Size_ManyInts__2) {
    Node* rtree = nullptr;

    const int n = 23451;

    for (int i = 1;i <= n;i++)
        rtree = add(rtree, i, i);

    EXPECT_EQ(n, size(rtree));
}


TEST(TestRandomBinaryTree, Height_ManyInts__3) {
    Node* rtree = nullptr;

    const int n = 34213;

    for (int i = 1;i <= n;i++)
        rtree = add(rtree, i, i);

    EXPECT_GT(100, height(rtree));
}

TEST(TestRandomBinaryTree, Remove_ManyInts__4) {
    Node* rtree = nullptr;

    const int n = 23451;
    const int k = 2132;

    for (int i = 1;i <= n;i++)
        rtree = add(rtree, i, i);

    for (int i = 1;i <= k;i++)
        rtree = remove(rtree, i);

    EXPECT_EQ(n-k, size(rtree));
}

TEST(TestRandomBinaryTree, Get_ManyInts__5) {
    Node* rtree = nullptr;

    const int n = 12342;

    for (int i = 1;i <= n;i++)
        rtree = add(rtree, i, i);

    int counter = 0;
    for (int i = 1;i <= n;i++)
        if (i == get(rtree, i))
            counter++;

    EXPECT_EQ(n, counter);
}


TEST(TestRandomBinaryTree, Get_EmptyTree__6) {
    Node* rtree = nullptr;

    int a = get(rtree, 7);

    EXPECT_EQ(a, 0);
}


TEST(TestRandomBinaryTree, Size_EmptyTree__7) {
    Node* rtree = nullptr;

    EXPECT_EQ(0, size(rtree));
}


TEST(TestRandomBinaryTree, Height_EmptyTree__8) {
    Node* rtree = nullptr;

    EXPECT_EQ(0, height(rtree));
}


TEST(TestRandomBinaryTree, Remove_EmptyTree__9) {
    Node* rtree = nullptr;

    rtree = remove(rtree, 6);

    EXPECT_EQ(0, size(rtree));
}


TEST(TestRandomBinaryTree, AddRemove_FewIntegers_EmptyTree__10) {
    Node* rtree = nullptr;

    const int n = 150;
    const int k = 150;

    for (int i = 1;i <= n;i++)
        rtree = add(rtree, i, i);

    for (int i = 1;i <= k;i++)
        rtree = remove(rtree, i);

    EXPECT_EQ(0, size(rtree));
}
