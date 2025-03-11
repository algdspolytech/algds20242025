#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void runTests() {
    Node* root = NULL;

    // 1. Element Addition Test
    root = insert(root, 5);
    printf("Test 1: %s\n", root->data == 5 ? "Passed" : "Failed");

    // 2. The test of adding multiple elements
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 6);
    printf("Test 2: ");
    inorder(root);
    printf("\n");

    // 3. The test of finding an existing element
    printf("Test 3: %s\n", search(root, 4) ? "Passed" : "Failed");

    // 4. The search test for a non-existent element
    printf("Test 4: %s\n", search(root, 10) ? "Failed" : "Passed");

    // 5. Test for deleting an existing element
    root = deleteNode(root, 4);
    printf("Test 5: ");
    inorder(root);
    printf("\n");

    // 6. Root Element Removal Test
    root = deleteNode(root, 5);
    printf("Test 6: ");
    inorder(root);
    printf("\n");

    // 7. Test for deleting a non-existent element
    root = deleteNode(root, 10);
    printf("Test 7: ");
    inorder(root);
    printf("\n");

    // 8. Empty Tree processing Test
    printf("Test 8: %s\n", search(NULL, 1) ? "Failed" : "Passed");

    // 9. Duplicate addition Test
    root = insert(root, 5);
    root = insert(root, 5);
    printf("Test 9: ");
    inorder(root);
    printf("\n");

    // 10. Full bypass test after operations
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = deleteNode(root, 20);
    printf("Test 10: ");
    inorder(root);
    printf("\n");
}

int main() {
    runTests();
    return 0;
}
