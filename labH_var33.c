#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int key, int value) {
    if (root == NULL) {
        return createNode(key, value);
    }
    if (key <= root->key) {
        root->left = insert(root->left, key, value);
    }
    else {
        root->right = insert(root->right, key, value);
    }
    return root;
}

int findMaxInRange(Node* root, int low, int high) {
    if (root == NULL) return -1; 
    if (root->key < low) return findMaxInRange(root->right, low, high);
    if (root->key >= high) return findMaxInRange(root->left, low, high);

    int maxValue = root->value;
    int leftMax = findMaxInRange(root->left, low, high);
    int rightMax = findMaxInRange(root->right, low, high);

    if (leftMax > maxValue) maxValue = leftMax;
    if (rightMax > maxValue) maxValue = rightMax;

    return maxValue;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


void runTests() {
    Node* root = NULL;

    // Test 1: Adding an element to an empty tree
    root = insert(root, 10, 100);
    printf("Test 1: %s\n", findMaxInRange(root, 5, 15) == 100 ? "PASSED" : "FAILED");

    // Test 2: Adding multiple elements and finding the maximum
    root = insert(root, 20, 200);
    root = insert(root, 5, 50);
    printf("Test 2: %s\n", findMaxInRange(root, 5, 20) == 100 ? "PASSED" : "FAILED");

    // Test 3: Finding the maximum in a range without elements
    printf("Test 3: %s\n", findMaxInRange(root, 5, 10) == -1 ? "PASSED" : "FAILED");

    // Test 4: Finding the maximum in a range with one element
    root = insert(root, 10, 100);
    printf("Test 4: %s\n", findMaxInRange(root, 10, 11) == 100 ? "PASSED" : "FAILED");

    // Test 5: Finding the maximum with multiple elements
    root = insert(root, 15, 150);
    printf("Test 5: %s\n", findMaxInRange(root, 5, 15) == 100 ? "PASSED" : "FAILED");

    // Test 6: Finding the maximum outside the range
    printf("Test 6: %s\n", findMaxInRange(root, 0, 5) == -1 ? "PASSED" : "FAILED");

    // Test 7: Finding the maximum in a large range
    root = insert(root, 30, 300);
    printf("Test 7: %s\n", findMaxInRange(root, 0, 40) == 300 ? "PASSED" : "FAILED");

    // Test 8: Checking for negative values
    root = insert(root, -10, -100);
    root = insert(root, -20, -200);
    printf("Test 8: %s\n", findMaxInRange(root, -30, -5) == -100 ? "PASSED" : "FAILED");

    // Test 9: Empty tree when there is a range
    freeTree(root); 
    root = NULL; 
    printf("Test 9: %s\n", findMaxInRange(root, -10, -5) == -1 ? "PASSED" : "FAILED");

    // Test 10: Checking for equal keys with different values
    root = insert(root, 10, 100);
    root = insert(root, 10, 200);
    printf("Test 10: %s\n", findMaxInRange(root, 5, 15) == 200 ? "PASSED" : "FAILED");

    freeTree(root);
}

int main() {
    runTests();
    return 0;
}
