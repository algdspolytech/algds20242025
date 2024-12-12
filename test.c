#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include "main.h"
#include "test.h"

// Тест 1: Проверка calculateWidth для однозначного числа
void TestDataWidth_SingleDigit_no1() {
    int result = calculateWidth(5);
    assert(result == 1 && "TestDataWidth_SingleDigit_no1 failed");
    printf("TestDataWidth_SingleDigit_no1 passed\n");
}

// Тест 2: Проверка calculateWidth для многозначного числа
void TestDataWidth_MultipleDigits_no2() {
    int result = calculateWidth(12345);
    assert(result == 5 && "TestDataWidth_MultipleDigits_no2 failed");
    printf("TestDataWidth_MultipleDigits_no2 passed\n");
}

// Тест 3: Проверка calculateSubtreeWidth для одного узла
void TestTreeWidth_SingleNode_no3() {
    TreeNode* tree = createNode(10); 
    calculateSubtreeWidth(tree);
    assert(tree->subtree_width == 2 && "TestTreeWidth_SingleNode_no3 failed"); 
    printf("TestTreeWidth_SingleNode_no3 passed\n");

    free(tree);
}

// Тест 4: Проверка calculateSubtreeWidth для нескольких узлов
void TestTreeWidth_MultipleNodes_no4() {
    TreeNode* tree = createNode(10);
    tree->left = createNode(5);
    calculateSubtreeWidth(tree);
    assert(tree->subtree_width == 3 && "TestTreeWidth_MultipleNodes_no4 failed"); 
    printf("TestTreeWidth_MultipleNodes_no4 passed\n");

    free(tree->left);
    free(tree);
}

// Тест 5: Проверка calculateTreeHeight для одного узла
void TestTreeHeight_SingleNode_no5() {
    TreeNode* tree = createNode(10);
    int result = calculateTreeHeight(tree);
    assert(result == 1 && "TestTreeHeight_SingleNode_no5 failed");
    printf("TestTreeHeight_SingleNode_no5 passed\n");

    free(tree);
}

// Тест 6: Проверка calculateTreeHeight для нескольких узлов
void TestTreeHeight_MultipleNodes_no6() {
    TreeNode* tree = createNode(10);
    tree->left = createNode(5);
    int result = calculateTreeHeight(tree);
    assert(result == 2 && "TestTreeHeight_MultipleNodes_no6 failed");
    printf("TestTreeHeight_MultipleNodes_no6 passed\n");

    free(tree->left);
    free(tree);
}

// Тест 7: Проверка digitToChar для корректной цифры
void TestIntToChar_ValidDigit_no7() {
    char result = digitToChar(5);
    assert(result == '5' && "TestIntToChar_ValidDigit_no7 failed");
    printf("TestIntToChar_ValidDigit_no7 passed\n");
}

// Тест 8: Проверка digitToChar для некорректной цифры
void TestIntToChar_InvalidDigit_no8() {
    char result = digitToChar(10);
    assert(result == '\0' && "TestIntToChar_InvalidDigit_no8 failed");
    printf("TestIntToChar_InvalidDigit_no8 passed\n");
}

// Тест 9: Проверка writeNumberToMatrix для однозначного числа
void TestWriteData_SingleDigit_no9() {
    char** matrix = (char**)malloc(sizeof(char*) * 1);
    matrix[0] = (char*)malloc(sizeof(char) * 2);
    matrix[0][0] = ' ';
    matrix[0][1] = '\0';

    writeNumberToMatrix(matrix, 1, 2, 0, 0, 5);
    assert(matrix[0][0] == '5' && "TestWriteData_SingleDigit_no9 failed");
    printf("TestWriteData_SingleDigit_no9 passed\n");

    free(matrix[0]);
    free(matrix);
}

// Тест 10: Проверка writeNumberToMatrix для многозначного числа
void TestWriteData_MultipleDigits_no10() {
    char** matrix = (char**)malloc(sizeof(char*) * 1);
    matrix[0] = (char*)malloc(sizeof(char) * 6);
    for (int i = 0; i < 5; i++) {
        matrix[0][i] = ' ';
    }
    matrix[0][5] = '\0';

    writeNumberToMatrix(matrix, 1, 6, 0, 0, 12345);
    assert(matrix[0][0] == '1' && matrix[0][1] == '2' && matrix[0][2] == '3' &&
           matrix[0][3] == '4' && matrix[0][4] == '5' && "TestWriteData_MultipleDigits_no10 failed");
    printf("TestWriteData_MultipleDigits_no10 passed\n");

    free(matrix[0]);
    free(matrix);
}
