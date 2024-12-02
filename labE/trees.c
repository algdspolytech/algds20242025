#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include"trees.h"

int update_tree_width(Tree* T)
{
	if (T == NULL)
	{
		return 0;
	}

	int left_width = update_tree_width(T->left);
	int right_width = update_tree_width(T->right);

	if (T->str != NULL)
	{
		T->width = left_width + right_width + strlen(T->str);
	}
	else
	{
		T->width = 0;
	}
	//T->width = left_width + right_width + strlen(T->str);

	return T->width;
}

Tree* Create_tree(char* m[], int n, int index)
{
	if (index >= n || m[index] == NULL)
	{
		return NULL;
	}

	Tree* T = malloc(sizeof(Tree));
	if (T == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}
	T->str = m[index];
	T->width = 0;
	T->left = NULL;
	T->right = NULL;

	T->left = Create_tree(m, n, 2 * index + 1);
	T->right = Create_tree(m, n, 2 * index + 2);

	return T;
}

void printTree(Tree* node, int level) {
	if (node == NULL) {
		return; 
	}

	printTree(node->right, level + 1);

	for (int i = 0; i < level; i++) {
		printf("    "); 
	}
	printf("%s (%i)\n", node->str, node->width); 

	printTree(node->left, level + 1);
}

//// Освобождение памяти дерева
//void freeTree(Tree* node)
//{
//	if (node == NULL) {
//		return;
//	}
//	freeTree(node->left);
//	freeTree(node->right);
//	free(node);
//}

void main(void)
{
	setlocale(LC_ALL, "Russian");
	char* s[] = { "root", "left", "right", "a", NULL, "b", "c", "d" };

	Tree* T = Create_tree(s, 8, 0);
	update_tree_width(T);
	printTree(T, 0);

	Run_tests();
}