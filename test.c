#include "main.h"

void test1() {
    AVLNode* root = NULL;
    root = insert(root, 10);
    AVLNode* found = search(root, 10);
    assert(found != NULL && found->key == 10);
    printf("Test 1 passed: Single insertion and search\n");
    freeTree(root);
}

void test2() {
    AVLNode* root = NULL;
    int keys[] = { 20, 10, 30, 25, 40 };
    for (int i = 0; i < 5; i++) {
        root = insert(root, keys[i]);
    }
    AVLNode* found = search(root, 25);
    assert(found != NULL && found->key == 25);
    printf("Test 2 passed: Multiple insertions and search\n");
    freeTree(root);
}

void test3() {
    AVLNode* root = NULL;
    int keys[] = { 20, 10, 30 };
    for (int i = 0; i < 3; i++) {
        root = insert(root, keys[i]);
    }
    root = deleteNode(root, 10);
    AVLNode* found = search(root, 10);
    assert(found == NULL);
    printf("Test 3 passed: Deletion of a leaf node\n");
    freeTree(root);
}

void test4() {
    AVLNode* root = NULL;
    int keys[] = { 30, 20, 40, 10 }; 
    for (int i = 0; i < 4; i++) {
        root = insert(root, keys[i]);
    }
    root = deleteNode(root, 20);
    AVLNode* found = search(root, 20);
    assert(found == NULL);
    printf("Test 4 passed: Deletion of a node with one child\n");
    freeTree(root);
}

void test5() {
    AVLNode* root = NULL;
    int keys[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (int i = 0; i < 7; i++) {
        root = insert(root, keys[i]);
    }
    root = deleteNode(root, 50); 
    AVLNode* found = search(root, 50);
    assert(found == NULL);
    printf("Test 5 passed: Deletion of a node with two children\n");
    freeTree(root);
}

void test6() {
    AVLNode* root = NULL;
    int keys[] = { 30, 20, 10 };
    for (int i = 0; i < 3; i++) {
        root = insert(root, keys[i]);
    }
    assert(root != NULL && root->key == 20);
    printf("Test 6 passed: Right rotation (LL case)\n");
    freeTree(root);
}

void test7() {
    AVLNode* root = NULL;
    int keys[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (int i = 0; i < 7; i++) {
        root = insert(root, keys[i]);
    }
    root = deleteNode(root, 70);
    AVLNode* found = search(root, 70);
    assert(found == NULL);

    int keysRemain[] = { 50, 30, 20, 40, 60, 80 };
    for (int i = 0; i < 6; i++) {
        AVLNode* tmp = search(root, keysRemain[i]);
        assert(tmp != NULL);
    }
    printf("Test 7 passed: Complex insertion and deletion operations\n");
    freeTree(root);
}

void test8() {
    AVLNode* root = NULL;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 150);
    root = deleteNode(root, 100);
    assert(search(root, 100) == NULL);
    printf("Test 8 passed: Delete root node\n");
}

void test9() {
    AVLNode* root = NULL;
    for (int i = 1; i <= 1000; i++) {
        root = insert(root, i);
    }
    assert(height(root) < 20);
    printf("Test 9 passed: Large dataset remains balanced\n");
}

void test10() {
    AVLNode* root = NULL;
    root = insert(root, 10);
    root = deleteNode(root, 20);
    assert(root != NULL && root->key == 10);
    printf("Test 10 passed: Delete non-existing node\n");
}


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    printf("All tests passed\n");
    return 0;
}
