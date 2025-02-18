#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int start;
	int end;
} Interval;

typedef struct IntervalNode {
	Interval interval;
	int maxEnd;
	struct IntervalNode* left;
	struct IntervalNode* right;
} IntervalNode;

bool doOverlap(int start1, int end1, int start2, int end2);
IntervalNode* createNode(int start, int end);
void updateMaxEnd(IntervalNode* node);
IntervalNode* insertInterval(IntervalNode* root, int start, int end);
IntervalNode* findMinNode(IntervalNode* root);
IntervalNode* deleteInterval(IntervalNode* root, int start, int end);
IntervalNode* findInterval(IntervalNode* root, int start, int end);
void findAllOverlappingIntervals(IntervalNode* root, int start, int end);
void freeIntervalTree(IntervalNode* root);