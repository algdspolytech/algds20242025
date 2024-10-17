#ifndef TESTS_H
#define TESTS_H

#include "list.h"

void test_createNode_1();
void test_append_to_empty_list_2();
void test_append_to_non_empty_list_3();
void test_merge_two_sorted_lists_4();
void test_empty_merge_5();
void test_split_list_even_6();
void test_split_list_odd_7();
void test_mergeSort_randomlist_8();
void test_mergeSort_single_element_9();
void test_mergeSort_empty_list_10();
void test_mergeSort_sorted_list_11();
int compareLists(Node* list1, Node* list2);
void runTest(const char* testName, int result, const char* expected, const char* actual);
#endif
