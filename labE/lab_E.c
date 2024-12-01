#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int minLeafHeight;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->minLeafHeight = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int calculateMinLeafHeight(Node* root) {
    if (root == NULL)
        return INT_MAX;

    if (root->left == NULL && root->right == NULL) {
        root->minLeafHeight = 0;
        return 0;
    }

    int leftHeight = calculateMinLeafHeight(root->left);
    int rightHeight = calculateMinLeafHeight(root->right);

    int smallerHeight;
    if (leftHeight < rightHeight) {
        smallerHeight = leftHeight;
    }
    else {
        smallerHeight = rightHeight;
    }

    root->minLeafHeight = smallerHeight + 1;

    return root->minLeafHeight;
}

int treeHeight(Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    int largerHeight;
    if (leftHeight > rightHeight) {
        largerHeight = leftHeight;
    }
    else {
        largerHeight = rightHeight;
    }

    return largerHeight + 1;

}

void fillTreeLevel(Node* root, char** lines, int level, int start, int end) {
    if (root == NULL || start > end)
        return;

    int mid = (start + end) / 2;
    lines[level][mid] = '0' + root->minLeafHeight;

    fillTreeLevel(root->left, lines, level + 1, start, mid - 1);
    fillTreeLevel(root->right, lines, level + 1, mid + 1, end);
}

void printTreeToFilePyramid(Node* root, FILE* file) {
    if (root == NULL) {
        fprintf(file, "Empty tree\n");
        return;
    }

    int height = treeHeight(root);
    int width = pow(2, height) - 1;

    char** lines = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        lines[i] = (char*)malloc((width + 1) * sizeof(char));
        for (int j = 0; j < width; j++)
            lines[i][j] = ' ';
        lines[i][width] = '\0';
    }

    fillTreeLevel(root, lines, 0, 0, width - 1);

    for (int i = 0; i < height; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);
}

