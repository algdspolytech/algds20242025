#include "min_height_of_subtrees.h"

// Функция для создания нового узла
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->min_leaf_height = -1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для вычисления минимальной высоты листьев в поддереве
int calculateMinLeafHeight(TreeNode* node) {
    if (node == NULL) {
        return -1;
    }

    if (node->left == NULL && node->right == NULL) {
        node->min_leaf_height = 0;
        return 0;
    }

    int left_min_height = calculateMinLeafHeight(node->left);
    int right_min_height = calculateMinLeafHeight(node->right);

    node->min_leaf_height = (left_min_height < right_min_height) ? left_min_height + 1 : right_min_height + 1;

    return node->min_leaf_height;
}

void visualizeTree(TreeNode* node) {
    if (node == NULL) {
        printf("()");
        return;
    }

    printf("(%d", node->value);
    if (node->left != NULL || node->right != NULL) {
        visualizeTree(node->left);
        visualizeTree(node->right);
    }
    printf(")");
}

TreeNode* createHeightTree(TreeNode* node) {
    if (node == NULL) {
        return NULL;
    }

    TreeNode* newNode = createNode(node->min_leaf_height);
    newNode->left = createHeightTree(node->left);
    newNode->right = createHeightTree(node->right);

    return newNode;
}
/*int main() {
    setlocale(LC_CTYPE, "Russian");

    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->left->left->left = createNode(7);
    root->left->left->right = createNode(8);

    calculateMinLeafHeight(root);

    printf("Исходное дерево:\n");
    visualizeTree(root);
    printf("\n");
    printf("\n");

    TreeNode* heightTree = createHeightTree(root);

    printf("Дерево из минимальных высот:\n");
    visualizeTree(heightTree);
    printf("\n");

    free(root->left->left->left);
    free(root->left->left->right);
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right->right);
    free(root->right);
    free(root);

    free(heightTree->left->left->left);
    free(heightTree->left->left->right);
    free(heightTree->left->left);
    free(heightTree->left->right);
    free(heightTree->left);
    free(heightTree->right->right);
    free(heightTree->right);
    free(heightTree);

    return 0;
}*/