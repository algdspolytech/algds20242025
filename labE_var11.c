#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h> // для rand()

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

void saveTree(Node* root, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing!\n");
        return;
    }
    if (root != NULL) {
        fprintf(fp, "%d ", root->data);
        saveTree(root->left, filename);
        saveTree(root->right, filename);
    }
    fclose(fp);
}

Node* loadTree(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for reading!\n");
        return NULL;
    }
    Node* root = NULL;
    int data;
    while (fscanf(fp, "%d", &data) == 1) {
        root = insert(root, data);
    }
    fclose(fp);
    return root;
}

void printTree(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        printTree(root->left);
        printTree(root->right);
    }
}


//Тесты
void AddToEmptyTree_no1() {
    Node* root = NULL;
    root = insert(root, 10);
    assert(root->data == 10);
}

void AddMultipleToEmptyTree_no2() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    assert(root->data == 10);
    assert(root->left->data == 5);
    assert(root->right->data == 15);
}

void SaveAndLoadTree_no3() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    saveTree(root, "test_tree.txt");
    Node* loadedRoot = loadTree("test_tree.txt");
    assert(loadedRoot->data == 10);
    assert(loadedRoot->left->data == 5);
    assert(loadedRoot->right->data == 15);
    remove("test_tree.txt");
}

void LoadEmptyFile_no4() {
    Node* root = loadTree("empty.txt"); 
    assert(root == NULL);
    remove("empty.txt");

}

void SaveEmptyTree_no5() {
    Node* root = NULL;
    saveTree(root, "empty_tree.txt");
    FILE* fp = fopen("empty_tree.txt", "r");
    assert(fp != NULL);
    fclose(fp);
    remove("empty_tree.txt");
}


void InsertDuplicates_no6() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 10);
    assert(root->data == 10);
    assert(root->left == NULL);
    assert(root->right == NULL); 
}

void LargeTree_no7() {
    Node* root = NULL;
    for (int i = 0; i < 100; ++i) {
        root = insert(root, i);
    }
    assert(root != NULL);
}

void NegativeNumbers_no8() {
    Node* root = NULL;
    root = insert(root, -10);
    root = insert(root, -5);
    root = insert(root, -15);
    assert(root->data == -10);
    assert(root->left->data == -15);
    assert(root->right->data == -5);
}


void ZeroValue_no9() {
    Node* root = NULL;
    root = insert(root, 0);
    assert(root->data == 0);
}


void PrintEmptyTree_no10() {
    Node* root = NULL;
    printTree(root); 
    assert(1);
}

void PrintSingleNodeTree_no11() {
    Node* root = NULL;
    root = insert(root, 5);
    printTree(root);
    assert(1);
}

void LoadCorruptedFile_no12() {
    FILE* fp = fopen("corrupted.txt", "w");
    fprintf(fp, "abc");
    fclose(fp);

    Node* root = loadTree("corrupted.txt");
    assert(root == NULL);
    remove("corrupted.txt");
}


void StressTest_no13() {
    Node* root = NULL;
    for (int i = 0; i < 1000; ++i) {
        root = insert(root, rand() % 2000 - 1000); 
    }
    saveTree(root, "stress_test.txt");
    Node* loaded = loadTree("stress_test.txt");
    assert(loaded != NULL); 
    remove("stress_test.txt");
}

int main() {
    AddToEmptyTree_no1();
    AddMultipleToEmptyTree_no2();
    SaveAndLoadTree_no3();
    LoadEmptyFile_no4();
    SaveEmptyTree_no5();
    InsertDuplicates_no6();
    LargeTree_no7();
    NegativeNumbers_no8();
    ZeroValue_no9();
    PrintEmptyTree_no10();
    PrintSingleNodeTree_no11();
    LoadCorruptedFile_no12();
    StressTest_no13();
    printf("All tests passed!\n");
    return 0;
}