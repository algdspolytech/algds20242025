#include "headers/main.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(TreeTests, CreateTree_no1) {
  Node *root = CreateTree(0);
  EXPECT_EQ(root->data, 0);
  EXPECT_EQ(root->num_of_children, 0);
}

TEST(TreeTests, AddNodesToParent_no2) {
  Node *root = CreateTree(0);
  AddNode(root, 1);
  AddNode(root, 2);
  EXPECT_EQ(root->num_of_children, 2);
  EXPECT_EQ(root->nodes[0]->data, 1);
  EXPECT_EQ(root->nodes[1]->data, 2);
}

TEST(FuncTests, EmptyTree_no3) {
  Node *root = NULL;
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_TRUE(result == NULL);
}

TEST(FuncTests, TreeOnlyWithRoot_no4) {
  Node *root = CreateTree(0);
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_EQ(result->data, 0);
  EXPECT_EQ(result->num_of_children, 0);
}

TEST(FuncTests, TreeWithRootAndLeafes_no5) {
  Node *root = CreateTree(0);
  for (int i = 1; i < 4; i++) {
    AddNode(root, i);
  }
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_EQ(result->data, 0);
  EXPECT_EQ(result->num_of_children, 3);
}

TEST(FuncTests, TreeWithUniBranches_no6) {
  Node *root = CreateTree(0);

  for (int i = 1; i < 3; i++) {
    AddNode(root, i);
  }
  for (int i = 3; i < 5; i++) {
    AddNode(root->nodes[0], i);
  }
  for (int i = 5; i < 7; i++) {
    AddNode(root->nodes[1], i);
  }
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_EQ(result->data, 0);
  EXPECT_EQ(result->num_of_children, 2);
  EXPECT_EQ(result->nodes[0]->data, 1);
  EXPECT_EQ(result->nodes[1]->data, 2);
}

TEST(FuncTests, TreeWithDeepNesting_no7) {
  Node *root = CreateTree(0);
  Node *t = root;
  for (int i = 1; i < 8; i++) {
    AddNode(t, i);
    t = t->nodes[0];
  }
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_EQ(result->data, 0);
  EXPECT_EQ(result->num_of_children, 1);
}

TEST(FuncTests, TreeWithUnbalancedTree_no8) {
  Node *root = CreateTree(0);
  for (int i = 1; i < 3; i++) {
    AddNode(root, i);
  }
  for (int i = 3; i < 6; i++) {
    AddNode(root->nodes[0], i);
  }
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_EQ(result->data, 1);
  EXPECT_EQ(result->num_of_children, 3);
}

TEST(FuncTests, RandomTree_no9) {
  Node *root = CreateTree(1);
  for (int i = 2; i < 6; i++) {
    AddNode(root, i);
  }
  for (int i = 6; i < 9; i++) {
    AddNode(root->nodes[0], i);
  }
  for (int i = 9; i < 11; i++) {
    AddNode(root->nodes[1], i);
  }
  for (int i = 11; i < 12; i++) {
    AddNode(root->nodes[2], i);
  }
  for (int i = 12; i < 18; i++) {
    AddNode(root->nodes[3], i);
  }
  Node *result = FindNodeWithMostChildren(root);
  EXPECT_EQ(result->data, 5);
  EXPECT_EQ(result->num_of_children, 6);
}

TEST(PrintTests, PrintRandomTree_no10) {
  Node *root = CreateTree(1);
  cout << "This test simply shows the output \"in the form of Norton\", while the tree is output completely from the parent and across all descendants\n";
  for (int i = 2; i < 6; i++) {
    AddNode(root, i);
  }
  for (int i = 6; i < 9; i++) {
    AddNode(root->nodes[0], i);
  }
  for (int i = 9; i < 11; i++) {
    AddNode(root->nodes[1], i);
  }
  for (int i = 11; i < 12; i++) {
    AddNode(root->nodes[2], i);
  }
  for (int i = 12; i < 18; i++) {
    AddNode(root->nodes[3], i);
  }
  PrintTreeFromCurrentNode(root);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  cout << "RUN TEST" << endl;

  return RUN_ALL_TESTS();
}