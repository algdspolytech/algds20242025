#ifndef LABF_H
#define LABF_H

typedef struct IntervalNode {
    int start;
    int end;
    struct IntervalNode *left;
    struct IntervalNode *right;
    struct IntervalNode *parent;
} IntervalNode;

void insert(IntervalNode** root, int start, int end);

IntervalNode* search(IntervalNode* root, int start, int end);

void deleteNode(IntervalNode** root, int start, int end);

void findOverlappingIntervals(IntervalNode* root, int queryStart, int queryEnd, IntervalNode** result, int *count);

void freeTree(IntervalNode* root);

#endif
