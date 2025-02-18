#include <stdio.h>
#include "stdlib.h"
#include "LabF.h"

bool doOverlap(int start1, int end1, int start2, int end2) {
	return (start1 <= end2 && start2 <= end1);
}

IntervalNode* createNode(int start, int end) {
	IntervalNode* node = (IntervalNode*)malloc(sizeof(IntervalNode));
	if (!node) {
		fprintf(stderr, "Ошибка выделения памяти.\n");
		exit(EXIT_FAILURE);
	}
	node->interval.start = start;
	node->interval.end = end;
	node->maxEnd = end;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void updateMaxEnd(IntervalNode* node) {
	if (!node) return;

	int leftMax = node->left ? node->left->maxEnd : node->interval.end;
	int rightMax = node->right ? node->right->maxEnd : node->interval.end;

	int currentEnd = node->interval.end;
	int max = (currentEnd > leftMax) ? currentEnd : leftMax;
	if (rightMax > max) {
		max = rightMax;
	}
	node->maxEnd = max;
}

IntervalNode* insertInterval(IntervalNode* root, int start, int end) {
	if (root == NULL) {
		return createNode(start, end);
	}

	if (start < root->interval.start) {
		root->left = insertInterval(root->left, start, end);
	}
	else {
		root->right = insertInterval(root->right, start, end);
	}

	updateMaxEnd(root);
	return root;
}

IntervalNode* findMinNode(IntervalNode* root) {
	IntervalNode* current = root;
	while (current && current->left) {
		current = current->left;
	}
	return current;
}

IntervalNode* deleteInterval(IntervalNode* root, int start, int end) {
	if (root == NULL) {
		return NULL;
	}

	if (start < root->interval.start) {
		root->left = deleteInterval(root->left, start, end);
	}
	else if (start > root->interval.start) {
		root->right = deleteInterval(root->right, start, end);
	}
	else {
		if (end == root->interval.end) {
			if (root->left == NULL) {
				IntervalNode* temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL) {
				IntervalNode* temp = root->left;
				free(root);
				return temp;
			}
			else {
				IntervalNode* temp = findMinNode(root->right);
				root->interval.start = temp->interval.start;
				root->interval.end = temp->interval.end;
				root->right = deleteInterval(root->right, temp->interval.start, temp->interval.end);
			}
		}
	}


	updateMaxEnd(root);
	return root;
}

IntervalNode* findInterval(IntervalNode* root, int start, int end) {
	if (root == NULL) {
		return NULL;
	}

	if (start < root->interval.start) {
		return findInterval(root->left, start, end);
	}
	else if (start > root->interval.start) {
		return findInterval(root->right, start, end);
	}
	else {
		if (end == root->interval.end) {
			return root;
		}
		else if (end < root->interval.end) {
			return findInterval(root->left, start, end);
		}
		else {
			return findInterval(root->right, start, end);
		}
	}
}

void findAllOverlappingIntervals(IntervalNode* root, int start, int end) {
	if (root == NULL) {
		return;
	}

	if (doOverlap(root->interval.start, root->interval.end, start, end)) {
		printf("Пересекается: [%d, %d]\n", root->interval.start, root->interval.end);
	}

	if (root->left && root->left->maxEnd >= start) {
		findAllOverlappingIntervals(root->left, start, end);
	}

	if (root->right && root->interval.start <= end) {
		findAllOverlappingIntervals(root->right, start, end);
	}
}

void freeIntervalTree(IntervalNode* root) {
	if (!root) return;
	freeIntervalTree(root->left);
	freeIntervalTree(root->right);
	free(root);
}


