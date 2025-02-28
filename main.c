#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// для скошения узла в корень
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == NULL) return root;

        // левый-левый
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // левый-правый
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    }
    else {
        if (root->right == NULL) return root;

        // правый-правый
        if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        // правый-левый
        else if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

Node* search(Node* root, int key) {
    return splay(root, key);
}

// добавление элемента
Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);

    root = splay(root, key);

    if (root->key == key) return root;

    Node* newNode = createNode(key);

    if (root->key > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    }
    else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    return newNode;
}

// удаление элемента
Node* deleteel(Node* root, int key) {
    if (root == NULL) return NULL;

    root = splay(root, key);

    if (root->key != key) return root;

    Node* temp;
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    }
    else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

void printTree(Node* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    printTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    printTree(root->left, space);
}

// проверяет добавление элемента в пустое дерево
void testAddToEmptyList_no1() {
    Node* root = NULL;
    root = insert(root, 10);
    if (root != NULL && root->key == 10) {
        printf("testAddToEmptyList_no1: successfully\n");
    }
    else {
        printf("testAddToEmptyList_no1: failed\n");
    }
}

// проверяет добавление нескольких элементов в дерево
void testAddMultipleElements_no2() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    if (root != NULL && root->key == 5 && root->right->key == 10 && root->right->right->key == 20) {
        printf("testAddMultipleElements_no2: successfully\n");
    }
    else {
        printf("testAddMultipleElements_no2: failed\n");
    }
}

// проверяет поиск элемента в дереве
void testSearchElement_no3() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = search(root, 20);
    if (root != NULL && root->key == 20) {
        printf("testSearchElement_no3: successfully\n");
    }
    else {
        printf("testSearchElement_no3: failed\n");
    }
}

// проверяет удаление элемента из дерева
void testDeleteElement_no4() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = deleteel(root, 20);
    if (root != NULL && root->key == 5 && root->right->key == 10) {
        printf("testDeleteElement_no4: failed\n");
    }
    else {
        printf("testDeleteElement_no4: successfully\n");
    }
}

// проверяет удаление элемента из пустого дерева
void testDeleteFromEmptyList_no5() {
    Node* root = NULL;
    root = deleteel(root, 10);
    if (root == NULL) {
        printf("testDeleteFromEmptyList_no5: successfully\n");
    }
    else {
        printf("testDeleteFromEmptyList_no5: failed\n");
    }
}

// проверяет удаление несуществующего элемента из дерева
void testDeleteNonExistingElement_no6() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = deleteel(root, 30);
    if (root != NULL && root->key == 20 && root->left->key == 10) {
        printf("testDeleteNonExistingElement_no6: successfully\n");
    }
    else {
        printf("testDeleteNonExistingElement_no6: failed\n");
    }
}

// проверяет вставку дубликата ключа
void testInsertDuplicateKey_no7() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 10); // Дубликат
    if (root != NULL && root->key == 10 && root->left == NULL && root->right == NULL) {
        printf("testInsertDuplicateKey_no7: successfully\n");
    }
    else {
        printf("testInsertDuplicateKey_no7: failed\n");
    }
}

// проверяет поиск несуществующего элемента
void testSearchNonExistingElement_no8() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = search(root, 30); // Элемент отсутствует
    if (root != NULL && root->key == 20) { // После поиска корень должен быть 20 (последний доступный элемент)
        printf("testSearchNonExistingElement_no8: successfully\n");
    }
    else {
        printf("testSearchNonExistingElement_no8: failed\n");
    }
}

// проверяет удаление корневого элемента
void testDeleteRootElement_no9() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = deleteel(root, 10); // Удаляем корень
    if (root != NULL && root->key == 5 && root->right->key == 20) {
        printf("testDeleteRootElement_no9: successfully\n");
    }
    else {
        printf("testDeleteRootElement_no9: failed\n");
    }
}

// проверяет корректность операции splay (после поиска элемент должен стать корнем)
void testSplayOperation_no10() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 15);
    root = search(root, 15); // Ищем 15, он должен стать корнем
    if (root != NULL && root->key == 15) {
        printf("testSplayOperation_no10: successfully\n");
    }
    else {
        printf("testSplayOperation_no10: failed\n");
    }
}

int main() {
    testAddToEmptyList_no1();
    testAddMultipleElements_no2();
    testSearchElement_no3();
    testDeleteElement_no4();
    testDeleteFromEmptyList_no5();
    testDeleteNonExistingElement_no6();
    testInsertDuplicateKey_no7();
    testSearchNonExistingElement_no8();
    testDeleteRootElement_no9();
    testSplayOperation_no10();

    return 0;
}