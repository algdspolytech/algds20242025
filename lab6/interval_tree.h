#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

typedef struct Node {
    int lowerBound;
    int upperBound;
    struct Node* leftChild;
    struct Node* rightChild;
    struct Node* parentNode;
} Node;

void addInterval(Node** treeRoot, int lower, int upper);
Node* findInterval(Node* treeRoot, int lower, int upper);
void removeInterval(Node** treeRoot, int lower, int upper);
void getOverlappingIntervals(Node* treeRoot, int queryLower, int queryUpper, Node** output, int* outputCount);
void releaseTree(Node* treeRoot);

#endif
