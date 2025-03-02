#include "Header.h"
#include <stdio.h>
#include <stdlib.h>


// ������� ��� ��������� ������� ���������
int get_size(struct Node* node) {
    return node ? node->size : 0;
}

// ������� ��� ���������� ������� ���������
void update_size(struct Node* node) {
    if (node) {
        node->size = get_size(node->left) + get_size(node->right) + 1;
    }
}

// ������� ��� �������� ������ ����
struct Node* new_node(int x, int c) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));  // ��������� ������ ��� ������ ����
    if (!node) {  // ��������, �� ����� �� ��������� NULL
        printf("Error allocating memory for new node.\n");
        exit(1);  // ��������� ��������� � �������, ���� �� ������� �������� ������
    }
    node->x = x;
    node->c = c;
    node->priority = rand();  // ��������� ��������� ��� ����
    node->left = node->right = NULL;
    node->size = 1;
    return node;
}

// ������� ��� ���������� �������� ������
struct Node* rotate_right(struct Node* node) {
    if (!node || !node->left) return node;  // �������� �� NULL

    struct Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    update_size(node);
    update_size(new_root);
    return new_root;
}

// ������� ��� ���������� �������� �����
struct Node* rotate_left(struct Node* node) {
    if (!node || !node->right) return node;  // �������� �� NULL

    struct Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    update_size(node);
    update_size(new_root);
    return new_root;
}

// ������� ��� ������� ���� � ��������� ������
struct Node* insert(struct Node* root, int x, int c) {
    if (!root) {
        return new_node(x, c);
    }

    if (x < root->x) {
        root->left = insert(root->left, x, c);
        if (root->left && root->left->priority > root->priority)
            root = rotate_right(root);
    }
    else {
        root->right = insert(root->right, x, c);
        if (root->right && root->right->priority > root->priority)
            root = rotate_left(root);
    }
    update_size(root);
    return root;
}



// ������� ��� ������ ��������� �� ��������� [x, y)
int find_max(struct Node* root, int x, int y) {
    if (!root) return -1;  // ������ ���������

    
    // ���� ������� ���� ������� �� ������� ���������
    if (root->x >= y) 
        return find_max(root->left, x, y);  // ����� ���������
    if (root->x < x) 
        return find_max(root->right, x, y);  // ������ ���������

    // ������ � �������� ���������
    int left_max = find_max(root->left, x, y);
    int right_max = find_max(root->right, x, y);
    int result = root->c;

    // ���� ������ �������� � �����������, ��������� ���������
    if (left_max > result) result = left_max;
    if (right_max > result) result = right_max;

    return result;
}





//int main() {
//    struct Node* root = NULL;
//
//    // ������ ��� (x, c)
//    int arr[][2] = { {1, 5}, {3, 7}, {2, 6}, {4, 8} };
//    int n = 4;
//
//    // ��������� ��� ���� � ��������� ������
//    for (int i = 0; i < n; i++) {
//        root = insert(root, arr[i][0], arr[i][1]);
//    }
//
//    // ������ ������� ��� ��������� [2, 4)
//    printf("Max value in range [2, 4): %d\n", find_max(root, 2, 4));
//
//    return 0;
//}
