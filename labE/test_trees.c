#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<assert.h>
#include"trees.h"

void test_update_tree_width_OneKnot_no1()
{
	Tree T = { "root", 0, NULL, NULL};
	update_tree_width(&T);

	assert(T.width == 4);
	printTree(&T, 0);
}

void test_update_tree_width_TwoLevels_no2()
{
	char* s[] = { "root", "left", "right" };
	Tree T = { s[1], 0, NULL, NULL };
	Tree T1 = { s[2], 0, NULL, NULL };
	Tree T2 = { s[0], 0, &T1, &T };

	update_tree_width(&T2);

	assert(T.width == 4);
	assert(T1.width == 5);
	assert(T2.width == 13);

	printf("\n");
	printf("\n");
	printTree(&T2, 0);
}

void test_update_tree_width_UnbalancedTree_no3()
{
	char* s[] = { "root", "left", NULL, "left1", NULL, NULL, NULL};
	Tree T = { s[3], 0, NULL, NULL };
	Tree T1 = { s[4], 0, NULL, NULL };
	Tree T2 = { s[5], 0, NULL, NULL };
	Tree T3 = { s[6], 0, NULL, NULL };
	Tree T4 = { s[1], 0, &T1, &T };
	Tree T5 = { s[2], 0, &T3, &T2 };
	Tree T6 = { s[0], 0, &T5, &T4 };

	update_tree_width(&T6);

	assert(T.width == 5);
	assert(T1.width == 0);
	assert(T2.width == 0);
	assert(T3.width == 0);
	assert(T4.width == 9);
	assert(T5.width == 0);
	assert(T6.width == 13);

	printf("\n");
	printf("\n");
	printTree(&T6, 0);
}

void test_update_tree_width_3levels_no4()
{
	char* s[] = { "root", "left", "right", "afc", "f", "dkj", "k" };
	Tree T = { s[3], 0, NULL, NULL };
	Tree T1 = { s[4], 0, NULL, NULL };
	Tree T2 = { s[5], 0, NULL, NULL };
	Tree T3 = { s[6], 0, NULL, NULL };
	Tree T4 = { s[1], 0, &T1, &T };
	Tree T5 = { s[2], 0, &T3, &T2 };
	Tree T6 = { s[0], 0, &T5, &T4 };

	update_tree_width(&T6);

	assert(T.width == 3);
	assert(T1.width == 1);
	assert(T2.width == 3);
	assert(T3.width == 1);
	assert(T4.width == 8);
	assert(T5.width == 9);
	assert(T6.width == 21);

	printf("\n");
	printf("\n");
	printTree(&T6, 0);
}

void test_update_tree_width_EmptyTree_no5()
{
	char* s[] = { NULL };
	Tree T = { s[0], 0, NULL, NULL };

	update_tree_width(&T);

	assert(T.width == 0);

	printf("\n");
	printf("\n");
	printTree(&T, 0);
}

void test_Create_tree_Onelevel_no6()
{
	char* s[] = { "root" };

	Tree* T = Create_tree(s, 1, 0);

	assert(T->left == NULL);
	assert(T->right == NULL);
	assert(T->str == "root");
	assert(T->width == 0);
}

void test_Create_tree_UnbalancedTree_no7()
{
	char* s[] = { "root", "left", NULL, "left1", NULL, NULL, NULL };

	Tree* T = Create_tree(s, 7, 0);

	assert(strcmp(T->str, "root") == 0);
	assert(strcmp(T->left->str, "left") == 0);
	assert(T->right == NULL);
	assert(strcmp(T->left->left->str, "left1") == 0);
	assert(T->left->right == NULL);
}


void test_Create_tree_full_no8() 
{
	char* s[] = { "root", "left", "right", "a", "b", "c", "d" };

	Tree* T = Create_tree(s, 7, 0);

	assert(T != NULL);
	assert(strcmp(T->str, "root") == 0);
	assert(strcmp(T->left->str, "left") == 0);
	assert(strcmp(T->right->str, "right") == 0);
	assert(strcmp(T->left->left->str, "a") == 0);
	assert(strcmp(T->left->right->str, "b") == 0);
	assert(strcmp(T->right->left->str, "c") == 0);
	assert(strcmp(T->right->right->str, "d") == 0);
}

void test_update_tree_width_LongNode_no9()
{
	char* s[] = { "supercalifragilisticexpialidocious" };

	Tree T = { s[0], 0, NULL, NULL };

	update_tree_width(&T);

	assert(T.width == strlen(s[0]));

	printf("\n");
	printf("\n");
	printTree(&T, 0);
}

void test_Create_tree_DeepUnbalancedTree_no10()
{
	char* s[] = { "root", "left", NULL, "left1", NULL, NULL, NULL, "left2", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "left3" };

	Tree* T = Create_tree(s, 16, 0);

	assert(strcmp(T->str, "root") == 0);
	assert(strcmp(T->left->str, "left") == 0);
	assert(T->right == NULL);
	assert(strcmp(T->left->left->str, "left1") == 0);
	assert(T->left->right == NULL);
	assert(strcmp(T->left->left->left->str, "left2") == 0);
	assert(T->left->left->right == NULL);
	assert(strcmp(T->left->left->left->left->str, "left3") == 0);
}


void Run_tests()
{
	test_update_tree_width_OneKnot_no1();
	test_update_tree_width_TwoLevels_no2();
	test_update_tree_width_UnbalancedTree_no3();
	test_update_tree_width_3levels_no4();
	test_update_tree_width_EmptyTree_no5();
	test_Create_tree_Onelevel_no6();
	test_Create_tree_UnbalancedTree_no7();
	test_Create_tree_full_no8();
	test_update_tree_width_LongNode_no9();
	test_Create_tree_DeepUnbalancedTree_no10();

	printf("All tests were successful!\n");
}