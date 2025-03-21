#include "AVLTree.h"

void measureTime(const char* testName, void (*testFunc)(void*), void* arg) {
    clock_t start = clock();
    testFunc(arg);
    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("%-20s: %.5f sec\n", testName, elapsed);
}

#define NUM_ELEMENTS 100000

void testRandomInsert(void* arg) {
    int isAVL = *(int*)arg;
    if (isAVL) {
        struct Node* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = insert(tree, rand());
    } else {
        BSTNode* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = BSTInsert(tree, rand());
    }
}

void testSortedInsert(void* arg) {
    int isAVL = *(int*)arg;
    if (isAVL) {
        struct Node* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = insert(tree, i);
    } else {
        BSTNode* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = BSTInsert(tree, i);
    }
}

void testSearch(void* arg) {
    int isAVL = *(int*)arg;
    if (isAVL) {
        struct Node* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = insert(tree, rand());
        for (int i = 0; i < NUM_ELEMENTS; i++)
            search(tree, rand());
    } else {
        BSTNode* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = BSTInsert(tree, rand());
        for (int i = 0; i < NUM_ELEMENTS; i++)
            BSTSearch(tree, rand());
    }
}

void testDelete(void* arg) {
    int isAVL = *(int*)arg;
    if (isAVL) {
        struct Node* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = insert(tree, rand());
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = deleteNode(tree, rand());
    } else {
        BSTNode* tree = NULL;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = BSTInsert(tree, rand());
        for (int i = 0; i < NUM_ELEMENTS; i++)
            tree = BSTDelete(tree, rand());
    }
}

int main() {
    srand(time(NULL));
    int isAVL;

    printf("=== AVL Tree Performance ===\n");
    isAVL = 1;
    measureTime("Random Insert", testRandomInsert, &isAVL);
    measureTime("Sorted Insert", testSortedInsert, &isAVL);
    measureTime("Search", testSearch, &isAVL);
    measureTime("Delete", testDelete, &isAVL);

    printf("\n=== BST Performance ===\n");
    isAVL = 0;
    measureTime("Random Insert", testRandomInsert, &isAVL);
    measureTime("Sorted Insert", testSortedInsert, &isAVL);
    measureTime("Search", testSearch, &isAVL);
    measureTime("Delete", testDelete, &isAVL);

    return 0;
}