#include "Header.h"

// Функция для создания нового узла
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->minLeafHeight = 1;  // значение по умолчанию
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для вычисления минимальной высоты листа в поддеревье
int minLeafHeight(Node* root) {
    if (root == NULL)
        return -1;  // Пустое дерево не имеет высоты

    // Если узел — это лист, его высота равна 0
    if (root->left == NULL && root->right == NULL)
        return 0;

    int leftHeight = minLeafHeight(root->left);
    int rightHeight = minLeafHeight(root->right);

    if (root->left == NULL) return rightHeight + 1;
    if (root->right == NULL) return leftHeight + 1;

    return (leftHeight < rightHeight ? leftHeight : rightHeight) + 1;
}

// Функция для обновления минимальной высоты листьев в поддеревьях
void updateMinLeafHeights(Node* root) {
    if (root == NULL)
        return;

    root->minLeafHeight = minLeafHeight(root);
    updateMinLeafHeights(root->left);
    updateMinLeafHeights(root->right);
}

// Функция для печати дерева в файл
void printTreeToFile(Node* root, int space, FILE* file) {
    if (root == NULL)
        return;

    space += 5;
    printTreeToFile(root->right, space, file);

    fprintf(file, "\n");
    for (int i = 5; i < space; i++) {
        fprintf(file, " ");
    }
    fprintf(file, "%d\n", root->minLeafHeight);

    printTreeToFile(root->left, space, file);
}
