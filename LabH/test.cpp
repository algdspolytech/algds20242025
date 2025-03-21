#include "funcs.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

void inorder_collect(Node *root, int *result, int *index) {
  if (!root || root->key == -1)
    return;
  inorder_collect(root->left, result, index);
  result[(*index)++] = root->key;
  inorder_collect(root->right, result, index);
}

TEST(_insert, SingleElement) { // all return True
  Node *root = create_node(-1);

  root = insert(root, 10);

  int result[1], index = 0;
  inorder_collect(root, result, &index);
  int expected[] = {10};

  ASSERT_EQ(index, 1);
  EXPECT_EQ(result[0], expected[0]);

  free_tree(root);
}

TEST(_insert, MultipleElements) { // all return True
  Node *root = create_node(-1);

  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 7);

  int result[3], index = 0;
  inorder_collect(root, result, &index);
  int expected[] = {3, 5, 7};

  ASSERT_EQ(index, 3);
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(result[i], expected[i]);

  free_tree(root);
}

TEST(_insert, Duplicates) { // all return True
  Node *root = create_node(-1);

  root = insert(root, 5);
  root = insert(root, 5);
  root = insert(root, 5);

  int result[3], index = 0;
  inorder_collect(root, result, &index);
  int expected[] = {5, 5, 5};

  ASSERT_EQ(index, 3);
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(result[i], expected[i]);

  free_tree(root);
}

TEST(_erase, LeafNode) { // all return True
  Node *root = create_node(10);
  root->left = create_node(5);
  root->right = create_node(15);

  root = erase(root, 5);

  int result[2], index = 0;
  inorder_collect(root, result, &index);
  int expected[] = {10, 15};

  ASSERT_EQ(index, 2);
  for (int i = 0; i < 2; i++)
    EXPECT_EQ(result[i], expected[i]);

  free_tree(root);
}

TEST(_erase, NodeWithTwoChildren) { // return True
  Node *root = create_node(10);
  root->left = create_node(5);
  root->right = create_node(15);

  root = erase(root, 10);

  EXPECT_TRUE(root->key == 5 || root->key == 15);

  free_tree(root);
}

TEST(_erase, NonExistingNode) { // return True
  Node *root = create_node(10);
  root->left = create_node(5);
  root->right = create_node(15);

  root = erase(root, 100);

  int result[3], index = 0;
  inorder_collect(root, result, &index);
  int expected[] = {5, 10, 15};

  ASSERT_EQ(index, 3);
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(result[i], expected[i]);

  free_tree(root);
}

TEST(_merge, TwoEmptyTrees) { // return True
  Node *left = create_node(-1);
  Node *right = create_node(-1);

  Node *merged = merge(left, right);

  EXPECT_EQ(merged->key, -1);

  free_tree(merged);
}

TEST(_merge, NonEmptyWithEmpty) { // return True
  Node *left = create_node(10);
  Node *right = create_node(-1);

  Node *merged = merge(left, right);

  EXPECT_EQ(merged->key, 10);

  free_tree(merged);
}

TEST(_merge, DifferentPriority) { // all return True
  Node *left = create_node(10);
  Node *right = create_node(20);

  left->priority = 100;
  right->priority = 50;

  Node *merged = merge(left, right);

  EXPECT_EQ(merged->key, 10);
  EXPECT_EQ(merged->right->key, 20);

  free_tree(merged);
}

TEST(_merge, EqualPriority) { // all return True
  Node *left = create_node(10);
  Node *right = create_node(20);

  left->priority = 75;
  right->priority = 75;

  Node *merged = merge(left, right);

  int result[2], index = 0;
  inorder_collect(merged, result, &index);

  int expected1[] = {10, 20};
  int expected2[] = {20, 10};

  ASSERT_EQ(index, 2);
  EXPECT_TRUE((result[0] == expected1[0] && result[1] == expected1[1]) ||
              (result[0] == expected2[0] && result[1] == expected2[1]));

  free_tree(merged);
}

TEST(_split, ByMinValue) { // all return True
  Node *root = create_node(10);
  root->left = create_node(5);
  root->right = create_node(15);

  Node *left = create_node(-1);
  Node *right = create_node(-1);

  split(root, 5, &left, &right);

  int result_left[1], result_right[2], index_left = 0, index_right = 0;
  inorder_collect(left, result_left, &index_left);
  inorder_collect(right, result_right, &index_right);

  int expected_left[] = {5};
  int expected_right[] = {10, 15};

  ASSERT_EQ(index_left, 1);
  ASSERT_EQ(index_right, 2);

  EXPECT_EQ(result_left[0], expected_left[0]);
  EXPECT_EQ(result_right[0], expected_right[0]);
  EXPECT_EQ(result_right[1], expected_right[1]);

  free_tree(left);
  free_tree(right);
}

TEST(_split, ByMaxValue) { // all return True
  Node *root = create_node(10);
  root->left = create_node(5);
  root->right = create_node(15);

  Node *left = create_node(-1);
  Node *right = create_node(-1);

  split(root, 15, &left, &right);

  int result_left[3], result_right[1], index_left = 0, index_right = 0;
  inorder_collect(left, result_left, &index_left);
  inorder_collect(right, result_right, &index_right);

  int expected_left[] = {5, 10, 15};
  int expected_right[] = {};

  ASSERT_EQ(index_left, 3);
  ASSERT_EQ(index_right, 0);

  for (int i = 0; i < 3; i++)
    EXPECT_EQ(result_left[i], expected_left[i]);

  free_tree(left);
  free_tree(right);
}

TEST(_split, Middle) { // all return True
  Node *root = create_node(10);
  root->left = create_node(5);
  root->right = create_node(15);

  Node *left = create_node(-1);
  Node *right = create_node(-1);

  split(root, 10, &left, &right);

  int result_left[2], result_right[1], index_left = 0, index_right = 0;
  inorder_collect(left, result_left, &index_left);
  inorder_collect(right, result_right, &index_right);

  int expected_left[] = {5, 10};
  int expected_right[] = {15};

  ASSERT_EQ(index_left, 2);
  ASSERT_EQ(index_right, 1);

  EXPECT_EQ(result_left[0], expected_left[0]);
  EXPECT_EQ(result_left[1], expected_left[1]);
  EXPECT_EQ(result_right[0], expected_right[0]);

  free_tree(left);
  free_tree(right);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}