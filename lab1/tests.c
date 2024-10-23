#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <time.h>

#include <windows.h>

#include <assert.h>

#include "functions.h"


void test_init_EmptyString_return0_no1() {
	Node* head = NULL;
	head = init("");
	assert(strcmp(head->str, "") == 0 && head->next == NULL);
}

void test_init_NotEmptyString_return0_no2() {
	Node* head = NULL;
	head = init("test_string");
	assert(strcmp(head->str, "test_string") == 0 && head->next == NULL);
}

void test_add_node_EmptyString_return0_no3() {
	Node* head = init("test");
	add_node(head, "");
	assert(strcmp(head->next->str, "") == 0 && head->next->next == NULL);
}

void test_add_node_NotEmptyString_return0_no4() {
	Node* head = init("test");
	add_node(head, "test_string");
	assert(strcmp(head->next->str, "test_string") == 0 && head->next->next == NULL);
}

void test_add_node_NullList_return0_no5() {
	Node* head = NULL;
	add_node(head, "test_string");
	assert(head == NULL);
}

void test_add_node_SeveralNodes_return0_no6() {
	Node* head = init("test");
	add_node(head, "test_string1");
	add_node(head, "test_string2");
	add_node(head, "test_string3");

	assert(strcmp(head->next->str, "test_string1") == 0);
	assert(strcmp(head->next->next->str, "test_string2") == 0);
	assert(strcmp(head->next->next->next->str, "test_string3") == 0 && head->next->next->next->next == NULL);

}

void test_len_of_full_str_EmptyList_return0_no7() {
	Node* head = NULL;
	assert(len_of_full_str(head) == 0);
}

void test_len_of_full_str_ListWithEmptyStrings_return0_no8() {
	Node* head = init("");
	add_node(head, "");
	add_node(head, "");
	add_node(head, "");
	assert(len_of_full_str(head) == 0);
}

void test_len_of_full_str_ListWithSeveralNotEmptyStrings_return0_no9() {
	Node* head = init("test1");
	add_node(head, "test12");
	add_node(head, "test123");
	add_node(head, "test1234");
	assert(len_of_full_str(head) == 26);
}

void test_len_of_full_str_ListWithEmptyAndNotEmptyStrings_return0_no10() {
	Node* head = init("test1");
	add_node(head, "");
	add_node(head, "test123");
	add_node(head, "");
	add_node(head, "");
	add_node(head, "");
	assert(len_of_full_str(head) == 12);
}

void test_get_full_str_EmptyList_return0_no11() {
	Node* head = NULL;
	assert(strcmp(get_full_str(head), "") == 0);
}

void test_get_full_str_ListWithEmptyStrings_return0_no12() {
	Node* head = init("");
	add_node(head, "");
	add_node(head, "");
	add_node(head, "");
	add_node(head, "");
	add_node(head, "");
	assert(strcmp(get_full_str(head), "") == 0);
}

void test_get_full_str_ListWithSeveralNotEmptyStrings_return0_no13() {
	Node* head = init("test1");
	add_node(head, "test2");
	add_node(head, "test3");
	add_node(head, "test4");
	assert(strcmp(get_full_str(head), "test1test2test3test4") == 0);
}

void test_get_full_str_ListWithEmptyAndNotEmptyStrings_return0_no14() {
	Node* head = init("test1");
	add_node(head, "");
	add_node(head, "test3");
	add_node(head, "");
	add_node(head, "");
	add_node(head, "");
	assert(strcmp(get_full_str(head), "test1test3") == 0);
}