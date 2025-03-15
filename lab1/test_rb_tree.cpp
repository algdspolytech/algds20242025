#include <gtest/gtest.h>
#include "rb_tree.h"

extern "C" {
    Node* NIL;
    void insert(Node** root, int key);
    void delete(Node** root, int key);
    Node* search(Node* root, int key);
    void free_tree(Node* root);
}

class RBTreeTest : public ::testing::Test {
protected:
    Node* root = NIL;

    void TearDown() override {
        free_tree(root);
        root = NIL;
    }

    bool is_valid_black_depth(Node* node, int& black_depth) {
        if (node == NIL) {
            black_depth = 1;
            return true;
        }
        int left_depth, right_depth;
        bool left_valid = is_valid_black_depth(node->left, left_depth);
        bool right_valid = is_valid_black_depth(node->right, right_depth);
        if (!left_valid || !right_valid || left_depth != right_depth)
            return false;
        black_depth = left_depth + (node->color == BLACK ? 1 : 0);
        return true;
    }

    bool no_red_red_violation(Node* node) {
        if (node == NIL) return true;
        if (node->color == RED) {
            if (node->left->color == RED || node->right->color == RED)
                return false;
        }
        return no_red_red_violation(node->left) && no_red_red_violation(node->right);
    }

    bool is_valid_rb_tree(Node* root) {
        if (root == NIL) return true;
        if (root->color != BLACK) return false;
        int black_depth;
        return is_valid_black_depth(root, black_depth) && no_red_red_violation(root);
    }
};

TEST_F(RBTreeTest, InsertSingleNode) {
    insert(&root, 10);
    EXPECT_EQ(root->key, 10);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

TEST_F(RBTreeTest, InsertMultipleNodes) {
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

TEST_F(RBTreeTest, DeleteLeafNode) {
    insert(&root, 10);
    insert(&root, 5);
    delete(&root, 5);
    EXPECT_EQ(search(root, 5), NIL);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

TEST_F(RBTreeTest, DeleteRootNode) {
    insert(&root, 10);
    delete(&root, 10);
    EXPECT_EQ(root, NIL);
}

TEST_F(RBTreeTest, SearchExistingAndNonExisting) {
    insert(&root, 10);
    insert(&root, 20);
    EXPECT_NE(search(root, 10), NIL);
    EXPECT_NE(search(root, 20), NIL);
    EXPECT_EQ(search(root, 30), NIL);
}

TEST_F(RBTreeTest, InsertDuplicateKeys) {
    insert(&root, 10);
    insert(&root, 10);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

TEST_F(RBTreeTest, DeleteNodeWithTwoChildren) {
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 7);
    delete(&root, 5);
    EXPECT_EQ(search(root, 5), NIL);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

TEST_F(RBTreeTest, LargeInsertionAndDeletion) {
    for (int i = 0; i < 100; ++i)
        insert(&root, i);
    for (int i = 0; i < 100; ++i)
        delete(&root, i);
    EXPECT_EQ(root, NIL);
}

TEST_F(RBTreeTest, CheckBlackDepth) {
    for (int i = 0; i < 20; ++i)
        insert(&root, i);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

TEST_F(RBTreeTest, MixedOperations) {
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    delete(&root, 50);
    insert(&root, 80);
    delete(&root, 30);
    insert(&root, 20);
    EXPECT_TRUE(is_valid_rb_tree(root));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}