#include "Header.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Тест: Создание узла
void TestCreateNode_no1() {
    Node* node = createNode(5);
    printf("TestCreateNode_no1 = %s\n", (node != NULL && node->value == 5 && node->left == NULL && node->right == NULL) ? "Pass" : "Fail");
    free(node);
}

// Тест: Минимальная высота для пустого дерева
void TestMinLeafHeight_EmptyTree_no2() {
    int result = minLeafHeight(NULL);
    printf("TestMinLeafHeight_EmptyTree_no2 = %s\n", result == -1 ? "Pass" : "Fail");
}

// Тест: Минимальная высота для одного узла
void TestMinLeafHeight_SingleNode_no3() {
    Node* node = createNode(1);
    int result = minLeafHeight(node);
    printf("TestMinLeafHeight_SingleNode_no3 = %s\n", result == 0 ? "Pass" : "Fail");
    free(node);
}

// Тест: Минимальная высота для полного дерева высоты 2
void TestMinLeafHeight_FullTree_no4() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    int result = minLeafHeight(root);
    printf("TestMinLeafHeight_FullTree_no4 = %s\n", result == 1 ? "Pass" : "Fail");
    free(root->left);
    free(root->right);
    free(root);
}

// Тест: Минимальная высота для несимметричного дерева
void TestMinLeafHeight_AsymmetricTree_no5() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->left->left = createNode(3);
    int result = minLeafHeight(root);
    printf("TestMinLeafHeight_AsymmetricTree_no5 = %s\n", result == 2 ? "Pass" : "Fail");
    free(root->left->left);
    free(root->left);
    free(root);
}

// Тест: Обновление минимальных высот в поддеревьях
void TestUpdateMinLeafHeights_no6() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    updateMinLeafHeights(root);
    printf("TestUpdateMinLeafHeights_no6 = %s\n", (root->minLeafHeight == 1 && root->left->minLeafHeight == 0 && root->right->minLeafHeight == 0) ? "Pass" : "Fail");
    free(root->left);
    free(root->right);
    free(root);
}

// Тест: Печать дерева с одной вершиной
void TestPrintTree_SingleNode_no7() {
    FILE* file = fopen("test_tree.txt", "w");
    Node* root = createNode(1);
    updateMinLeafHeights(root);

    printTreeToFile(root, 0, file);

    fclose(file);
    printf("TestPrintTree_SingleNode_no7 = Pass\n");
    free(root);
}



// Тест: Печать полного дерева высоты 2
void TestPrintTree_FullTree_no8() {
    FILE* file = fopen("test_tree.txt", "w");
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    printTreeToFile(root, 0, file);
    fclose(file);
    printf("TestPrintTree_FullTree_no8 = Pass\n");
    free(root->left);
    free(root->right);
    free(root);
}

// Тест: Проверка минимальных высот для дерева с разными глубинами поддеревьев
void TestMinLeafHeight_UnbalancedTree_no9() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);      
    root->left->left->left = createNode(5);
    root->right->right = createNode(6);    

    updateMinLeafHeights(root);

    printf("TestMinLeafHeight_UnbalancedTree_no9 = %s\n",
        (root->minLeafHeight == 2 &&   
            root->left->minLeafHeight == 2 &&   
            root->right->minLeafHeight == 1 && 
            root->left->left->left->minLeafHeight == 0) ? "Pass" : "Fail"); 

    
    free(root->left->left->left);
    free(root->left->left);
    free(root->left);
    free(root->right->right);
    free(root->right);
    free(root);
}

// Тест: Обработка пустого файла при записи
void TestPrintTree_Empty_no10() {
    FILE* file = fopen("test_empty_tree.txt", "w");
    printTreeToFile(NULL, 0, file);
    fclose(file);
    printf("TestPrintTree_Empty_no10 = Pass\n");
}

// Функция для запуска всех тестов
void RunAllTests() {
    TestCreateNode_no1();
    TestMinLeafHeight_EmptyTree_no2();
    TestMinLeafHeight_SingleNode_no3();
    TestMinLeafHeight_FullTree_no4();
    TestMinLeafHeight_AsymmetricTree_no5();
    TestUpdateMinLeafHeights_no6();
    TestPrintTree_SingleNode_no7();
    TestPrintTree_FullTree_no8();
    TestMinLeafHeight_UnbalancedTree_no9();
    TestPrintTree_Empty_no10();
}

int main() {
    RunAllTests();
    return 0;
}
