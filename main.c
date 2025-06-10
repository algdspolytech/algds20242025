#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TreeNode {
    int key;
    int value;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

int height(TreeNode* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

TreeNode* createNode(int key, int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->value = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int getBalanceFactor(TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void updateMetadata(TreeNode* node) {
    if (node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateMetadata(y);
    updateMetadata(x);
    return x;
}

TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateMetadata(x);
    updateMetadata(y);
    return y;
}

TreeNode* insert(TreeNode* node, int key, int value) {
    if (node == NULL) {
        return createNode(key, value);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }
    else {
        node->value = value;
    }
    updateMetadata(node);
    int balance = getBalanceFactor(node);
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

TreeNode* search(TreeNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

TreeNode* findKthElement(TreeNode* root, int k) {
    if (root == NULL) {
        return NULL;
    }
    int leftSize = height(root->left);
    if (k == leftSize + 1) {
        return root;
    }
    else if (k <= leftSize) {
        return findKthElement(root->left, k);
    }
    else {
        return findKthElement(root->right, k - leftSize - 1);
    }
}

TreeNode* insertAtPosition(TreeNode* root, int pos, int key, int value) {
    if (pos < 1 || pos > height(root) + 1) {
        printf("Invalid position!\n");
        return root;
    }
    if (pos == 1) {
        TreeNode* newNode = createNode(key, value);
        newNode->right = root;
        return newNode;
    }
    root->left = insertAtPosition(root->left, pos - 1, key, value);
    return root;
}

TreeNode* minValueNode(TreeNode* Treenode) {
    TreeNode* current = Treenode;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = minValueNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
    }
    if (root == NULL) {
        return root;
    }
    updateMetadata(root);
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

TreeNode* concatenateLists(TreeNode* list1, TreeNode* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    TreeNode* lastNode = list1;
    while (lastNode->right != NULL) {
        lastNode = lastNode->right;
    }
    lastNode->right = list2;
    return list1;
}

void printList(TreeNode* root) {
    while (root != NULL) {
        printf("%d ", root->key);
        root = root->right;
    }
    printf("\n");
}

//UNIT TEST
// Тест 1: Создание нового узла
void testCreateNewNode() {
    TreeNode* node = createNode(5, 50);

    assert(node != NULL);
    assert(node->key == 5);
    assert(node->value == 50);
    assert(node->height == 1);
    assert(node->left == NULL);
    assert(node->right == NULL);

    free(node);
}

// Тест 2: Поиск существующего ключа
void testSearchExistingKey() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->key = 10;
    root->value = 100;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;

    TreeNode* result = search(root, 10);

    assert(result != NULL);
    assert(result->key == 10);
    assert(result->value == 100);

    free(root);
}

// Тест 3: Поиск несуществующего ключа
void testSearchNonexistingKey() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->key = 10;
    root->value = 100;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;

    TreeNode* result = search(root, 20);

    assert(result == NULL);

    free(root);
}

// Тест 4: Вставка в пустое дерево
void testInsertIntoEmptyTree() {
    TreeNode* root = NULL;
    root = insert(root, 10, 100);

    assert(root != NULL);
    assert(root->key == 10);
    assert(root->value == 100);
    assert(root->height == 1);
    assert(root->left == NULL);
    assert(root->right == NULL);

    free(root);
}

// Тест 5: Вставка в существующее дерево
void testInsertIntoExistingTree() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->key = 10;
    root->value = 100;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;
    root = insert(root, 20, 200);

    assert(root != NULL);
    assert(root->key == 10);
    assert(root->left == NULL);
    assert(root->right != NULL);
    assert(root->right->key == 20);
    assert(root->right->value == 200);

    free(root);
}

// Тест 6: Поиск k-го элемента
void testFindKthElement() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->key = 10;
    root->value = 100;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;

    TreeNode* leftChild = (TreeNode*)malloc(sizeof(TreeNode));
    leftChild->key = 5;
    leftChild->value = 50;
    leftChild->height = 1;
    leftChild->left = NULL;
    leftChild->right = NULL;
    root->left = leftChild;

    root->height = leftChild->height + 1;

    TreeNode* kthElement = findKthElement(root, 1);

    assert(kthElement != NULL);
    assert(kthElement->key == 5);
    assert(kthElement->value == 50);

    free(root);
}

// Тест 7: Вставка элемента в позицию
void testInsertAtPosition() {
    TreeNode* root = NULL;
    root = insertAtPosition(root, 1, 10, 100);

    assert(root != NULL);
    assert(root->key == 10);
    assert(root->value == 100);

    free(root);
}

// Тест 8: Удаление листа
void testDeleteLeafNode() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->key = 10;
    root->value = 100;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;

    root = deleteNode(root, 10);

    assert(root == NULL);

    free(root);
}

// Тест 9: Сцепление двух списков
void testConcatenateLists() {

    TreeNode* list1 = (TreeNode*)malloc(sizeof(TreeNode));
    list1->key = 10;
    list1->value = 100;
    list1->height = 1;
    list1->left = NULL;
    list1->right = (TreeNode*)malloc(sizeof(TreeNode));
    list1->right->key = 20;
    list1->right->value = 200;
    list1->right->height = 1;
    list1->right->left = NULL;
    list1->right->right = NULL;

    TreeNode* list2 = (TreeNode*)malloc(sizeof(TreeNode));
    list2->key = 30;
    list2->value = 300;
    list2->height = 1;
    list2->left = NULL;
    list2->right = (TreeNode*)malloc(sizeof(TreeNode));
    list2->right->key = 40;
    list2->right->value = 400;
    list2->right->height = 1;
    list2->right->left = NULL;
    list2->right->right = NULL;

    TreeNode* mergedList = concatenateLists(list1, list2);

    assert(mergedList != NULL);
    assert(mergedList->key == 10);
    assert(mergedList->right->key == 20);
    assert(mergedList->right->right->key == 30);
    assert(mergedList->right->right->right->key == 40);

    free(mergedList->right->right->right);
    free(mergedList->right->right);
    free(mergedList->right);
    free(mergedList);
}

// Тест 10: Проверка балансировки дерева
void testAVLBalance() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->key = 10;
    root->value = 100;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;

    assert(getBalanceFactor(root) <= 1 && getBalanceFactor(root) >= -1);

    free(root);
}

int main() {
    testCreateNewNode();
    testSearchExistingKey();
    testSearchNonexistingKey();
    testInsertIntoEmptyTree();
    testInsertIntoExistingTree();
    testFindKthElement();
    testInsertAtPosition();
    testDeleteLeafNode();
    testConcatenateLists();
    testAVLBalance();

    return 0;
}
