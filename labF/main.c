#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int low;           // Начало интервала
    int high;          // Конец интервала
    int max_high;      // Максимальный конец интервала в поддереве
    struct Node* left; // Левый узел
    struct Node* right; // Правый узел
} Node;

// Создание нового узла
Node* createNode(int low, int high) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->low = low;
    node->high = high;
    node->max_high = high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Вставка интервала в дерево
Node* insert(Node* root, int low, int high) {
    if (root == NULL) {
        return createNode(low, high);
    }

    if (low < root->low) {
        root->left = insert(root->left, low, high);
    }
    else {
        root->right = insert(root->right, low, high);
    }

    if (root->max_high < high) {
        root->max_high = high;
    }

    return root;
}

// Нахождение минимального узла в правом поддереве
Node* findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Удаление интервала из дерева
Node* deleteNode(Node* root, int low) {
    if (root == NULL) {
        return NULL;
    }

    if (low < root->low) {
        root->left = deleteNode(root->left, low);
    }
    else if (low > root->low) {
        root->right = deleteNode(root->right, low);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL; 
        }
        else if (root->left == NULL || root->right == NULL) {
            Node* temp = (root->left) ? root->left : root->right;
            free(root);
            return temp;
        }
        else {
            Node* minNode = findMin(root->right);
            root->low = minNode->low;
            root->high = minNode->high;
            root->right = deleteNode(root->right, minNode->low);
        }
    }

    if (root->left) {
        root->max_high = root->left->max_high;
    }
    if (root->right) {
        root->max_high = root->max_high > root->right->max_high ? root->max_high : root->right->max_high;
    }
    return root;
}

// Нахождение пересекающихся интервалов
void findOverlappingIntervals(Node* root, int intervalLow, int intervalHigh, Node** result, int* count) {
    if (root == NULL) {
        return;
    }

    if (root->low <= intervalHigh && root->high >= intervalLow) {
        result[*count] = root;
        (*count)++;
    }

    if (root->left && root->left->max_high >= intervalLow) {
        findOverlappingIntervals(root->left, intervalLow, intervalHigh, result, count);
    }

    if (root->right && root->right->low <= intervalHigh) {
        findOverlappingIntervals(root->right, intervalLow, intervalHigh, result, count);
    }
}