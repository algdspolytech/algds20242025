#include <gtest/gtest.h>

extern "C" {
#include "tree.h"
}

bool is_valid_rb_tree(tree_t *tree, node_t *node, int black_count, int current_count) {
    if (node == tree->nil) return black_count == current_count;

    if (node->color == BLACK) current_count++;
    if (node->parent && node->color == RED && node->parent->color == RED) return false;

    return is_valid_rb_tree(tree, node->left, black_count, current_count) &&
           is_valid_rb_tree(tree, node->right, black_count, current_count);
}

bool validate_rb_tree(tree_t* tree) {
    if (!tree->root) return true;
    int cnt = 0;
    node_t *cur = tree->root;

    while(cur != tree->nil) {
        if (cur->color == BLACK)
            cnt++;
        cur = cur->left;
    }

    return is_valid_rb_tree(tree, tree->root, cnt, 0);
}

TEST(RBTreeTests, Insert_RootShouldBeBlack_No1) {
    tree_t *tree = tree_create();
    node_t *node = create_node(10, RED, tree->nil);
    insert(tree, node);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(tree->root->color, BLACK);
    EXPECT_EQ(tree->root->parent, tree->nil);

    
}

TEST(RBTreeTests, Fix_violations_ParentIsBlackNoFixNeeded_No2) {
    tree_t *tree = tree_create();
    node_t *root = create_node(20, BLACK, tree->nil);
    node_t *child = create_node(10, RED, tree->nil);

    tree->root = root;
    root->left = child;
    child->parent = root;

    fix_violations(tree, child);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(child->color, RED);
    EXPECT_EQ(child->parent, root);

    dispose_tree(tree);
}

TEST(RBTreeTests, Fix_violations_ParentAndUncleAreRed_No3) {
    tree_t *tree = tree_create();
    node_t *root = create_node(30, BLACK, tree->nil);
    node_t *left_child = create_node(20, RED, tree->nil);
    node_t *right_child = create_node(40, RED, tree->nil);
    node_t *grandchild = create_node(10, RED, tree->nil);

    tree->root = root;
    root->left = left_child;
    left_child->parent = root;
    root->right = right_child;
    right_child->parent = root;
    left_child->left = grandchild;
    grandchild->parent = left_child;

    fix_violations(tree, grandchild);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(left_child->color, BLACK);
    EXPECT_EQ(right_child->color, BLACK);
    EXPECT_EQ(grandchild->parent, left_child);
    dispose_tree(tree);
}

TEST(RBTreeTests, fix_violations_RightChildOfLeftParentRotatesLeft_No4) {
    tree_t *tree = tree_create();
    node_t *root = create_node(30, BLACK, tree->nil);
    node_t *left_child = create_node(20, RED, tree->nil);
    node_t *right_child_of_left = create_node(25, RED, tree->nil);

    tree->root = root;
    root->left = left_child;
    left_child->parent = root;
    left_child->right = right_child_of_left;
    right_child_of_left->parent = left_child;

    fix_violations(tree, right_child_of_left);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(tree->root, right_child_of_left);
    EXPECT_EQ(tree->root->color, BLACK);
    EXPECT_EQ(tree->root->left, left_child);
    EXPECT_EQ(tree->root->right, root);
    dispose_tree(tree);
}

TEST(RBTreeTests, fix_violations_LeftChildOfLeftParentRotatesRight_No5) {
    tree_t *tree = tree_create();
    node_t *root = create_node(30, BLACK, tree->nil);
    node_t *left_child = create_node(20, RED, tree->nil);
    node_t *left_left_child = create_node(10, RED, tree->nil);

    tree->root = root;
    root->left = left_child;
    left_child->parent = root;
    left_child->left = left_left_child;
    left_left_child->parent = left_child;

    fix_violations(tree, left_left_child);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(tree->root->left, left_left_child);
    EXPECT_EQ(tree->root->color, BLACK);
    EXPECT_EQ(tree->root->right, root);
    dispose_tree(tree);
}

TEST(RBTreeTests, Insert_MultipleInsertsShouldMaintainRedBlackProperties_No6) {
    tree_t *tree = tree_create();
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 33, 24, 66, 78};

    for (int v : values) {
        node_t* node = create_node(v, RED, tree->nil);
        insert(tree, node);
    }

    EXPECT_TRUE(validate_rb_tree(tree));
    dispose_tree(tree);
}

TEST(RBTreeTests, rb_remove_DeleteLeafNode_No7) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, RED, tree->nil);
    tree->root->right = create_node(15, RED, tree->nil);
    tree->root->left->parent = tree->root;
    tree->root->right->parent = tree->root;

    Node *nodeToDelete = findLUB(5, tree);
    rb_remove(tree, nodeToDelete);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(tree->root->left, tree->nil);
    EXPECT_EQ(tree->root->data, 10);
    EXPECT_EQ(tree->root->color, BLACK);
    dispose_tree(tree);
}

TEST(RBTreeTests, rb_remove_DeleteNodeWithOneChild_No8) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, BLACK, tree->nil);
    tree->root->right = create_node(15, BLACK, tree->nil);
    tree->root->left->right = create_node(7, RED, tree->nil);
    tree->root->left->parent = tree->root;
    tree->root->right->parent = tree->root;
    tree->root->left->right->parent = tree->root->left;

    node_t *nodeToDelete = findLUB(5, tree);
    rb_remove(tree, nodeToDelete);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(tree->root->left->data, 7);
    EXPECT_EQ(tree->root->left->color, BLACK);
    dispose_tree(tree);
}

TEST(RBTreeTests, rb_remove_DeleteNodeWithTwoChildren_No9) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, BLACK, tree->nil);
    tree->root->right = create_node(15, BLACK, tree->nil);
    tree->root->left->left = create_node(3, RED, tree->nil);
    tree->root->left->right = create_node(7, RED, tree->nil);
    tree->root->left->parent = tree->root;
    tree->root->right->parent = tree->root;
    tree->root->left->left->parent = tree->root->left;
    tree->root->left->right->parent = tree->root->left;

    Node *nodeToDelete = findLUB(5, tree);
    rb_remove(tree, nodeToDelete);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(tree->root->left->data, 7);
    EXPECT_EQ(tree->root->left->color, BLACK);
    dispose_tree(tree);
}

TEST(RBTreeTests, rb_remove_DeleteRootNode_No10) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, RED, tree->nil);
    tree->root->right = create_node(15, RED, tree->nil);
    tree->root->left->parent = tree->root;
    tree->root->right->parent = tree->root;

    Node *nodeToDelete = findLUB(10, tree);
    rb_remove(tree, nodeToDelete);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_NE(tree->root, tree->nil);
    EXPECT_TRUE(tree->root->data == 15 || tree->root->data == 5);
    EXPECT_EQ(tree->root->color, BLACK);
    dispose_tree(tree);
}

TEST(RBTreeTests, rb_remove_DeleteNodeCausingFixup_No11) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, BLACK, tree->nil);
    tree->root->right = create_node(20, BLACK, tree->nil);
    tree->root->right->left = create_node(15, RED, tree->nil);
    tree->root->right->right = create_node(25, RED, tree->nil);
    tree->root->left->parent = tree->root;
    tree->root->right->parent = tree->root;
    tree->root->right->left->parent = tree->root->right;
    tree->root->right->right->parent = tree->root->right;

    node_t *nodeToDelete = findLUB(25, tree);
    rb_remove(tree, nodeToDelete);

    EXPECT_TRUE(validate_rb_tree(tree));
    EXPECT_EQ(findLUB(25, tree), tree->nil);
    dispose_tree(tree);
}

TEST(RBTreeTests, findLUB_FindLUB_No12) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, BLACK, tree->nil);
    tree->root->right = create_node(15, BLACK, tree->nil);
    tree->root->left->left = create_node(3, RED, tree->nil);
    tree->root->left->right = create_node(7, RED, tree->nil);
    tree->root->right->left = create_node(12, RED, tree->nil);
    tree->root->right->right = create_node(20, RED, tree->nil);

    EXPECT_EQ(findLUB(6, tree)->data, 7);
    EXPECT_EQ(findLUB(10, tree)->data, 10);
    EXPECT_EQ(findLUB(14, tree)->data, 15);
    EXPECT_EQ(findLUB(2, tree)->data, 3);
    EXPECT_EQ(findLUB(20, tree)->data, 20);
    dispose_tree(tree);
}

TEST(RBTreeTests, findLUB_FindLUBReturnsNil_No13) {
    tree_t *tree = tree_create();
    tree->root = create_node(10, BLACK, tree->nil);
    tree->root->left = create_node(5, BLACK, tree->nil);
    tree->root->right = create_node(15, BLACK, tree->nil);
    tree->root->left->left = create_node(3, RED, tree->nil);
    tree->root->left->right = create_node(7, RED, tree->nil);
    tree->root->right->left = create_node(12, RED, tree->nil);
    tree->root->right->right = create_node(20, RED, tree->nil);

    EXPECT_EQ(findLUB(25, tree), tree->nil);
    EXPECT_EQ(findLUB(21, tree), tree->nil);
    dispose_tree(tree);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}