#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "Treaps.h"
#include "Treaps.c"

TEST(CreateNodeTest, new_node_key_is_correct_no1) {
	Treap_t* t = CreateNode(1);
	EXPECT_EQ(t->key, 1);
}

TEST(CreateNodeTest, new_node_priority_is_valid_value_no2) {
	Treap_t* t = CreateNode(1);
	EXPECT_TRUE(t->priority >= 0 && t->priority <= RAND_MAX);
}

TEST(MergeTest, both_treaps_not_null_return_merged_treap_no3) {
	Treap_t t1 = { 3, 1, NULL, NULL };
	Treap_t t2 = { 2, 2, NULL, NULL };
	Treap_t* t = Merge(&t2, &t1);
	EXPECT_EQ(t, &t1);
	EXPECT_EQ(t->left, &t2);
}

TEST(MergeTest, one_treap_is_null_return_merged_treap_no4) {
	Treap_t t1 = { 3, 1, NULL, NULL };
	Treap_t* t = Merge(&t1, NULL);
	EXPECT_EQ(t, &t1);
	EXPECT_EQ(t->left, nullptr);
	EXPECT_EQ(t->left, nullptr);
}

TEST(SplitTest, key_is_in_treap_no5) {
	Treap_t t2 = { 1, 2, NULL, NULL };
	Treap_t t1 = { 3, 1, &t2, NULL };
	Treap_t *l, *r;
	Split(&t1, 3, &l, &r);
	EXPECT_EQ(l, &t2);
	EXPECT_EQ(r, &t1);
}

TEST(SplitTest, key_not_in_treap_no6) {
	Treap_t t2 = { 1, 2, NULL, NULL };
	Treap_t t1 = { 3, 1, &t2, NULL };
	Treap_t* l, * r;
	Split(&t1, 2, &l, &r);
	EXPECT_EQ(l, &t2);
	EXPECT_EQ(r, &t1);
}

TEST(AddTest, element_added_to_treap_no7) {
	Treap_t t1 = { 3, -1, NULL, NULL };
	Treap_t* t = Add(&t1, 1);
	EXPECT_EQ(t->left->key, 1);
}

TEST(FindTest, element_is_in_treap_return_pointer_to_element_no8) {
	Treap_t t2 = { 2, 2, NULL, NULL };
	Treap_t t1 = { 3, 1, &t2, NULL };
	Treap_t* el = Find(&t1, 2);
	EXPECT_EQ(el, t1.left);
}

TEST(FindTest, element_not_in_treap_return_null_no9) {
	Treap_t t2 = { 2, 2, NULL, NULL };
	Treap_t t1 = { 3, 1, &t2, NULL };
	Treap_t* el = Find(&t1, 4);
	EXPECT_EQ(el, nullptr);
}

TEST(DeleteTest, element_is_in_treap_element_deleted_no10) {
	Treap_t t2 = { 2, 2, NULL, NULL };
	Treap_t t1 = { 3, 1, &t2, NULL };
	Treap_t* t = Delete(&t1, 2);
	EXPECT_EQ(t->left, nullptr);
}

TEST(DeleteTest, element_not_in_treap_treap_unchanged_no11) {
	Treap_t t2 = { 2, 2, NULL, NULL };
	Treap_t t1 = { 3, 1, &t2, NULL };
	Treap_t* t = Delete(&t1, 5);
	EXPECT_EQ(t, &t1);
	EXPECT_EQ(t->left, &t2);
}