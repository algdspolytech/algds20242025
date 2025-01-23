#include <stdlib.h>
#include <stdio.h>
#include "interval_tree.h"

Node* createNewNode(int lower, int upper) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newNode->lowerBound = lower;
    newNode->upperBound = upper;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parentNode = NULL;
    return newNode;
}

void addInterval(Node** treeRoot, int lower, int upper) {
    Node* newNode = createNewNode(lower, upper);
    if (*treeRoot == NULL) {
        *treeRoot = newNode;
        return;
    }

    Node* currentNode = *treeRoot;
    Node* parentNode = NULL;

    while (currentNode != NULL) {
        parentNode = currentNode;
        if (lower < currentNode->lowerBound) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
    }

    newNode->parentNode = parentNode;
    if (lower < parentNode->lowerBound) {
        parentNode->leftChild = newNode;
    }
    else {
        parentNode->rightChild = newNode;
    }
}

Node* findInterval(Node* treeRoot, int lower, int upper) {
    Node* currentNode = treeRoot;
    while (currentNode != NULL) {
        if (currentNode->lowerBound == lower && currentNode->upperBound == upper) {
            return currentNode;
        }
        else if (lower < currentNode->lowerBound) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
    }
    return NULL;
}

void removeInterval(Node** treeRoot, int lower, int upper) {
    Node* nodeToRemove = findInterval(*treeRoot, lower, upper);
    if (nodeToRemove == NULL) return;

    if (nodeToRemove->leftChild == NULL && nodeToRemove->rightChild == NULL) { // Leaf node
        if (nodeToRemove->parentNode != NULL) {
            if (nodeToRemove->parentNode->leftChild == nodeToRemove) {
                nodeToRemove->parentNode->leftChild = NULL;
            }
            else {
                nodeToRemove->parentNode->rightChild = NULL;
            }
        }
        free(nodeToRemove);
    }
    else if (nodeToRemove->leftChild == NULL || nodeToRemove->rightChild == NULL) { // One child
        Node* childNode = (nodeToRemove->leftChild != NULL) ? nodeToRemove->leftChild : nodeToRemove->rightChild;
        if (nodeToRemove->parentNode != NULL) {
            if (nodeToRemove->parentNode->leftChild == nodeToRemove) {
                nodeToRemove->parentNode->leftChild = childNode;
            }
            else {
                nodeToRemove->parentNode->rightChild = childNode;
            }
        }
        if (childNode != NULL) childNode->parentNode = nodeToRemove->parentNode;
        free(nodeToRemove);
    }
    else {
        Node* minNode = nodeToRemove->rightChild;
        Node* minNodeParent = nodeToRemove;
        while (minNode->leftChild != NULL) {
            minNodeParent = minNode;
            minNode = minNode->leftChild;
        }

        nodeToRemove->lowerBound = minNode->lowerBound;
        nodeToRemove->upperBound = minNode->upperBound;

        if (minNodeParent == nodeToRemove) {
            nodeToRemove->rightChild = minNode->rightChild;
            if (minNode->rightChild != NULL) minNode->rightChild->parentNode = nodeToRemove;
        }
        else {
            minNodeParent->leftChild = minNode->rightChild;
            if (minNode->rightChild != NULL) minNode->rightChild->parentNode = minNodeParent;
        }
        free(minNode);
    }
}

void getOverlappingIntervals(Node* treeRoot, int queryLower, int queryUpper, Node** output, int* outputCount) {
    Node* currentNode = treeRoot;
    while (currentNode != NULL) {
        if ((queryLower <= currentNode->upperBound && queryUpper >= currentNode->lowerBound)) {
            output[*outputCount] = currentNode;
            (*outputCount)++;
        }
        if (queryLower < currentNode->lowerBound) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
    }
}

void releaseTree(Node* treeRoot) {
    if (treeRoot == NULL) return;

    Node* currentNode = treeRoot;
    Node* nextNode;
    while (currentNode != NULL) {
        if (currentNode->leftChild != NULL) {
            nextNode = currentNode->leftChild;
            while (nextNode->rightChild != NULL) {
                nextNode = nextNode->rightChild;
            }
            nextNode->rightChild = currentNode->rightChild;
            free(currentNode);
            currentNode = nextNode->rightChild;
        }
        else {
            nextNode = currentNode->rightChild;
            free(currentNode);
            currentNode = nextNode;
        }
    }
}
