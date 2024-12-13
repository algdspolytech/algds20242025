#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include "funcs.h"
#include "tests.h"


int main() {
    // Создаем дерево вручную
    TreeNode* root = createNode("root");
    root->left = createNode("left");
    root->right = createNode("right");
    root->left->left = createNode("child1");
    root->left->right = createNode("child2");
    root->right->right = createNode("child3");

    // Вычисляем ширину поддерева для каждого узла
    computeWidth(root);

    // Печатаем дерево с ширинами
    printTree(root, 0);

    // Освобождаем память
    freeTree(root);

    testEmptyTree_No1();
    testSingleNode_No2();
    testTwoLevelTree_No3();
    testAsymmetricTree_No4();
    testNodeWidths_No5();
    testLongWords_No6();
    testSingleLongWord_No7();
    testSingleSubtree_No8();
    testLargeTree_No9();
    testEmptyWord_No10();

    return 0;
}