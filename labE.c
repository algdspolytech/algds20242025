#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tree.h"

TreeNode* createNode(const char* word) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        perror("Ошибка выделения памяти для нового узла");
        exit(EXIT_FAILURE);
    }

    newNode->word = (char*)malloc(strlen(word) + 1);
    if (newNode->word == NULL) {
        perror("Ошибка выделения памяти для слова");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->word, word);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->width = strlen(word); // Начальная ширина - длина слова
    return newNode;
}

TreeNode* insert(TreeNode* root, const char* word) {
    if (root == NULL) {
        return createNode(word);
    }
    if (strcmp(word, root->word) < 0 ||
        (strcmp(word, root->word) == 0 && strlen(word) < strlen(root->word))) {
        root->left = insert(root->left, word);
    }
    else {
        root->right = insert(root->right, word);
    }
    return root;
}


int calculateWidth(TreeNode* node) {
    if (node == NULL) return 0;

    // Сумма ширины левого и правого поддеревьев
    int leftWidth = calculateWidth(node->left);
    int rightWidth = calculateWidth(node->right);
    return leftWidth + rightWidth + node->width;
}

void printTree(TreeNode* node, FILE* out) {
    if (node == NULL) return;
    printTree(node->left, out);
    fprintf(out, "%s\n%d\n", node->word, node->width);
    printTree(node->right, out);
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;
    free(node->word);
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int execute_algorithm() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    TreeNode* root = NULL;
    size_t bufferSize = 100;
    char* buffer = (char*)malloc(bufferSize * sizeof(char)); 

    if (buffer == NULL) {
        perror("Ошибка выделения памяти");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    // Чтение строк из файла
    while (fgets(buffer, bufferSize, inputFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // Удаление символа новой строки
        root = insert(root, buffer);
    }

    free(buffer); 

    calculateWidth(root);
    printTree(root, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    freeTree(root); 

    return EXIT_SUCCESS;
}