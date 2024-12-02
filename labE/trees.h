#pragma once

typedef struct Tree
{
	char* str;
	int width;//ширина дерева
	struct Tree* right;
	struct Tree* left;
} Tree;

int update_tree_width(Tree* T);
Tree* Create_tree(char* m[], int n, int index);

void Run_tests();
