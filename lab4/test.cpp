#include <gtest/gtest.h>
#include <stdio.h>
#include "main.h"

TEST(BinaryTreeTest, CreateNode) {
    Node* node = createNode("Root");
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->data, "Root");
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    freeTree(node);
}

TEST(BinaryTreeTest, AddNode) {
    Node* root = createNode("Is it an animal?");
    root->left = createNode("Yes");
    root->right = createNode("No");

    // Проверяем корневой узел
    EXPECT_STREQ(root->data, "Is it an animal?");
    EXPECT_STREQ(root->left->data, "Yes");
    EXPECT_STREQ(root->right->data, "No");

    freeTree(root);
}

TEST(BinaryTreeTest, SaveAndLoadTree) {
    const char* filename = "test_tree.txt";

    // Создаем дерево
    Node* root = createNode("Is it an animal?");
    root->left = createNode("Yes");
    root->right = createNode("No");

    // Сохраняем дерево в файл
    FILE* file = fopen(filename, "w");
    ASSERT_NE(file, nullptr);
    saveTree(file, root);
    fclose(file);

    // Загружаем дерево из файла
    file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);
    Node* loadedTree = loadTree(file);
    fclose(file);

    // Проверяем загруженное дерево
    ASSERT_NE(loadedTree, nullptr);
    EXPECT_STREQ(loadedTree->data, "Is it an animal?");
    EXPECT_STREQ(loadedTree->left->data, "Yes");
    EXPECT_STREQ(loadedTree->right->data, "No");

    freeTree(root);
    freeTree(loadedTree);
}

TEST(BinaryTreeTest, PrintTree) {
    Node* root = createNode("Is it an animal?");
    root->left = createNode("Yes");
    root->right = createNode("No");

    // Проверяем, что функция выполняется без сбоев (вывод сложно тестировать автоматически)
    testing::internal::CaptureStdout();
    printTree(root, 0);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Is it an animal?\n"), std::string::npos);
    EXPECT_NE(output.find("  Yes\n"), std::string::npos);
    EXPECT_NE(output.find("  No\n"), std::string::npos);

    freeTree(root);
}

TEST(BinaryTreeTest, AddNodeToEmptyTree) {
    Node* root = nullptr;
    root = createNode("Is it a mammal?");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->data, "Is it a mammal?");
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    freeTree(root);
}

TEST(BinaryTreeTest, LoadTreeFromEmptyFile) {
    const char* filename = "empty_tree.txt";
    FILE* file = fopen(filename, "w");
    ASSERT_NE(file, nullptr);
    fclose(file);

    file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);
    Node* root = loadTree(file);
    fclose(file);

    EXPECT_EQ(root, nullptr);
}

TEST(BinaryTreeTest, SaveEmptyTree) {
    const char* filename = "empty_tree_save.txt";
    Node* root = nullptr;

    FILE* file = fopen(filename, "w");
    ASSERT_NE(file, nullptr);
    saveTree(file, root);
    fclose(file);

    file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);
    char buffer[10];
    fgets(buffer, sizeof(buffer), file);
    EXPECT_EQ(strcmp(buffer, "#\n"), 0);
    fclose(file);
}

TEST(BinaryTreeTest, FreeTree) {
    Node* root = createNode("Root");
    root->left = createNode("Left");
    root->right = createNode("Right");
    freeTree(root);

    // Проверяем, что повторное освобождение безопасно
    freeTree(nullptr);
}

TEST(BinaryTreeTest, DeepTreeLoad) {
    const char* filename = "deep_tree.txt";
    Node* root = createNode("Root");
    root->left = createNode("Left");
    root->right = createNode("Right");
    root->left->left = createNode("Left.Left");
    root->left->right = createNode("Left.Right");

    FILE* file = fopen(filename, "w");
    ASSERT_NE(file, nullptr);
    saveTree(file, root);
    fclose(file);

    file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);
    Node* loadedTree = loadTree(file);
    fclose(file);

    EXPECT_STREQ(loadedTree->data, "Root");
    EXPECT_STREQ(loadedTree->left->data, "Left");
    EXPECT_STREQ(loadedTree->right->data, "Right");
    EXPECT_STREQ(loadedTree->left->left->data, "Left.Left");
    EXPECT_STREQ(loadedTree->left->right->data, "Left.Right");

    freeTree(root);
    freeTree(loadedTree);
}

TEST(BinaryTreeTest, SaveAndLoadSingleNodeTree) {
    const char* filename = "single_node_tree.txt";

    // Создаем дерево с одним узлом
    Node* root = createNode("Only Node");

    // Сохраняем дерево в файл
    FILE* file = fopen(filename, "w");
    ASSERT_NE(file, nullptr);
    saveTree(file, root);
    fclose(file);

    // Загружаем дерево из файла
    file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);
    Node* loadedTree = loadTree(file);
    fclose(file);

    // Проверяем загруженное дерево
    ASSERT_NE(loadedTree, nullptr);
    EXPECT_STREQ(loadedTree->data, "Only Node");
    EXPECT_EQ(loadedTree->left, nullptr);
    EXPECT_EQ(loadedTree->right, nullptr);

    freeTree(root);
    freeTree(loadedTree);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
