#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <time.h>

#include <windows.h>

#include "functions.h"

#include "tests.h"

int main() {
	test_init_EmptyString_return0_no1();
	test_init_NotEmptyString_return0_no2();
	test_add_node_EmptyString_return0_no3();
	test_add_node_NotEmptyString_return0_no4();
	test_add_node_NullList_return0_no5();
	test_add_node_SeveralNodes_return0_no6();
	test_len_of_full_str_EmptyList_return0_no7();
	test_len_of_full_str_ListWithSeveralNotEmptyStrings_return0_no9();
	test_len_of_full_str_ListWithEmptyAndNotEmptyStrings_return0_no10();
	test_get_full_str_EmptyList_return0_no11();
	test_get_full_str_ListWithEmptyStrings_return0_no12();
	test_get_full_str_ListWithSeveralNotEmptyStrings_return0_no13();
	test_get_full_str_ListWithEmptyAndNotEmptyStrings_return0_no14();

	printf("All tests passed!\n");

	Node* head = NULL;
	head = init("First");
	add_node(head, "Second");
	add_node(head, "Third");
	add_node(head, ""); //space
	add_node(head, "Fourth");
	printf("list: ");
	print_list(head);
	printf("length of full string fro the list: %d\n", len_of_full_str(head));
	printf("full string from the list: %s\n", get_full_str(head));
	free_list(head);
}