#pragma once
#ifndef TESTS_H
#define TESTS_H

void test_avl_insert_ascending();
void test_avl_insert_random();
void test_avl_delete_leaf();
void test_avl_delete_node_with_two_children();
void test_avl_search_existing();
void test_avl_search_non_existing();
void test_avl_balance_after_insertions();
void test_avl_duplicate_insert();
void test_avl_complex_operations();

#endif