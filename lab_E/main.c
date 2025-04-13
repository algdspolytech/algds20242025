#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Функция создания нового узла
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция вставки узла в дерево
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Функция удаления поддерева с заданным ключом
void deleteSubtree(Node** root, int key) {
    if (*root == NULL) {
        return;
    }

    // Если текущий узел содержит искомый ключ
    if ((*root)->key == key) {
        // Удаляем все поддерево
        freeSubtree(*root);
        *root = NULL;
        return;
    }

    // Рекурсивно ищем ключ в левом и правом поддеревьях
    deleteSubtree(&((*root)->left), key);
    deleteSubtree(&((*root)->right), key);
}

// Вспомогательная функция для освобождения памяти поддерева
void freeSubtree(Node* node) {
    if (node == NULL) {
        return;
    }

    freeSubtree(node->left);
    freeSubtree(node->right);
    free(node);
}

// Функция для печати дерева (in-order)
void printTree(Node* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("%d ", root->key);
        printTree(root->right);
    }
}

// Функция для проверки существования узла с заданным ключом
int nodeExists(Node* root, int key) {
    if (root == NULL) {
        return 0;
    }

    if (root->key == key) {
        return 1;
    }

    return nodeExists(root->left, key) || nodeExists(root->right, key);
}

// Макрос для проверки условия в тестах
#define CHECK(condition) \
    do { \
        if (!(condition)) { \
            printf("FAILED (Line %d)\n", __LINE__); \
            return; \
        } \
    } while (0)

// Тест 1: Удаление корня дерева
void testDeleteRoot() {
    printf("Test 1: Delete root node - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);

    deleteSubtree(&root, 5);

    CHECK(root == NULL);
    printf("PASSED\n");
}

// Тест 2: Удаление листового узла
void testDeleteLeaf() {
    printf("Test 2: Delete leaf node - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);

    deleteSubtree(&root, 2);

    CHECK(!nodeExists(root, 2));
    CHECK(nodeExists(root, 5));
    CHECK(nodeExists(root, 3));
    CHECK(nodeExists(root, 7));
    printf("PASSED\n");
}

// Тест 3: Удаление узла с одним потомком
void testDeleteNodeWithOneChild() {
    printf("Test 3: Delete node with one child - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);
    insert(root, 4);

    deleteSubtree(&root, 3);

    CHECK(!nodeExists(root, 3));
    CHECK(!nodeExists(root, 2));
    CHECK(!nodeExists(root, 4));
    CHECK(nodeExists(root, 5));
    CHECK(nodeExists(root, 7));
    printf("PASSED\n");
}

// Тест 4: Удаление узла с двумя потомками
void testDeleteNodeWithTwoChildren() {
    printf("Test 4: Delete node with two children - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);

    deleteSubtree(&root, 7);

    CHECK(!nodeExists(root, 7));
    CHECK(!nodeExists(root, 6));
    CHECK(!nodeExists(root, 8));
    CHECK(nodeExists(root, 5));
    CHECK(nodeExists(root, 3));
    CHECK(nodeExists(root, 2));
    CHECK(nodeExists(root, 4));
    printf("PASSED\n");
}

// Тест 5: Попытка удаления несуществующего узла
void testDeleteNonExistentNode() {
    printf("Test 5: Try to delete non-existent node - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);

    int initialNodes = nodeExists(root, 5) + nodeExists(root, 3) + nodeExists(root, 7);

    deleteSubtree(&root, 10);

    CHECK(nodeExists(root, 5));
    CHECK(nodeExists(root, 3));
    CHECK(nodeExists(root, 7));
    CHECK(initialNodes == 3);
    printf("PASSED\n");
}

// Тест 6: Удаление из пустого дерева
void testDeleteFromEmptyTree() {
    printf("Test 6: Delete from empty tree - ");
    Node* root = NULL;

    deleteSubtree(&root, 5);

    CHECK(root == NULL);
    printf("PASSED\n");
}

// Тест 7: Удаление узла из дерева с одним элементом
void testDeleteFromSingleNodeTree() {
    printf("Test 7: Delete from single-node tree - ");
    Node* root = NULL;
    root = insert(root, 5);

    deleteSubtree(&root, 5);

    CHECK(root == NULL);
    printf("PASSED\n");
}

// Тест 8: Удаление нескольких узлов по очереди
void testDeleteMultipleNodes() {
    printf("Test 8: Delete multiple nodes sequentially - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);

    deleteSubtree(&root, 3);
    CHECK(!nodeExists(root, 3));
    CHECK(!nodeExists(root, 2));
    CHECK(!nodeExists(root, 4));

    deleteSubtree(&root, 7);
    CHECK(!nodeExists(root, 7));
    CHECK(!nodeExists(root, 6));
    CHECK(!nodeExists(root, 8));

    deleteSubtree(&root, 5);
    CHECK(root == NULL);
    printf("PASSED\n");
}

// Тест 9: Удаление всех узлов дерева
void testDeleteAllNodes() {
    printf("Test 9: Delete all nodes of the tree - ");
    Node* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);

    deleteSubtree(&root, 5);
    deleteSubtree(&root, 3);
    deleteSubtree(&root, 7);
    deleteSubtree(&root, 2);
    deleteSubtree(&root, 4);
    deleteSubtree(&root, 6);
    deleteSubtree(&root, 8);

    CHECK(root == NULL);
    printf("PASSED\n");
}

// Тест 10: Удаление узла из большого дерева
void testDeleteFromLargeTree() {
    printf("Test 10: Delete from large tree - ");
    Node* root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 17);
    insert(root, 1);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);
    insert(root, 11);
    insert(root, 13);
    insert(root, 16);
    insert(root, 18);

    deleteSubtree(&root, 15);

    CHECK(!nodeExists(root, 15));
    CHECK(!nodeExists(root, 12));
    CHECK(!nodeExists(root, 17));
    CHECK(!nodeExists(root, 11));
    CHECK(!nodeExists(root, 13));
    CHECK(!nodeExists(root, 16));
    CHECK(!nodeExists(root, 18));
    CHECK(nodeExists(root, 10));
    CHECK(nodeExists(root, 5));
    CHECK(nodeExists(root, 3));
    CHECK(nodeExists(root, 7));
    CHECK(nodeExists(root, 1));
    CHECK(nodeExists(root, 4));
    CHECK(nodeExists(root, 6));
    CHECK(nodeExists(root, 8));
    printf("PASSED\n");
}

int main() {
    testDeleteRoot();
    testDeleteLeaf();
    testDeleteNodeWithOneChild();
    testDeleteNodeWithTwoChildren();
    testDeleteNonExistentNode();
    testDeleteFromEmptyTree();
    testDeleteFromSingleNodeTree();
    testDeleteMultipleNodes();
    testDeleteAllNodes();
    testDeleteFromLargeTree();

    return 0;
}
