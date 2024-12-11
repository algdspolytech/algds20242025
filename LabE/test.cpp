#include "funcs.h"
#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(_calculate_subtree_width, SimpleTree) { /*return True*/
    TreeNode* root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(15);

    int width = calculate_subtree_width(root);
    EXPECT_EQ(width, 5);

    free_tree(root);
}

TEST(_calculate_subtree_width, SingleNode) { /*return True*/
    TreeNode* root = create_node(42);

    int width = calculate_subtree_width(root);
    EXPECT_EQ(width, 2);

    free_tree(root);
}

TEST(_calculate_subtree_width, NestedNodes) { /*return True*/
    TreeNode* root = create_node(100);
    root->left = create_node(50);
    root->right = create_node(25);
    root->left->left = create_node(5);
    root->left->right = create_node(10);

    int width = calculate_subtree_width(root);
    EXPECT_EQ(width, 10);

    free_tree(root);
}

TEST(_calculate_subtree_width, OnlyLeftSubtree) { /*return True*/
    TreeNode* root = create_node(10);
    root->left = create_node(20);

    int width = calculate_subtree_width(root);
    EXPECT_EQ(width, 4);

    free_tree(root);
}

TEST(_calculate_subtree_width, OnlyRightSubtree) { /*return True*/
    TreeNode* root = create_node(10);
    root->right = create_node(300);

    int width = calculate_subtree_width(root);
    EXPECT_EQ(width, 5);

    free_tree(root);
}

TEST(_calculate_subtree_width, EmptyTree) { /*return True*/
    TreeNode* root = NULL;

    int width = calculate_subtree_width(root);
    EXPECT_EQ(width, 0);
}

TEST(_create_node, CorrectValue) { /*all return True*/
    TreeNode* node = create_node(25);
    EXPECT_EQ(node->value, 25);
    EXPECT_EQ(node->width, 0);
    free_tree(node);
}

TEST(_create_node, InitialPointers) { /*all return True*/
    TreeNode* node = create_node(42);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free_tree(node);
}

TEST(_free_tree, SingleNode) { /*return True*/
    TreeNode* node = create_node(99);
    free_tree(node);
    SUCCEED();
}

TEST(_free_tree, NestedNodes) { /*return True*/
    TreeNode* root = create_node(10);
    root->left = create_node(20);
    root->right = create_node(30);
    root->left->left = create_node(40);
    root->left->right = create_node(50);

    free_tree(root);
    SUCCEED();
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	cout << "RUN TEST" << endl;

	return RUN_ALL_TESTS();
}