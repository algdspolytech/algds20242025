#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct TreeNode {
	int data;

	int width;

	TreeNode* left;
	TreeNode* right;
}; // Binary tree structure

// Creates tree
TreeNode* create_tree(int data, int width, TreeNode* left, TreeNode* right);
// Free memory
void free_tree(TreeNode* tree);
// Function to read tree from file
TreeNode* read_tree(FILE* file);
// Function to write tree's widths to file (for tests)
void write_tree_width(FILE* file, TreeNode* tree);
// Function to display tree with widths
void display_tree(TreeNode* tree);
// Calculating width
int calculate_width(TreeNode* tree);