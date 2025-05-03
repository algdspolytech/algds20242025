#include "pch.h"
#include "../LabH/red_black_treew.cpp"

TEST(RedBlackTreeInsert, InsertRoot__1) {
    Node* root = nullptr;

    int i = 1;
    root = insert_node(root, i);

    EXPECT_EQ(i, root->data);

}
TEST(RedBlackTreeInsert, Insert__2) {
    Node* root = nullptr;

    for (int i = 1; i < 3; i++)
        root = insert_node(root, i);

    EXPECT_EQ(2, root->right->data);
}

TEST(RedBlackTreeSearch, Search__3) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }
    Node* node = search(root, 7);
    EXPECT_EQ(node->data, 7);
}

TEST(RedBlackTreeSearch, SearchElementNotExist__4) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }
    Node* node = search(root, 12);
    EXPECT_EQ(node, nullptr);
}

TEST(RedBlackTreeInsert, InsertRedNode__5) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }

    Node* node = search(root, 8);
    EXPECT_EQ(node->color, 0);
}


// Естественно красный не может быть листовым, имеется ввиду что его детьми являются два черных Null'a
TEST(RedBlackTreeDelete, DeleteLeafRedElement__6) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }

    Node* node = search(root, 10);
    root = delete_node(root, node);
    node = search(root, 10);
    EXPECT_EQ(node, nullptr);
}

// Вариант удаления черного узла с одним ненулевым ребенком (этот ребенок красный, черным быть он не может)
TEST(RedBlackTreeDelete, DeleteBlackElementWithOneChild__7) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }

    Node* node = search(root, 9);
    root = delete_node(root, node);
    node = search(root, 9);
    EXPECT_EQ(node, nullptr);
}

TEST(RedBlackTreeDelete, DeleteRoot__8) {
    Node* root = nullptr;

    for (int i = 1; i < 2; i++) {
        root = insert_node(root, i);
    }

    Node* node = search(root, 1);
    root = delete_node(root, node);
    EXPECT_EQ(root, nullptr);
}

TEST(RedBlackTreeDelete, DeleteBlackWithTwoLeafChildren__9) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }

    Node* node = search(root, 1);
    root = delete_node(root, node);
    node = search(root, 1);

    EXPECT_EQ(node, nullptr);
}

TEST(RedBlackTreeDelete, DeleteBlackWithTwoBlackNotLeafChildren__10) {
    Node* root = nullptr;

    for (int i = 1; i < 11; i++) {
        root = insert_node(root, i);
    }

    Node* node = search(root, 2);
    root = delete_node(root, node);
    node = search(root, 2);

    EXPECT_EQ(node, nullptr);
}