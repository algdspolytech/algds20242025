#include <stdio.h>
#include <stdlib.h>
#include "lab5.h"
#include "test.h"



node_t* CreateNode(interval_t interval) {
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->interval = interval;
    newNode->max_end = interval.end;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void UpdateMaxEnd(node_t* node) {
    if (node == NULL) return;
    int leftMax = (node->left != NULL) ? node->left->max_end : node->interval.end;
    int rightMax = (node->right != NULL) ? node->right->max_end : node->interval.end;
    node->max_end = (leftMax > rightMax) ? leftMax : rightMax;
}

node_t* DeleteInterval(node_t* root, interval_t interval) {
    if (root == NULL) return NULL;

    if (interval.start == root->interval.start && interval.end == root->interval.end) {   // node has been found
        if (root->left == NULL) {              //one subtree or zero
            node_t* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node_t* temp = root->left;
            free(root);
            return temp;
        }

        else {
            node_t* minNode = root->right;      //two subtree. find min in right one
            while (minNode->left != NULL) {
                minNode = minNode->left;
            }

            root->interval = minNode->interval;       //copy node

            root->right = DeleteInterval(root->right, minNode->interval);  //delete node
        }
    }

    else if (interval.start < root->interval.start) {               //if interval is less, go to the left
        root->left = DeleteInterval(root->left, interval);
    }

    else if (interval.start >= root->interval.start) {         //if more or equal - to the right
        root->right = DeleteInterval(root->right, interval);
    }

    UpdateMaxEnd(root);   //new max_end
    return root;
}

node_t* InsertInterval(node_t* node, interval_t interval) {
    if (node == NULL) {
        return CreateNode(interval);
    }

    if (interval.start < node->interval.start) {
        node->left = InsertInterval(node->left, interval);
    }
    else {
        node->right = InsertInterval(node->right, interval);
    }

    if (node->max_end < interval.end) {  //new max_end
        node->max_end = interval.end;
    }

    return node;
}

int IsIntersection(interval_t i1, interval_t i2) {
    return (i1.start <= i2.end && i2.start <= i1.end);
}

interval_t* SearchIntersections(node_t* node, interval_t interval, interval_t* result, int* count) {
    if (node == NULL) {
        if (*count == 0) {
            free(result);
            return NULL;
        }
        else return result;
    }
        

    if (IsIntersection(node->interval, interval)) {   //with node
        result[*count] = node->interval;
        (*count)++;
    }

    if (node->left != NULL && node->left->max_end >= interval.start) {  //with left
        result = SearchIntersections(node->left, interval,result, count);
    }

    result = SearchIntersections(node->right, interval, result,count); //with right

    return result;
}

int main() {
    tests();
    printf("Test succeeded\n");
    return 0;
}