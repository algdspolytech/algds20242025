#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "LabE.h"


TreeNode* create_tree(int data, int width, TreeNode* left, TreeNode* right) {
	TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
	if (!tree) return 0;

	tree->left = left;
	tree->right = right;
	tree->data = data;
	tree->width = width;

	return tree;
}

void free_tree(TreeNode* tree) {
	if (!tree) return;

	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}


static TreeNode* _rec_read_tree(int* data, int i, int length) {
	if (i >= length)
		return 0;

	return create_tree(data[i], 0, _rec_read_tree(data, 2 * i + 1, length), _rec_read_tree(data, 2 * i + 2, length));
}


// Function to read tree from file
TreeNode* read_tree(FILE* file) {
	int length = 0;
	int size = 2;
	int* data = (int*)malloc(sizeof(int) * size);

	int a = 0;
	while (fscanf(file, "%i", &a) != EOF) {
		if (length >= size) {
			size *= 2;
			data = (int*)realloc(data, sizeof(int)*size);
		}

		data[length] = a;
		length++;
	}
	data = (int*)realloc(data, length*sizeof(int));
	
	return _rec_read_tree(data, 0, length);
}

// Function to write tree's widths to file (for tests)
void write_tree_width(FILE* file, TreeNode* tree) {
	if (!tree || !file)
		return;

	fprintf(file, "%i ", tree->width);

	write_tree_width(file, tree->left);
	write_tree_width(file, tree->right);
}


static int max(int a, int b) {
	return a > b ? a : b;
}

static int get_depth(TreeNode* tree) {
	if (!tree)
		return 0;
	return 1 + max(get_depth(tree->left), get_depth(tree->right));
}

// Function to display tree with widths
void display_tree(TreeNode* tree) {

	int depth = get_depth(tree);
	int cur_length = 1;
	int next_size = 2;
	int next_length = 0;
	int symbol_width = 4;
	TreeNode** cur_line = (TreeNode**)malloc(sizeof(TreeNode*));
	TreeNode** next_line = (TreeNode**)malloc(sizeof(TreeNode*) * next_size);

	cur_line[0] = tree;

	int all_width = (pow(2, depth)) * (symbol_width + 1) + 1;

	for (int i = 0;i < depth;i++) {

		int items = cur_length;
		int tab = (all_width - symbol_width * items) /(pow(2, i+1));

		for (int j = 0;j < cur_length;j++) {
			for (int k = 0;k < tab;k++)
				printf(" ");
			if (j > 0)
				for (int k = 0;k < tab;k++)
					printf(" ");

			printf("%4i", cur_line[j]->data);
		}
		for (int k = 0;k < tab;k++)
			printf(" ");
		printf("\n");
		for (int j = 0;j < cur_length;j++) {
			for (int k = 0;k < tab;k++)
				printf(" ");
			if (j > 0)
				for (int k = 0;k < tab;k++)
					printf(" ");

			printf("%4i", cur_line[j]->width);
		}
		for (int k = 0;k < tab;k++)
			printf(" ");
		printf("\n");


		for (int j = 0;j < cur_length;j++) {
			if (next_length + 2 >= next_size) {
				next_size *= 2;
				next_line = (TreeNode**)realloc(next_line, sizeof(TreeNode*) * next_size);
			}
			next_line[next_length] = cur_line[j]->left;
			next_line[next_length + 1] = cur_line[j]->right;
			next_length += 2;
		}
		
		cur_line = (TreeNode**)realloc(cur_line, sizeof(TreeNode*) * next_size);
		for (int i = 0;i < next_length;i++)
			cur_line[i] = next_line[i];
		
		cur_length = next_length;
		next_length = 0;
	}
}


static int get_width(int number) {
	int width = 0;
	while (number) {
		width++;
		number /= 10;
	}
	return width;
}

// Calculating width
int calculate_width(TreeNode* tree) {
	if (!tree)
		return 0;
	tree->width = get_width(tree->data) + calculate_width(tree->right) + calculate_width(tree->left);
	return tree->width;
}