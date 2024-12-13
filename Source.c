#include <stdio.h>
#include <stdlib.h>

typedef struct node_lr {
    int key;
    int size;
    struct node_lr* left;
    struct node_lr* right;
} node_lr;


void upSize(node_lr* node) {
    if (node) {
        int leftS = (node->left) ? node->left->size : 0;
        int rightS = (node->right) ? node->right->size : 0;
        node->size = 1 + leftS + rightS;
    }
}

node_lr* createNode(int key) {
    node_lr* node = (node_lr*)malloc(sizeof(node_lr));
    node->key = key;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

node_lr* find_k_smallest(node_lr* root, int k) {
    if (root == NULL) return NULL;

    int leftS = (root->left) ? root->left->size : 0;

    if (k == leftS + 1) {
        return root;
    }
    else if (k <= leftS) {
        return find_k_smallest(root->left, k);
    }
    else {
        return find_k_smallest(root->right, k - leftS - 1);
    }
}

node_lr* insert(node_lr* root, int key) {
    if (root == NULL) return createNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    upSize(root);
    return root;
}


int find_order(node_lr* root, int key) {
    int order = 0;
    node_lr* current = root;

    while (current != NULL) {
        int leftSize = (current->left) ? current->left->size : 0;

        if (key == current->key) {
            order += leftSize + 1;
            return order;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            order += leftSize + 1;
            current = current->right;
        }
    }
    return -1;
}


node_lr* find_element_minus_K(node_lr* root, int key, int k) {
    int currentOrder = find_order(root, key);

    if (currentOrder == -1 || currentOrder <= k) {
        return NULL;
    }
    return find_k_smallest(root, currentOrder - k);
}


void inorderPrint(node_lr* root) {
    if (root != NULL) {
        inorderPrint(root->left);
        printf("%d (size: %d) ", root->key, root->size);
        inorderPrint(root->right);
    }
}

// ���� 1: �������� ������� ��������� � ������������ ������� � ������
void testInsertionAndOrder() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    assert(find_order(root, 20) == 4);  // 20 � ��������� �������
    assert(find_order(root, 10) == 2);  // 10 � ������ �������
}

// ���� 2: �������� ���������� �������� � �������� �� 2 ������ ��� 30 (������� 10)
void testElementMinusK() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 30, 2);
    assert(result != NULL && result->key == 10);
}

// ���� 3: �������� �� ������� NULL, ����� ��� �������� � �������� �� K ������ ��� ������������ ��������
void testElementMinusKForMin() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 5, 3);  // ��� 5 �� ���������� �������� �� 3 ������� ������
    assert(result == NULL);
}

// ���� 4: �������� ������ ��� ������ � ����� ���������
void testSingleElementTree() {
    node_lr* singleNodeTree = NULL;
    singleNodeTree = insert(singleNodeTree, 100);
    assert(find_order(singleNodeTree, 100) == 1);
    assert(find_order(singleNodeTree, 100, 1) == NULL);
}

// ���� 5: �������� ������ � ����������� ���������� (������ ���� ���������� ���������)
void testTreeWithDuplicates() {
    node_lr* treeWithDuplicates = NULL;
    treeWithDuplicates = insert(treeWithDuplicates, 10);
    treeWithDuplicates = insert(treeWithDuplicates, 10);
    treeWithDuplicates = insert(treeWithDuplicates, 10);
    assert(find_order(treeWithDuplicates, 10) == 3);  // ������ ������� 3, �.�. ��� ���������� ��������
}

// ���� 6: �������� ������, ����� ����� ����� ������� � �������� �� 1 ������ ��� 15 (������� 10)
void testElementMinusKForOneLess() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 15, 1);
    assert(result != NULL && result->key == 10);
}

// ���� 7: �������� ������, ����� ������� �������� �� ����������
void testElementMinusKForNonExistent() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 35, 6);  // 35 � ��������� �������, ��� ��������� � �������� �� 6 ������
    assert(result == NULL);
}

// ���� 8: �������� ������ � �������������� � �������������� �������
void testTreeWithNegativeAndPositive() {
    node_lr* treeWithNegative = NULL;
    treeWithNegative = insert(treeWithNegative, -10);
    treeWithNegative = insert(treeWithNegative, -5);
    treeWithNegative = insert(treeWithNegative, 0);
    treeWithNegative = insert(treeWithNegative, 5);
    treeWithNegative = insert(treeWithNegative, 10);
    assert(find_order(treeWithNegative, -10) == 1);
    assert(find_order(treeWithNegative, 5) == 4);
}

// ���� 9: �������� ������ � ����� ������� ��������� k (�� ������ NULL)
void testElementMinusKForLargeK() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 20, 1000);  // ����� K ������� ������ ������� ������, ������ ������� NULL
    assert(result == NULL);
}

// ���� 10: �������� ������, ���������� �� ������ ��������, � ������ ��������, ������� �� 1 ������
void testSingleElementMinusK() {
    node_lr* singleNodeTree2 = NULL;
    singleNodeTree2 = insert(singleNodeTree2, 50);
    node_lr* result = find_element_minus_K(singleNodeTree2, 50, 1);
    assert(result == NULL);  // ��� ������������� �������� �� ����� ���� �������� �� 1 ������
}

int main() {
    // ����� ���� ������
    testInsertionAndOrder();
    testElementMinusK();
    testElementMinusKForMin();
    testSingleElementTree();
    testTreeWithDuplicates();
    testElementMinusKForOneLess();
    testElementMinusKForNonExistent();
    testTreeWithNegativeAndPositive();
    testElementMinusKForLargeK();
    testSingleElementMinusK();

    printf("��� ����� �������� �������!\n");
    return 0;