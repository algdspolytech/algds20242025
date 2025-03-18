#include <stdio.h>
#include <stdlib.h>
#include "CartesianTree.c"
#include <gtest/gtest.h>

TEST(CreateNodeTest, NewNode_Correct_no1) {
CartesianTree_t* t = CreateNode(1);
EXPECT_EQ(t->key, 1);
}

TEST(CreateNodeTest, NewNode_ValidVal_no2) {
CartesianTree_t* t = CreateNode(1);
EXPECT_TRUE(t->priority >= 0 && t->priority <= RAND_MAX);
}

TEST(MergeTest, TwoTreaps_CorrectTreap_no3) {
CartesianTree_t t1 = { 3, 1, NULL, NULL };
CartesianTree_t t2 = { 2, 2, NULL, NULL };
CartesianTree_t* t = Merge(&t2, &t1);
EXPECT_EQ(t, &t1);
EXPECT_EQ(t->left, &t2);
}

TEST(MergeTest, FirstIsNull_CorrectTreap_no4) {
CartesianTree_t t1 = { 3, 1, NULL, NULL };
CartesianTree_t* t = Merge(&t1, NULL);
EXPECT_EQ(t, &t1);
EXPECT_EQ(t->left, nullptr);
EXPECT_EQ(t->left, nullptr);
}

TEST(SplitTest, KeyInTreap_no5) {
CartesianTree_t t2 = { 1, 2, NULL, NULL };
CartesianTree_t t1 = { 3, 1, &t2, NULL };
CartesianTree_t *l, *r;
Split(&t1, 3, &l, &r);
EXPECT_EQ(l, &t2);
EXPECT_EQ(r, &t1);
}

TEST(SplitTest, KeyNotInTreap_no6) {
CartesianTree_t t2 = { 1, 2, NULL, NULL };
CartesianTree_t t1 = { 3, 1, &t2, NULL };
CartesianTree_t* l, * r;
Split(&t1, 2, &l, &r);
EXPECT_EQ(l, &t2);
EXPECT_EQ(r, &t1);
}

TEST(AddTest, AddEl_Added_no7) {
CartesianTree_t t1 = { 3, -1, NULL, NULL };
CartesianTree_t* t = Add(&t1, 1);
EXPECT_EQ(t->left->key, 1);
}

TEST(FindTest, ElInTreap_Pointer_no8) {
CartesianTree_t t2 = { 2, 2, NULL, NULL };
CartesianTree_t t1 = { 3, 1, &t2, NULL };
CartesianTree_t* el = Find(&t1, 2);
EXPECT_EQ(el, t1.left);
}

TEST(FindTest, EllNotInTreap_Null_no9) {
CartesianTree_t t2 = { 2, 2, NULL, NULL };
CartesianTree_t t1 = { 3, 1, &t2, NULL };
CartesianTree_t* el = Find(&t1, 4);
EXPECT_EQ(el, nullptr);
}

TEST(DeleteTest, ElInTreap_Deleted_no10) {
CartesianTree_t t2 = { 2, 2, NULL, NULL };
CartesianTree_t t1 = { 3, 1, &t2, NULL };
CartesianTree_t* t = Delete(&t1, 2);
EXPECT_EQ(t->left, nullptr);
}
