
#include "binary_tree.h"

// Создание нового узла
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Вставка узла в бинарное дерево
TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Сохранение дерева в файл (префиксная запись)
int saveTreeToFile(TreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Не удалось открыть файл для записи");
        return 0;
    }

    // Префиксная запись с использованием '#' для NULL
    fprintf(file, "%d ", root ? root->data : '#');
    if (root) {
        saveTreeToFile(root->left, filename);
        saveTreeToFile(root->right, filename);
    }
    fclose(file);
    return 1;
}

// Загрузка дерева из файла
TreeNode* loadTreeFromFileHelper(FILE* file) {
    int data;
    if (fscanf(file, "%d ", &data) != 1) {
        return NULL;
    }
    if (data == '#') {
        return NULL;
    }
    TreeNode* node = createNode(data);
    node->left = loadTreeFromFileHelper(file);
    node->right = loadTreeFromFileHelper(file);
    return node;
}

TreeNode* loadTreeFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть файл для чтения");
        return NULL;
    }
    TreeNode* root = loadTreeFromFileHelper(file);
    fclose(file);
    return root;
}

// Префиксная печать дерева
void printTreePreOrder(TreeNode* root, FILE* stream) {
    if (root == NULL) {
        fprintf(stream, "# ");
        return;
    }
    fprintf(stream, "%d ", root->data);
    printTreePreOrder(root->left, stream);
    printTreePreOrder(root->right, stream);
}

// Инфиксная печать дерева
void printTreeInOrder(TreeNode* root, FILE* stream) {
    if (root == NULL) {
        return;
    }
    printTreeInOrder(root->left, stream);
    fprintf(stream, "%d ", root->data);
    printTreeInOrder(root->right, stream);
}

// Постфиксная печать дерева
void printTreePostOrder(TreeNode* root, FILE* stream) {
    if (root == NULL) {
        return;
    }
    printTreePostOrder(root->left, stream);
    printTreePostOrder(root->right, stream);
    fprintf(stream, "%d ", root->data);
}

// Освобождение памяти дерева
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
