#include "binary_tree.h"

// �������� ������ ����
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        fprintf(stderr, "������ ��������� ������\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ������� ���� � �������� ������
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

// ���������� ������ � ���� (���������� ������)
int saveTreeToFile(TreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("�� ������� ������� ���� ��� ������");
        return 0;
    }

    // ���������� ������ � �������������� '#' ��� NULL
    fprintf(file, "%d ", root ? root->data : '#');
    if (root) {
        saveTreeToFile(root->left, filename);
        saveTreeToFile(root->right, filename);
    }
    fclose(file);
    return 1;
}

// �������� ������ �� �����
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
        perror("�� ������� ������� ���� ��� ������");
        return NULL;
    }
    TreeNode* root = loadTreeFromFileHelper(file);
    fclose(file);
    return root;
}

// ���������� ������ ������
void printTreePreOrder(TreeNode* root, FILE* stream) {
    if (root == NULL) {
        fprintf(stream, "# ");
        return;
    }
    fprintf(stream, "%d ", root->data);
    printTreePreOrder(root->left, stream);
    printTreePreOrder(root->right, stream);
}

// ��������� ������ ������
void printTreeInOrder(TreeNode* root, FILE* stream) {
    if (root == NULL) {
        return;
    }
    printTreeInOrder(root->left, stream);
    fprintf(stream, "%d ", root->data);
    printTreeInOrder(root->right, stream);
}

// ����������� ������ ������
void printTreePostOrder(TreeNode* root, FILE* stream) {
    if (root == NULL) {
        return;
    }
    printTreePostOrder(root->left, stream);
    printTreePostOrder(root->right, stream);
    fprintf(stream, "%d ", root->data);
}

// ������������ ������ ������
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}