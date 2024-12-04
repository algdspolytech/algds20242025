#include <stdlib.h>
#include <stdio.h>
#include "LabF.h"

IntervalNode* createNode(int start, int end) {
    IntervalNode* newNode = (IntervalNode*)malloc(sizeof(IntervalNode));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newNode->start = start;
    newNode->end = end;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

void insert(IntervalNode** root, int start, int end) {
    IntervalNode* newNode = createNode(start, end);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    IntervalNode* current = *root;
    IntervalNode* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (start < current->start) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (start < parent->start) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

IntervalNode* search(IntervalNode* root, int start, int end) {
    IntervalNode* current = root;
    while (current != NULL) {
        if (current->start == start && current->end == end) {
            return current;
        } else if (start < current->start) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void deleteNode(IntervalNode** root, int start, int end) {
    IntervalNode* nodeToDelete = search(*root, start, end);
    if (nodeToDelete == NULL) return;

    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) { // Лист
        if (nodeToDelete->parent != NULL) {
            if (nodeToDelete->parent->left == nodeToDelete) {
                nodeToDelete->parent->left = NULL;
            } else {
                nodeToDelete->parent->right = NULL;
            }
        }
        free(nodeToDelete);
    } else if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) { // Один потомок
        IntervalNode* child = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;
        if (nodeToDelete->parent != NULL) {
            if (nodeToDelete->parent->left == nodeToDelete) {
                nodeToDelete->parent->left = child;
            } else {
                nodeToDelete->parent->right = child;
            }
        }
        if (child != NULL) child->parent = nodeToDelete->parent;
        free(nodeToDelete);
    } else {
        IntervalNode* minRight = nodeToDelete->right;
        IntervalNode* minRightParent = nodeToDelete;
        while (minRight->left != NULL) {
            minRightParent = minRight;
            minRight = minRight->left;
        }

        nodeToDelete->start = minRight->start;
        nodeToDelete->end = minRight->end;

        if (minRightParent == nodeToDelete) {
            nodeToDelete->right = minRight->right;
            if (minRight->right != NULL) minRight->right->parent = nodeToDelete;
        } else {
            minRightParent->left = minRight->right;
            if (minRight->right != NULL) minRight->right->parent = minRightParent;
        }
        free(minRight);
    }
}

void findOverlappingIntervals(IntervalNode* root, int queryStart, int queryEnd, IntervalNode** result, int *count) {
  IntervalNode* current = root;
  while(current != NULL){
    if( (queryStart <= current->end && queryEnd >= current->start)){
      result[*count] = current;
      (*count)++;
    }
    if(queryStart < current->start){
      current = current->left;
    } else {
      current = current->right;
    }
  }
}

void freeTree(IntervalNode* root) {
    if (root == NULL) return;

    IntervalNode* current = root;
    IntervalNode* next;
    while (current != NULL) {
        if (current->left != NULL) {
            next = current->left;
            while (next->right != NULL) {
                next = next->right;
            }
            next->right = current->right;
            free(current);
            current = next->right;
        } else {
            next = current->right;
            free(current);
            current = next;
        }
    }
}
