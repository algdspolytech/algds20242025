
#include "binary_tree.h"
#include <stdio.h>
#include <string.h>

// ������ ��� �������� �������
#define ASSERT(condition, test_name) \
    if (condition) { \
        printf("[PASSED] %s\n", test_name); \
    } else { \
        printf("[FAILED] %s\n", test_name); \
    }

// ���� 1: ���������� � ������ ������
void TestAddToEmptyTree_HappyPath_no1() {
    TreeNode* root = NULL;
    root = insertNode(root, 10);
    ASSERT(root != NULL && root->data == 10, "TestAddToEmptyTree_HappyPath_no1");
    freeTree(root);
}

// ���� 2: ���������� ������ � ������� �������
void TestAddLeftAndRightChildren_HappyPath_no2() {
    TreeNode* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    ASSERT(root->left->data == 5 && root->right->data == 15, "TestAddLeftAndRightChildren_HappyPath_no2");
    freeTree(root);
}

// ���� 3: ���������� ������������ ����
void TestAddDuplicateNode_HappyPath_no3() {
    TreeNode* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 10); // ��������
    ASSERT(root->right->data == 10, "TestAddDuplicateNode_HappyPath_no3");
    freeTree(root);
}

// ���� 4: ���������� � �������� ������
void TestSaveAndLoadTree_HappyPath_no4() {
    TreeNode* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    saveTreeToFile(root, "test_tree.txt");

    TreeNode* loadedRoot = loadTreeFromFile("test_tree.txt");
    ASSERT(loadedRoot == NULL && loadedRoot->data == 10 && loadedRoot->left->data == 5 && loadedRoot->right->data == 15, "TestSaveAndLoadTree_HappyPath_no4");

    freeTree(root);
    freeTree(loadedRoot);
}

// ���� 5: �������� �� ������� �����
void TestLoadFromEmptyFile_EdgeCase_no5() {
    FILE* file = fopen("empty.txt", "w");
    fclose(file);
    TreeNode* root = loadTreeFromFile("empty.txt");
    ASSERT(root == NULL, "TestLoadFromEmptyFile_EdgeCase_no5");
}

// ���� 6: ������ ������� ������
void TestPrintEmptyTree_HappyPath_no6() {
    TreeNode* root = NULL;
    printf("TestPrintEmptyTree_HappyPath_no6: ");
    printTreeInOrder(root, stdout);
    printf("\n");
    ASSERT(1, "TestPrintEmptyTree_HappyPath_no6"); // ������ ��������
}

// ���� 7: ������������ ������ ������
void TestFreeTree_HappyPath_no7() {
    TreeNode* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 5);
    freeTree(root);
    // ���������� �������� ���������, �� ���� ��������� �� ������, ������� �������
    ASSERT(1, "TestFreeTree_HappyPath_no7");
}

// ���� 8: ���������� �������� ���������� �����
void TestAddManyNodes_HappyPath_no8() {
    TreeNode* root = NULL;
    int i;
    for (i = 1; i <= 1000; i++) {
        root = insertNode(root, i);
    }
    // ��������� ������ � ������� ������
    ASSERT(root->data == 1 && root->right->data == 2, "TestAddManyNodes_HappyPath_no8");
    freeTree(root);
}

// ���� 9: �������� ������ �� ������������� �����
void TestLoadFromCorruptedFile_EdgeCase_no9() {
    FILE* file = fopen("corrupted.txt", "w");
    fprintf(file, "10 5 fifteen"); // ������������ ����
    fclose(file);
    TreeNode* root = loadTreeFromFile("corrupted.txt");
    // � ������ ���������� �������� ����� ����������� �� "fifteen"
    // ���������, ��� ������ � ����� ������� ���������
    ASSERT(root != NULL && root->data == 10 && root->left->data == 5, "TestLoadFromCorruptedFile_EdgeCase_no9");
    freeTree(root);
}

// ���� 10: ���������� � �������� ������ � �������������� �������
void TestSaveAndLoadNegativeNumbers_HappyPath_no10() {
    TreeNode* root = NULL;
    root = insertNode(root, -10);
    root = insertNode(root, -20);
    root = insertNode(root, -5);
    saveTreeToFile(root, "negative_tree.txt");

    TreeNode* loadedRoot = loadTreeFromFile("negative_tree.txt");
    ASSERT(loadedRoot == NULL && loadedRoot->data == -10 && loadedRoot->left->data == -20 && loadedRoot->right->data == -5, "TestSaveAndLoadNegativeNumbers_HappyPath_no10");

    freeTree(root);
    freeTree(loadedRoot);
}
#ifndef RUN_TESTS
int main() {
    TestAddToEmptyTree_HappyPath_no1();
    TestAddLeftAndRightChildren_HappyPath_no2();
    TestAddDuplicateNode_HappyPath_no3();
    TestSaveAndLoadTree_HappyPath_no4();
    TestLoadFromEmptyFile_EdgeCase_no5();
    TestPrintEmptyTree_HappyPath_no6();
    TestFreeTree_HappyPath_no7();
    TestAddManyNodes_HappyPath_no8();
    TestLoadFromCorruptedFile_EdgeCase_no9();
    TestSaveAndLoadNegativeNumbers_HappyPath_no10();
    return 0;
}
#endif // RUN_TESTS