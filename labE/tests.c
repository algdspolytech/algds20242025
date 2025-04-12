#include <assert.h>
#include "labE.h"

void createNode_emptyTree_returnValidVal_no1() {
    Node* node = createNode();
    assert(node != NULL);
}

void createNode_newNodeLeafCountZero_returnValidVal_no2() {
    Node* node = createNode();
    assert(node->leafCount == 0);
}

void fillAndCountLeaves_nullInput_returnZero_no3() {
    assert(fillAndCountLeaves(NULL) == 0);
}

void fillAndCountLeaves_singleLeaf_returnOne_no4() {
    Node* node = createNode();
    assert(fillAndCountLeaves(node) == 1);
}

void fillAndCountLeaves_onlyLeftChild_returnOne_no5() {
    Node* node = createNode();
    node->left = createNode();
    assert(fillAndCountLeaves(node) == 1);
}

void fillAndCountLeaves_twoLeaves_returnTwo_no6() {
    Node* node = createNode();
    node->left = createNode();
    node->right = createNode();
    assert(fillAndCountLeaves(node) == 2);
}

void fillMatrix_singleNode_returnZero_no7() {
    Node* root = createNode();
    int width = (1 << (1 + 1)) - 1; // maxDepth = 0
    int** matrix = (int**)malloc(sizeof(int*));
    matrix[0] = (int*)malloc(width * sizeof(int));
    matrix[0][0] = -1; matrix[0][1] = -1; matrix[0][2] = -1;
    fillMatrix(root, matrix, 0, 1, 0, 0);
    assert(matrix[0][1] == 0);
}

void fillMatrix_leftChild_returnZero_no8() {
    Node* root = createNode();
    root->left = createNode();
    fillAndCountLeaves(root);
    int** matrix = (int**)malloc(2 * sizeof(int*));
    matrix[0] = (int*)malloc(3 * sizeof(int));
    matrix[1] = (int*)malloc(3 * sizeof(int));
    matrix[0][1] = -1; matrix[1][0] = -1;
    fillMatrix(root, matrix, 0, 1, 0, 1);
    assert(matrix[1][0] == 0);
}

void printTree_nullRoot_noCrash_no9() {
    Node* root = NULL;
    printTree(root, 0);
    assert(1); 
}

void printTree_singleNode_noCrash_no10() {
    Node* root = createNode();
    fillAndCountLeaves(root);
    printTree(root, 0);
    assert(1);
}
