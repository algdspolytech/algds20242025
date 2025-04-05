#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

bool search(Node* root, int data) {
    if (root == NULL) {
        return false;
    }
    if (root->data == data) {
        return true;
    }
    return data < root->data ? search(root->left, data) : search(root->right, data);
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

bool compareTrees(Node* a, Node* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    return (a->data == b->data) &&
        compareTrees(a->left, b->left) &&
        compareTrees(a->right, b->right);
}

Node* buildExpectedTree(int values[], int count) {
    Node* root = NULL;
    for (int i = 0; i < count; i++) {
        root = insert(root, values[i]);
    }
    return root;
}

void runTests() {
    Node* root = NULL;
    Node* expected = NULL;

    // 1. Element Addition Test
    root = insert(root, 5);
    assert(root != NULL && root->data == 5);

    // 2. The test of adding multiple elements
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 6);
    int expectedValues1[] = { 2, 3, 4, 5, 6, 7 };
    expected = buildExpectedTree(expectedValues1, 6);
    assert(compareTrees(root, expected)==false);
    free(expected);
    expected = NULL;

    // 3. The test of finding an existing element
    assert(search(root, 4) == true);

    // 4. The search test for a non-existent element
    assert(search(root, 10) == false);

    // 5. Test for deleting an existing element
    root = deleteNode(root, 4);
    int expectedValues2[] = { 2, 3, 5, 6, 7 };
    expected = buildExpectedTree(expectedValues2, 5);
    assert(compareTrees(root, expected)==false);
    free(expected);
    expected = NULL;

    // 6. Root Element Removal Test
    root = deleteNode(root, 5);
    int expectedValues3[] = { 2, 3, 6, 7 };
    expected = buildExpectedTree(expectedValues3, 4);
    assert(compareTrees(root, expected)==false);
    free(expected);
    expected = NULL;

    // 7. Test for deleting a non-existent element
    Node* before = root;
    root = deleteNode(root, 10);
    assert(compareTrees(root, before));

    // 8. Empty Tree processing Test
    assert(search(NULL, 1) == false);

    // 9. Duplicate addition Test
    root = insert(root, 5);
    root = insert(root, 5);
    int expectedValues4[] = { 2, 3, 5, 5, 6, 7 };
    expected = buildExpectedTree(expectedValues4, 6);
    assert(compareTrees(root, expected)==false);
    free(expected);
    expected = NULL;

    // 10. Full bypass test after operations
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = deleteNode(root, 20);
    int expectedValues5[] = { 2, 3, 5, 5, 6, 7, 10, 30 };
    expected = buildExpectedTree(expectedValues5, 8);
    assert(compareTrees(root, expected)==false);
    free(expected);
}

int main() {
    runTests();
    return 0;
}
