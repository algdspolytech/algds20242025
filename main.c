#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "main.h"
#include "test.h"


// Функция для создания нового узла
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->subtree_width = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int calculateWidth(int number) {
    if (number == 0) {
        return 1; 
    }
    if (number < 0) {
        number = -number; 
    }
    return (int)log10(number) + 1; 
}

int calculateSubtreeWidth(TreeNode* node) {
    if (node == NULL) {
        return 0; 
    }

    // Рекурсивно вычисляем ширину левого и правого поддеревьев
    int leftWidth = calculateSubtreeWidth(node->left);
    int rightWidth = calculateSubtreeWidth(node->right);

    // Ширина текущего узла - это ширина его данных плюс ширина его поддеревьев
    node->subtree_width = calculateWidth(node->data) + leftWidth + rightWidth;

    // Возвращаем ширину текущего поддерева
    return node->subtree_width;
}
// Рекурсивная функция для вычисления высоты бинарного дерева
int calculateTreeHeight(TreeNode* node) {
    if (node == NULL) {
        return 0; // Высота пустого дерева равна 0
    }

    // Рекурсивно вычисляем высоту левого и правого поддеревьев
    int leftHeight = calculateTreeHeight(node->left);
    int rightHeight = calculateTreeHeight(node->right);

    // Высота дерева - это максимум из высот левого и правого поддеревьев плюс 1 (текущий узел)
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Функция для преобразования цифры в символ
char digitToChar(int digit) {
    if (digit < 0 || digit > 9) {
        return '\0'; 
    }
    return '0' + digit; 
}

// Функция для записи числа в матрицу, начиная с позиции (x, y)
void writeNumberToMatrix(char** matrix, int rows, int cols, int x, int y, int number) {
    if (x < 0 || y < 0 || x >= rows || y >= cols) {
        printf("Error: Position (%d, %d) is out of bounds.\n", x, y);
        return;
    }

    // Преобразуем число в строку
    char buffer[20]; // Достаточно для хранения числа любой длины
    sprintf(buffer, "%d", number);

    // Записываем число в матрицу посимвольно
    int i = 0;
    while (buffer[i] != '\0' && x < rows && y + i < cols) {
        matrix[x][y + i] = buffer[i];
        i++;
    }
}

// Рекурсивно строит текстовое представление дерева в матрице
void buildTextRepresentation(TreeNode* node, char** matrix, int rows, int cols, int x, int y) {
    if (node == NULL) {
        return; 
    }

    // Записываем данные текущего узла в матрицу
    writeNumberToMatrix(matrix, rows, cols, x, y, node->data);

    // Вычисляем высоту поддерева для определения позиции дочерних узлов
    int subtreeHeight = calculateTreeHeight(node) - 1;

    // Рекурсивно строим текстовое представление для левого поддерева
    if (node->left != NULL) {
        int leftChildX = x + 2; 
        int leftChildY = y - subtreeHeight; 
        buildTextRepresentation(node->left, matrix, rows, cols, leftChildX, leftChildY);
    }

    // Рекурсивно строим текстовое представление для правого поддерева
    if (node->right != NULL) {
        int rightChildX = x + 2; 
        int rightChildY = y + subtreeHeight; 
        buildTextRepresentation(node->right, matrix, rows, cols, rightChildX, rightChildY);
    }
}

// Выводит визуальное представление дерева на консоль
void printTreeVisual(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    // Вычисляем высоту дерева
    int height = calculateTreeHeight(root);

    // Вычисляем ширину дерева
    int width = (1 << height) * 2 - 1; 

    // Создаем матрицу для визуализации
    char** matrix = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        matrix[i] = (char*)malloc(width * sizeof(char));
        for (int j = 0; j < width; j++) {
            matrix[i][j] = ' '; 
        }
    }

    buildTextRepresentation(root, matrix, height, width, 0, width / 2);

    // Выводим матрицу на консоль
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }

    // Освобождаем память
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {

    // Создаем бинарное дерево
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->right = createNode(20);

    // Выводим визуальное представление дерева
    printf("Visual representation of the tree:\n");
    printTreeVisual(root);

    // Выполняем юнит-тесты
    printf("\nRunning unit tests:\n");
    TestDataWidth_SingleDigit_no1();
    TestDataWidth_MultipleDigits_no2();
    TestTreeWidth_SingleNode_no3();
    TestTreeWidth_MultipleNodes_no4();
    TestTreeHeight_SingleNode_no5();
    TestTreeHeight_MultipleNodes_no6();
    TestIntToChar_ValidDigit_no7();
    TestIntToChar_InvalidDigit_no8();
    TestWriteData_SingleDigit_no9();
    TestWriteData_MultipleDigits_no10();

    // Освобождаем память
    free(root->left->left);
    free(root->left->right);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}