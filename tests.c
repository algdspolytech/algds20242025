#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "functions.h"
#include "tests.h"


void test_create_node_zero_interval_return0() {
	interval interval = { 0, 0 };
	tree_node* tmp = create_node(interval);

	assert(tmp->left == 0 && tmp->right == 0 && tmp->maxEnd == 0);
}

void test_create_node_normal_interval_return0() {
	interval interval = { 1, 2 };
	tree_node* tmp = create_node(interval);

	assert(tmp->i.start == 1 && tmp->i.end == 2 && tmp->maxEnd == 2);
}

void test_insert_new_node_return0() {
	interval interval = { 1, 2 };
	tree_node* root = NULL;

	insert(&root, interval);

	assert(root->i.start == 1 && root->i.end == 2);
}

void test_insert_some_nodes_left_return0() {
	tree_node* root = NULL;

	interval interval1 = { 1, 2 };
	interval interval2 = { 3, 4 };


	insert(&root, interval1);
	insert(&root, interval2);

	assert(root->right->i.start == 3 && root->right->i.end == 4 && root->maxEnd == 4);
}

void test_insert_some_nodes_right_return0() {
	tree_node* root = NULL;

	interval interval1 = { 3, 4 };
	interval interval2 = { 1, 2 };


	insert(&root, interval1);
	insert(&root, interval2);

	assert(root->left->i.start == 1 && root->left->i.end == 2 && root->maxEnd == 4);
}

void test_insert_lots_nodes_return0() {
	tree_node* root = NULL;

	interval intervals[] = { {15, 20}, {23, 30}, {17, 19}, {5, 20} };
	for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); i++) {
		insert(&root, intervals[i]);
	}

	assert(root->maxEnd == 30);
}

void test_find_min_node_return0() {
	tree_node* root = NULL;

	interval intervals[] = { {15, 20}, {23, 30}, {17, 19}, {5, 20} };
	for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); i++) {
		insert(&root, intervals[i]);
	}

	tree_node* tmp = find_min_node(root);

	assert(tmp->i.start == 5 && tmp->i.end == 20);
}

void test_find_intersections_with_intersections_return0() {
	tree_node* root = NULL;

	interval intervals[] = { {15, 20}, {23, 30}, {17, 19}, {5, 20} };
	for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); i++) {
		insert(&root, intervals[i]);
	}

	interval query = { 6, 22 };

	interval* results = (interval*)malloc(300 * sizeof(interval));

	int len = 0;

	len = find_intersections(root, query, results);

	assert(len == 3);
}

void test_find_intersections_without_intersections_return0() {
	tree_node* root = NULL;

	interval intervals[] = { {15, 20}, {23, 30}, {17, 19}, {5, 20} };
	for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); i++) {
		insert(&root, intervals[i]);
	}

	interval query = { 1, 2 };

	interval* results = (interval*)malloc(300 * sizeof(interval));

	int len = 0;

	len = find_intersections(root, query, results);

	assert(len == 0);
}

void test_delete_node_return0() {
	tree_node* root = NULL;

	interval intervals[] = { {15, 20}, {23, 30}, {17, 19}, {5, 20} };
	for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); i++) {
		insert(&root, intervals[i]);
	}

	interval query = { 15, 20 };

	root = delete_node(root, query);

	assert(root->i.start == 17 && root->i.end == 19);
}
