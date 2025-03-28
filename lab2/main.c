#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>
#include "struct.h"
#include "tests.h"
#include "funcs.h"

#pragma warning(disable : 4996)

int main() {
    setlocale(LC_ALL, "Rus");
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->left->left->left = createNode(7);

    calculateMinLeafHeight(root);

    printf("Дерево после добавления min высоты листьев:\n");
    printTree(root);

    testSingleRoot_no1();
    testRootWithOneChild_no2();
    testFullBinaryTree_no3();
    testLeftHeavyTree_no4();
    testRightHeavyTree_no5();
    testTreeWithDifferentDepthLeaves_no6();
    testDeepBalancedTree_no7();
    testDeepLeftTree_no8();
    testEmptyTree_no9();
    testAllLeavesAtSameDepth_no10();

    printf("\n");
    printf("Все юнит-тесты пройдены успешно!\n");

    return 0;
}