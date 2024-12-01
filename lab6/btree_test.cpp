#include <gtest/gtest.h>
extern "C" {
    #include "btree.h"
}

Node* root = nullptr;

void cleanup() {
    if (root != nullptr) {
        freeTree(root);
        root = nullptr;
    }
}

TEST(BTreeTest, CreateNode_no1) {
    cleanup();
    Node* node = createNode(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, 5);
    EXPECT_EQ(node->count, 1);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

TEST(BTreeTest, InsertIntoEmptyTree_no2) {
    cleanup();
    root = insert(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->count, 1);
}

TEST(BTreeTest, InsertBalanced_no3) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    
    EXPECT_EQ(root->count, 3);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 15);
}

TEST(BTreeTest, InsertInSmallerSubtree_no4) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 20);  // должно пойти влево из-за баланса
    
    EXPECT_EQ(root->left->count, 2);
    EXPECT_EQ(root->right->count, 1);
}

TEST(BTreeTest, DeleteLeafNode_no5) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    root = delete(root, 5);
    
    EXPECT_EQ(root->count, 1);
    EXPECT_EQ(root->left, nullptr);
}

TEST(BTreeTest, DeleteNodeWithOneChild_no6) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 3);
    root = delete(root, 5);
    
    EXPECT_EQ(root->count, 2);
    EXPECT_EQ(root->left->value, 3);
}

TEST(BTreeTest, DeleteNodeWithTwoChildren_no7) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 12);
    root = insert(root, 17);
    root = delete(root, 15);
    
    EXPECT_EQ(root->count, 4);
    EXPECT_NE(root->right->value, 15);
}

TEST(BTreeTest, DeleteRootWithRebalancing_no8) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = delete(root, 10);
    
    EXPECT_EQ(root->count, 2);
    EXPECT_NE(root->value, 10);
}

TEST(BTreeTest, ComplexInsertionPattern_no9) {
    cleanup();
    const int values[] = {10, 5, 15, 3, 7, 12, 17};
    for (int value : values) {
        root = insert(root, value);
    }
    
    EXPECT_EQ(root->count, 7);
    EXPECT_EQ(root->left->count, 3);
    EXPECT_EQ(root->right->count, 3);
}

TEST(BTreeTest, DeleteNonExistentValue_no10) {
    cleanup();
    root = insert(root, 10);
    root = insert(root, 5);
    Node* originalRoot = root;
    root = delete(root, 15);  // попытка удалить несуществующее значение
    
    EXPECT_EQ(root, originalRoot);
    EXPECT_EQ(root->count, 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}
