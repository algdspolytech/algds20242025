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

// Тест 1: Проверка вставки элементов и правильности порядка в дереве
void testInsertionAndOrder() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    assert(find_order(root, 20) == 4);  // 20 — четвертый элемент
    assert(find_order(root, 10) == 2);  // 10 — второй элемент
}

// Тест 2: Проверка нахождения элемента с порядком на 2 меньше для 30 (ожидаем 10)
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

// Тест 3: Проверка на возврат NULL, когда нет элемента с порядком на K меньше для минимального элемента
void testElementMinusKForMin() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 5, 3);  // Для 5 не существует элемента на 3 позиции раньше
    assert(result == NULL);
}

// Тест 4: Проверка работы для дерева с одним элементом
void testSingleElementTree() {
    node_lr* singleNodeTree = NULL;
    singleNodeTree = insert(singleNodeTree, 100);
    assert(find_order(singleNodeTree, 100) == 1);
    assert(find_order(singleNodeTree, 100, 1) == NULL);
}

// Тест 5: Проверка дерева с одинаковыми значениями (должны быть обработаны корректно)
void testTreeWithDuplicates() {
    node_lr* treeWithDuplicates = NULL;
    treeWithDuplicates = insert(treeWithDuplicates, 10);
    treeWithDuplicates = insert(treeWithDuplicates, 10);
    treeWithDuplicates = insert(treeWithDuplicates, 10);
    assert(find_order(treeWithDuplicates, 10) == 3);  // Должно вернуть 3, т.к. три одинаковых элемента
}

// Тест 6: Проверка случая, когда нужно найти элемент с порядком на 1 меньше для 15 (ожидаем 10)
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

// Тест 7: Проверка случая, когда порядок элемента не существует
void testElementMinusKForNonExistent() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 35, 6);  // 35 — последний элемент, нет элементов с порядком на 6 меньше
    assert(result == NULL);
}

// Тест 8: Проверка работы с отрицательными и положительными числами
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

// Тест 9: Проверка работы с очень большим значением k (на выходе NULL)
void testElementMinusKForLargeK() {
    node_lr* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    node_lr* result = find_element_minus_K(root, 20, 1000);  // Такой K гораздо больше размера дерева, должно вернуть NULL
    assert(result == NULL);
}

// Тест 10: Проверка дерева, состоящего из одного элемента, и поиска элемента, который на 1 меньше
void testSingleElementMinusK() {
    node_lr* singleNodeTree2 = NULL;
    singleNodeTree2 = insert(singleNodeTree2, 50);
    node_lr* result = find_element_minus_K(singleNodeTree2, 50, 1);
    assert(result == NULL);  // Для единственного элемента не может быть элемента на 1 меньше
}

int main() {
    // Вызов всех тестов
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

    printf("Все тесты пройдены успешно!\n");
    return 0;