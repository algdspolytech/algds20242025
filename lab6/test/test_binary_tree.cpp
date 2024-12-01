#include <gtest/gtest.h>
extern "C"{
#include "../src/binary_tree.h"
}
class BinaryTreeTest : public ::testing::Test {
protected:
    TreeNode* root;

    void SetUp() override {
        root = nullptr;
    }

    void TearDown() override {
        while (root != nullptr) {
            remove_node(&root, root->value);
        }
    }
};

// Тест 1: Добавление узла в пустое дерево
TEST_F(BinaryTreeTest, AddToEmptyTree) {
    add_node(&root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->node_count, 1);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
}

// Тест 2: Добавление нескольких узлов
TEST_F(BinaryTreeTest, AddMultipleNodes) {
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 20);
    EXPECT_EQ(root->node_count, 3);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 20);
}

// Тест 3: Удаление единственного узла
TEST_F(BinaryTreeTest, RemoveSingleNode) {
    add_node(&root, 10);
    remove_node(&root, 10);
    EXPECT_EQ(root, nullptr);
}

// Тест 4: Удаление узла с одним потомком (левым)
TEST_F(BinaryTreeTest, RemoveNodeWithLeftChild) {
    add_node(&root, 10);
    add_node(&root, 5);
    remove_node(&root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->node_count, 1);
}

// Тест 5: Удаление узла с одним потомком (правым)
TEST_F(BinaryTreeTest, RemoveNodeWithRightChild) {
    add_node(&root, 10);
    add_node(&root, 15);
    remove_node(&root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->node_count, 1);
}

// Тест 6: Удаление узла с двумя потомками
TEST_F(BinaryTreeTest, RemoveNodeWithTwoChildren) {
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 20);
    remove_node(&root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->node_count, 2);
}

// Тест 7: Добавление узлов, проверка node_count
TEST_F(BinaryTreeTest, NodeCountUpdateOnAddition) {
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 15);
    EXPECT_EQ(root->node_count, 3);
    EXPECT_EQ(root->left->node_count, 1);
    EXPECT_EQ(root->right->node_count, 1);
}

// Тест 8: Удаление узлов, проверка node_count
TEST_F(BinaryTreeTest, NodeCountUpdateOnRemoval) {
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 20);
    remove_node(&root, 5);
    EXPECT_EQ(root->node_count, 2);
    EXPECT_EQ(root->left, nullptr);
}

// Тест 9: Удаление несуществующего узла
TEST_F(BinaryTreeTest, RemoveNonExistentNode) {
    add_node(&root, 10);
    remove_node(&root, 20);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->node_count, 1);
}

// Тест 10: Удаление корня из дерева с несколькими уровнями
TEST_F(BinaryTreeTest, RemoveRootFromDeepTree) {
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 15);
    add_node(&root, 3);
    add_node(&root, 7);
    remove_node(&root, 10);
    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->node_count, 4);
}

// Тест 11: Добавление узлов с одинаковыми значениями
TEST_F(BinaryTreeTest, AddDuplicateValues) {
    add_node(&root, 10);
    add_node(&root, 10);
    EXPECT_EQ(root->node_count, 2);
    EXPECT_EQ(root->left->value, 10);
}

// Тест 12: Удаление узла с одинаковым значением
TEST_F(BinaryTreeTest, RemoveDuplicateValueNode) {
    add_node(&root, 10);
    add_node(&root, 10);
    remove_node(&root, 10);
    EXPECT_EQ(root->node_count, 1);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left, nullptr);
}

// Тест 13: Проверка указателя на предка
TEST_F(BinaryTreeTest, ParentPointerCorrectness) {
    TreeNode* n1 = add_node(&root, 10);
    TreeNode* n2 = add_node(&root, 5);
    EXPECT_EQ(n2->parent, n1);
}

// Тест 14: Удаление листового узла
TEST_F(BinaryTreeTest, RemoveLeafNode) {
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 15);
    remove_node(&root, 15);
    EXPECT_EQ(root->node_count, 2);
    EXPECT_EQ(root->right, nullptr);
}

// Тест 15: Пустое дерево
TEST_F(BinaryTreeTest, EmptyTree) {
    EXPECT_EQ(root, nullptr);
    remove_node(&root, 10);
    EXPECT_EQ(root, nullptr);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}