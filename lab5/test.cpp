#include "gtest/gtest.h"
#include "leafheight.h"

/*
Branch* createBranch(int value);

int minLeafHeight(Branch* root);

void updateMinLeafHeights(Branch* root);

void printTreeToFile(Branch* root, int space, FILE* file);
*/

TEST(CreateBranchTest, CorrectValue) {
	Branch* branch = createBranch(1);
	EXPECT_EQ(branch->value,1);
	clearTree(branch);
}

TEST(ClearTreeTest, NullInput) {
	EXPECT_DEATH(clearTree(NULL), "Null Pointer Input");
}

TEST(ClearTreeTest, OneBranch) {
	Branch* branch = createBranch(1);
	clearTree(branch);
}

TEST(ClearTreeTest, MultipleBranches) {
	Branch* branch = createBranch(1);
	branch->left = createBranch(2);
	clearTree(branch);
}

TEST(MinLeafHeightTest, EmptyTree) {
	EXPECT_EQ(minLeafHeight(NULL), -1);
}

TEST(MinLeafHeightTest, OneBranch) {
	Branch* branch = createBranch(1);
	EXPECT_EQ(minLeafHeight(branch), 0);
	clearTree(branch);
}

TEST(MinLeafHeightTest, MultipleBranches) {
	Branch* branch = createBranch(1);
	branch->left = createBranch(2);
	branch->right = createBranch(3);
	branch->left->left = createBranch(4);
	EXPECT_EQ(minLeafHeight(branch),1);
}

TEST(updateMinLeafHeightsTest, MultipleBranches) {
	Branch* branch = createBranch(1);
	branch->left = createBranch(2);
	branch->right = createBranch(3);
	branch->left->left = createBranch(4);
	EXPECT_EQ(minLeafHeight(branch), 1);
	EXPECT_EQ(minLeafHeight(branch->left), 1);
	EXPECT_EQ(minLeafHeight(branch->right), 0);
	EXPECT_EQ(minLeafHeight(branch->left->left), 0);
}

TEST(PrintTreeTest, OneBranch) {
	FILE* file = fopen("test_tree.txt", "w");
	Branch* branch = createBranch(1);
	printTreeToFile(branch, 0, file);
	fclose(file);
	clearTree(branch);
}

TEST(PrintTreeTest, MultipleBranches) {
	FILE* file = fopen("test_tree.txt", "w");
	Branch* branch = createBranch(1);
	branch->left = createBranch(2);
	branch->right = createBranch(3);
	printTreeToFile(branch, 0, file);
	fclose(file);
	clearTree(branch);
}