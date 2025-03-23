#include <assert.h>
#include "Treap.h"

void TestCreate_no1() {
    Node* root = NULL;
    root = createNode(76);
    assert(root != NULL);
    assert(root->key == 76);
}

void TestGenerationKey_no2() {
    int key = generateRandomKey();
    assert(key>=0&&key<100);
}

void TestSplitTree_no3() {
    Node* root = NULL;
    root = insert(root, createNode(6));
    root = insert(root, createNode(4));
    root = insert(root, createNode(9));
    root = insert(root, createNode(2));
    root = insert(root, createNode(5));
    root = insert(root, createNode(10));

    Node* left = NULL;
    Node* right = NULL;

    split(root, 5, &left, &right);

    assert(left != NULL);
    assert(right != NULL);

    assert(left->key <= 5);
    if (left->left) {
        assert(left->left->key <= 5);
    }
    if (left->right) {
        assert(left->right->key <= 5);
    }

    assert(right->key > 5);
    if (right->left) {
        assert(right->left->key > 5);
    }
    if (right->right) {
        assert(right->right->key > 5);
    }
}

void TestInsertRandom_no4() {
    srand(time(NULL));
    Node* root = NULL;
    int key = generateRandomKey();
    Node* newNode = createNode(key);
    assert(newNode != NULL); 
    root = insert(root, newNode);
    assert(root != NULL); 
    assert(root->key == newNode->key);
}

void TestHeightTree_no5() {
    srand(time(NULL));
    Node* root = NULL;
    for (int i = 0; i < 10; i++) {
        int key = generateRandomKey();
        //printf("Inserting key: %d\n", key);
        root = insert(root, createNode(key));
    }
    int height_tree = height(root);
    assert(height_tree>0 && height_tree<=10);
}

void TestCountNodes_no6() {
    srand(time(NULL));
    Node* root = NULL;
    for (int i = 0; i < 10; i++) {
        int key = generateRandomKey();
        //printf("Inserting key: %d\n", key);
        root = insert(root, createNode(key));
    }
    int c_nodes = countNodes(root);
    assert(c_nodes > 0 && c_nodes <= 10);
}

void TestMergeTrees_no7() {
    Node* left = NULL;
    left = insert(left, createNode(4));
    left = insert(left, createNode(2));
    left = insert(left, createNode(3));

    Node* right = NULL;
    right = insert(right, createNode(8));
    right = insert(right, createNode(6));
    right = insert(right, createNode(10));

    Node* merged = merge(left, right);

    assert(merged != NULL);
    assert(countNodes(merged) == 7);
}

void TestSearch_no8() {
    srand(time(NULL));
    Node* root = NULL;
    for (int i = 0; i < 10; i++) {
        int key = i;
        //printf("Inserting key: %d\n", key);
        root = insert(root, createNode(key));
    }
    Node* found = search(root, 5);
    assert(found);
}

void TestDeleteEmptyTree_no9() {
    Node* root = NULL;

    root = delete(root, 5);

    assert(root == NULL);
}

void TestDelete_no10() {
    srand(time(NULL));
    Node* root = NULL;
    for (int i = 0; i < 10; i++) {
        int key = i;
        //printf("Inserting key: %d\n", key);
        root = insert(root, createNode(key));
    }
    Node* found = search(root, 5);
    assert(found != NULL); 
    root = delete(root, 5);
    assert(search(root, 5) == NULL);
}

void TestDeleteNonExistentKey_no11() {
    Node* root = NULL;
    root = insert(root, createNode(5));
    root = insert(root, createNode(3));
    root = insert(root, createNode(8));

    root = delete(root, 10);

    assert(root != NULL);
    assert(countNodes(root) == 3); 
}

void RunAllTests() {
    TestCreate_no1();
    TestGenerationKey_no2();
    TestSplitTree_no3();
    TestInsertRandom_no4();
    TestHeightTree_no5();
    TestCountNodes_no6();
    TestMergeTrees_no7();
    TestSearch_no8();
    TestDeleteEmptyTree_no9();
    TestDelete_no10();
    TestDeleteNonExistentKey_no11();
}

int main() {
    RunAllTests();
    return 0;
}
