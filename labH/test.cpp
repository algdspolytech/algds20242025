#include "pch.h"
extern "C" {
#include "../lab5/rbtree.h"
}

bool isRedBlackTreeValidHelper(Node* node) {
    if (node == NULL)
        return true;

    if (node->color == RED) {
        if ((node->left != NULL && node->left->color == RED) ||
            (node->right != NULL && node->right->color == RED))
            return false;
    }
    return isRedBlackTreeValidHelper(node->left) &&
        isRedBlackTreeValidHelper(node->right);
}

bool isRedBlackTreeValid(Node* root) {
    if (root == NULL)
        return true;

    if (root->color != BLACK)
        return false;

    return isRedBlackTreeValidHelper(root);
}

TEST(CreateNodeRBTTest, CreatesNodeWithCorrectData_no1) {
    Node* node = createNodeRBT(52);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data, 52);
    EXPECT_EQ(node->color, RED);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    EXPECT_EQ(node->parent, nullptr);
    free(node);
}

TEST(GrandparentTest, GrandparentSuccess_no2) {
    Node* grandparentNode = createNodeRBT(52);
    Node* parentNode = createNodeRBT(666);
    Node* childNode = createNodeRBT(5);

    parentNode->parent = grandparentNode;
    childNode->parent = parentNode;

    EXPECT_EQ(grandparent(childNode), grandparentNode);

    free(grandparentNode);
    free(parentNode);
    free(childNode);
}

TEST(UncleTest, UncleIsRightChild_no3) {
    Node* grandparentNode = createNodeRBT(5252);
    Node* parentNode = createNodeRBT(26);
    Node* uncleNode = createNodeRBT(333);
    Node* childNode = createNodeRBT(666);

    grandparentNode->left = parentNode;
    grandparentNode->right = uncleNode;
    parentNode->parent = grandparentNode;
    uncleNode->parent = grandparentNode;
    childNode->parent = parentNode;

    EXPECT_EQ(uncle(childNode), uncleNode);

    free(grandparentNode);
    free(parentNode);
    free(uncleNode);
    free(childNode);
}

TEST(SiblingTest, SiblingIsLeftChild_no4) {
    Node* parentNode = createNodeRBT(117);
    Node* leftChild = createNodeRBT(1212);
    Node* rightChild = createNodeRBT(333);

    parentNode->left = leftChild;
    parentNode->right = rightChild;
    leftChild->parent = parentNode;
    rightChild->parent = parentNode;

    EXPECT_EQ(sibling(rightChild), leftChild);

    free(parentNode);
    free(leftChild);
    free(rightChild);
}

TEST(LeftRotateTest, RotatesCorrectly_no5) {
    Node* root = createNodeRBT(52);
    root->right = createNodeRBT(26);
    root->right->parent = root;

    leftRotate(&root, root);

    EXPECT_EQ(root->data, 26);
    EXPECT_EQ(root->left->data, 52);
    EXPECT_EQ(root->left->parent, root);

    free(root->left);
    free(root);
}

TEST(RightRotateTest, RotatesCorrectly_no6) {
    Node* root = createNodeRBT(18);
    root->left = createNodeRBT(45);
    root->left->parent = root;

    rightRotate(&root, root);

    EXPECT_EQ(root->data, 45);
    EXPECT_EQ(root->right->data, 18);
    EXPECT_EQ(root->right->parent, root);

    free(root->right);
    free(root);
}
TEST(BalanceInsertTest, UncleIsRed_no7) {
    Node* root = createNodeRBT(10);
    root->color = BLACK;

    Node* leftChild = createNodeRBT(5);
    leftChild->parent = root;
    root->left = leftChild;

    Node* rightChild = createNodeRBT(15);
    rightChild->parent = root;
    root->right = rightChild;

    Node* newNode = createNodeRBT(3);
    newNode->parent = leftChild;
    leftChild->left = newNode;

    balanceInsert(&root, newNode);

    EXPECT_TRUE(isRedBlackTreeValid(root));

    free(root);
    free(leftChild);
    free(rightChild);
    free(newNode);
}

TEST(InsertRBTTest, InsertsAndBalancesCorrectly_no8) {
    Node* root = NULL;
    insertRBT(&root, 10);
    insertRBT(&root, 20);
    insertRBT(&root, 30);
    insertRBT(&root, 15);
    insertRBT(&root, 25);

    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_EQ(root->left->data, 10);
    EXPECT_EQ(root->left->color, BLACK);
    EXPECT_EQ(root->right->data, 30);
    EXPECT_EQ(root->right->color, BLACK);
    EXPECT_EQ(root->right->left->data, 25);
    EXPECT_EQ(root->right->left->color, RED);
    EXPECT_EQ(root->left->right->data, 15);
    EXPECT_EQ(root->left->right->color, RED);

    free(root->left->right);
    free(root->left);
    free(root->right->left);
    free(root->right);
    free(root);
}

TEST(SearchRBTTest, FindsNodeCorrectly_no9) {
    Node* root = NULL;
    insertRBT(&root, 10);
    insertRBT(&root, 20);
    insertRBT(&root, 30);

    Node* found = searchRBT(root, 20);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->data, 20);

    found = searchRBT(root, 40);
    EXPECT_EQ(found, nullptr);

    free(root->left);
    free(root->right);
    free(root);
}

TEST(RBTreeTest, DeleteNodeTest_no10) {
    Node* root = NULL;

    insertRBT(&root, 10);
    insertRBT(&root, 20);
    insertRBT(&root, 30);
    insertRBT(&root, 15);
    insertRBT(&root, 25);

    EXPECT_TRUE(isRedBlackTreeValid(root));

    deleteRBT(&root, 20);

    EXPECT_TRUE(isRedBlackTreeValid(root));

    EXPECT_EQ(root->right->data, 30);
}