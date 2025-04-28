#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

typedef struct AVLTree {
    Node* root;
} AVLTree;

typedef struct BSTree {
    Node* root;
} BSTree;

// Функции для AVL-дерева
int height(Node* N) {
    return N ? N->height : 0;
}

int m_a_x(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // новый узел добавляется как лист
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = m_a_x(height(y->left), height(y->right)) + 1;
    x->height = m_a_x(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = m_a_x(height(x->left), height(x->right)) + 1;
    y->height = m_a_x(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* N) {
    return N ? height(N->left) - height(N->right) : 0;
}

Node* insertAVL(Node* node, int key) {
    if (!node) return newNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else // Дубликаты не допускаются
        return node;

    node->height = 1 + m_a_x(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Левый левый случай
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Правый правый случай
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Левый правый случай
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Правый левый случай
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNodeAVL(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNodeAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteNodeAVL(root->right, key);
    else {
        if ((!root->left) || (!root->right)) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                free(root);
                return NULL;
            }
            else {
                *root = *temp; // Копируем содержимое узла
                free(temp);
            }
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNodeAVL(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + m_a_x(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Левый левый случай
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Левый правый случай
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Правый правый случай
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Правый левый случай
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

// Функции для бинарного дерева поиска
Node* insertBST(Node* node, int key) {
    if (!node) return newNode(key);

    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);

    return node;
}

Node* deleteNodeBST(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNodeBST(root->left, key);
    else if (key > root->key)
        root->right = deleteNodeBST(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                free(root);
                return NULL;
            }
            else {
                *root = *temp; // Копируем содержимое узла
                free(temp);
            }
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNodeBST(root->right, temp->key);
        }
    }

    return root;
}

// Время выполнения операций
double measureTime(void (*func)(Node**, int), Node** tree, int key) {
    clock_t start, end;
    start = clock();
    func(tree, key);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    return 0;
}


//Тесты
void AddToEmptyTree_no1() {
    AVLTree tree;
    tree.root = NULL;

    tree.root = insertAVL(tree.root, 10);

    assert(tree.root->key == 10);
}

void AddMultipleElements_no2() {
    AVLTree tree;
    tree.root = NULL;

    tree.root = insertAVL(tree.root, 30);
    tree.root = insertAVL(tree.root, 20);
    tree.root = insertAVL(tree.root, 10);

    assert(tree.root->key == 20); // Root should be balanced to 20
}

void DeleteLeafNode_no3() {
    AVLTree tree;
    tree.root = NULL;

    tree.root = insertAVL(tree.root, 10);
    tree.root = insertAVL(tree.root, 20);

    tree.root = deleteNodeAVL(tree.root, 20); // Deleting leaf

    assert(tree.root->key == 10); // Root should still be 10
}

void DeleteRootNode_no4() {
    AVLTree tree;
    tree.root = NULL;

    tree.root = insertAVL(tree.root, 10);

    tree.root = deleteNodeAVL(tree.root, 10); // Deleting root

    assert(tree.root == 0); // Tree should be empty now
}

void SearchExistingElement_no5() {
    AVLTree tree;
    tree.root = NULL;

    tree.root = insertAVL(tree.root, 10);

    assert(search(tree.root, 10) == 0); // Should find the element
}

void SearchNonExistingElement_no6() {
    AVLTree tree;
    tree.root = NULL;

    tree.root = insertAVL(tree.root, 10);

    assert(search(tree.root, 20) == 0); // Should not find the element
}

void AddToEmptyTree_no7() {
    BSTree bst;
    bst.root = NULL;

    bst.root = insertBST(bst.root, 10);
    
    assert(bst.root->key == 10);
}

void AddMultipleElements_no8() {
    BSTree bst;
    bst.root = NULL;

    bst.root = insertBST(bst.root, 30);
    bst.root = insertBST(bst.root, 20);

    assert(bst.root->left->key == 20); // Left child should be 20
}

void DeleteLeafNode_no9() {
    BSTree bst;
    bst.root = NULL;

    bst.root = insertBST(bst.root, 10);

    bst.root = deleteNodeBST(bst.root, 10); // Deleting leaf

    assert(bst.root == 0); // Tree should be empty now
}

void SearchExistingElement_no10() {
    BSTree bst;
    bst.root = NULL;

    bst.root = insertBST(bst.root, 10);

    assert(search(bst.root, 10) == 0); // Should find the element
}

// Сравнение времени выполнения операций
void CompareInsertTime_no11() {
    AVLTree avl_tree;
    avl_tree.root = NULL;

    BSTree bst_tree;
    bst_tree.root = NULL;

    const int numElements = 1000;

    double avl_time_total = 0.0;
    double bst_time_total = 0.0;

    for (int i = 0; i < numElements; ++i) {
        avl_time_total += measureTime((void (*)(Node**, int))insertAVL, &avl_tree.root, i);
        bst_time_total += measureTime((void (*)(Node**, int))insertBST, &bst_tree.root, i);
    }

    printf("Average time for AVL Insert: %f seconds\n", avl_time_total / numElements);
    printf("Average time for BST Insert: %f seconds\n", bst_time_total / numElements);

    assert(avl_time_total / numElements == bst_time_total / numElements); // AVL должен быть быстрее или равен
}

void Run_tests() {
    AddToEmptyTree_no1();
    AddMultipleElements_no2();
    DeleteLeafNode_no3();
    DeleteRootNode_no4();
    SearchExistingElement_no5();
    SearchNonExistingElement_no6();
    AddToEmptyTree_no7();
    AddMultipleElements_no8();
    DeleteLeafNode_no9();
    SearchExistingElement_no10();
    printf("Success!");
}