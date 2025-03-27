#include "pch.h"
#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>




extern "C" {
#include "..\Treap\treap.h"
}


/*

treapnode* createtreap(int* x, int* c, int size);

void addtreap(treapnode* root, int* sum, int a, int b);

int sumtreap(treapnode* root, int a, int b);
*/

TEST(TreapListTest, createpairs_ValidVal_ValidVal) {
	int a[2] = { 1, 2 };
	int b[2] = { 3,  4 };
	int** pairs = createpairs(2, a, b);
	EXPECT_TRUE(pairs[0][0] == 1 && pairs[0][1] == 3 
			&& pairs[1][0] == 2 && pairs[1][1] == 4);
}

TEST(TreapListTest, swap_ValidVal_ValidVal) {
	int a[2] = { 1, 2 };
	int b[2] = { 3,  4 };
	int** pairs = createpairs(2, a, b);
	swap(pairs, 0, 1);
	EXPECT_TRUE(pairs[0][0] == 2 && pairs[0][1] == 4 
			&& pairs[1][0] == 1 && pairs[1][1] == 3);
}

TEST(TreapListTest, qsortpairs_ValidVal_ValidVal) {
	int a[3] = { 1, 2, 3 };
	int b[3] = { 6, 4, 5 };
	int** pairs = createpairs(3, a, b);
	qsortpair(pairs, 0, 2);
	EXPECT_TRUE(pairs[0][0] == 1 && pairs[0][1] == 6 
			&& pairs[1][0] == 3 && pairs[1][1] == 5 
			&& pairs[2][0] == 2 && pairs[2][1] == 4);
}

TEST(TreapListTest, createtreapnode_ValidVal_ValidVal) {
	int x = 1;
	int c = 2;
	treapnode* tn = createtreapnode(x, c);
	EXPECT_TRUE(tn->x == 1 && tn->c == 2
		&& tn->left == NULL && tn->right == NULL);
}

TEST(TreapListTest, split_ValidVal_ValidVal) {
	int a[3] = { 1, 2, 3 };
	int b[3] = { 6, 4, 5 };
	treapnode* first = createtreapnode(a[0], b[0]);
	treapnode* second = createtreapnode(a[1], b[1]);
	treapnode* third = createtreapnode(a[2], b[2]);
	first->right = third;
	third->left = second;
	treapnode* lefttreap;
	treapnode* righttreap;
	split(first, 2, &lefttreap, &righttreap);
	EXPECT_TRUE(lefttreap == first && lefttreap->right == second
		&& first->left == NULL && second->left == NULL && second->right == NULL
		&& righttreap == third
		&& third->right == NULL && third->left == NULL);
}

TEST(TreapListTest, inserttreapnode_InvalidVal_newnode) {
	treapnode* tn = createtreapnode(1, 2);
	treapnode* nw = inserttreapnode(NULL, tn);
	EXPECT_TRUE(tn == nw);
}

TEST(TreapListTest, inserttreapnode_ValidVal_ValidVal) {
	int a[3] = { 1, 2, 3 };
	int b[3] = { 6, 4, 5 };
	treapnode* first = createtreapnode(a[0], b[0]);
	treapnode* second = createtreapnode(a[1], b[1]);
	treapnode* third = createtreapnode(a[2], b[2]);
	first->right = second;
	inserttreapnode(first, third);
	EXPECT_TRUE(first->right == third && third->left == second);
}

TEST(TreapListTest, createtreap_InvalidVal_NULL) {
	ASSERT_EQ(NULL, createtreap(NULL,NULL, 1));
}

TEST(TreapListTest, createtreap_ValidVal_ValidVal) {
	int a[3] = { 1, 2, 3 };
	int b[3] = { 6, 4, 5 };
	treapnode* root = createtreap(a, b, 3);
	EXPECT_TRUE(root->x == 1 && root ->c == 6 && root->left == NULL
		&& root->right->x == 3 && root->right->c == 5 && root->right->right == NULL
		&& root->right->left->x == 2 && root->right->left->c == 4 
		&& root->right->left->right == NULL && root->right->left->left == NULL);
}

TEST(TreapListTest, sumtreap_ValidVal_ValidVal) {
	int x[10] = { 1, 2, 3, 4, 5, 6,  7,  8,  8,  9 };
	int c[10] = { 1, 5, 7, 10,8, 83, 10, 23, 43, 50 };
	treapnode* treap = createtreap(x, c, 10);
	EXPECT_TRUE(sumtreap(treap, 5, 9) == 167);
}