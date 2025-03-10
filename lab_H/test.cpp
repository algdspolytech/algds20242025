#include <gtest/gtest.h>
#include "Treap.hpp"


bool isValidTreap(Node* root) {
    if (!root) return true;
    if (root->left && root->left->data.first >= root->data.first) return false;
    if (root->right && root->right->data.first <= root->data.first) return false;
    if (root->left && root->left->data.second > root->data.second) return false;
    if (root->right && root->right->data.second > root->data.second) return false;
    return isValidTreap(root->left) && isValidTreap(root->right);
}


TEST(TreapTest, TreapCreateNullptr_1) {
    Node* root = CreateTreap();
    ASSERT_EQ(root, nullptr);
}


TEST(TreapTest, TreapAddingOneNode_2) {
    Node* root = nullptr;
    insert(root, {10, 1});
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data.first, 10);
    EXPECT_EQ(root->data.second, 1);
}

TEST(TreapTest, TreapHeapCheck_3) {
    Node* root = nullptr;
    insert(root, {10, 1});
    insert(root, {5, 2});
    insert(root, {15, 3});
    EXPECT_TRUE(isValidTreap(root));
}

TEST(TreapTest, TreapAddingExistingNode_4) {
    Node* root = nullptr;
    insert(root, {10, 1});
    insert(root, {10, 2});
    EXPECT_EQ(root->data.first, 10);
    EXPECT_EQ(root->data.second, 2);
}


TEST(TreapTest, TreapSplitNormal_5) {
    Node* root = nullptr;
    insert(root, {10, 1});
    insert(root, {5, 2});
    insert(root, {15, 3});

    auto [left, right] = split(root, 10);
    EXPECT_TRUE(isValidTreap(left));
    EXPECT_TRUE(isValidTreap(right));
}

TEST(TreapTest, TreapSplitCheckingNodes_6) {
    Node* root = nullptr;
    insert(root, {10, 1});
    insert(root, {5, 2});
    insert(root, {15, 3});

    auto [left, right] = split(root, 10);
    if (left) EXPECT_LT(left->data.first, 10);
    if (right) EXPECT_GE(right->data.first, 10);
}

TEST(TreapTest, EmptyTreapSplit_7) {
    auto [left, right] = split(nullptr, 10);
    EXPECT_EQ(left, nullptr);
    EXPECT_EQ(right, nullptr);
}


TEST(TreapTest, SecondEmptyTreapMerge_8) {
    Node* first = new Node{{10, 1}, nullptr, nullptr};
    Node* result = merge(first, nullptr);
    EXPECT_EQ(result, first);
}

TEST(TreapTest, FirstEmptyTreapMerge_9) {
    Node* second = new Node{{20, 2}, nullptr, nullptr};
    Node* result = merge(nullptr, second);
    EXPECT_EQ(result, second);
}

TEST(TreapTest, TreapMergeHeapCheck_10) {
    Node* first = new Node{{10, 1}, nullptr, nullptr};
    Node* second = new Node{{20, 2}, nullptr, nullptr};
    Node* result = merge(first, second);
    EXPECT_TRUE(isValidTreap(result));
}


TEST(TreapTest, TreapRemoveExistingNode_11) {
    Node* root = nullptr;
    insert(root, {10, 1});
    remove(root, 10);
    EXPECT_EQ(root, nullptr);
}

TEST(TreapTest, TreapRemoveNotExistingNode_12) {
    Node* root = nullptr;
    insert(root, {10, 1});
    remove(root, 5);
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->data.first, 10);
}

TEST(TreapTest, TreapRemoveHeapCheck_13) {
    Node* root = nullptr;
    insert(root, {10, 1});
    insert(root, {5, 2});
    insert(root, {15, 3});
    remove(root, 10);
    EXPECT_TRUE(isValidTreap(root));
}


TEST(TreapTest, TreapClearNode_14) {
    Node* root = nullptr;
    insert(root, {10, 1});
    insert(root, {5, 2});
    insert(root, {15, 3});
    ClearNode(root);
    EXPECT_EQ(root, nullptr);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}