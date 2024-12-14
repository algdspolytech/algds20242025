#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define BUFFER_SIZE 1000

typedef struct Tree {
    char* data;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* createLeaf(const char* word) {
    Tree* new_node = (Tree*)malloc(sizeof(Tree));
    if (!new_node) {
        perror("Memory allocation error for the node");
        exit(EXIT_FAILURE);
    }

    new_node->data = _strdup(word);
    if (!new_node->data) {
        free(new_node);
        perror("Line copying error");
        exit(EXIT_FAILURE);
    }
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Tree* createTree(Tree* root, const char* word) {
    if (root == NULL) {
        return createLeaf(word);
    }
    if (strcmp(word, root->data) < 0 || (strcmp(word, root->data) == 0 && strlen(word) < strlen(root->data))) {
        root->left = createTree(root->left, word);
    }
    else {
        root->right = createTree(root->right, word);
    }
    return root;
}

int Width(Tree* node) {
    if (node == NULL) {
        return 0;
    }
    int leftWidth = Width(node->left);
    int rightWidth = Width(node->right);
    return leftWidth + rightWidth + strlen(node->data);
}

void printTree(Tree* node, FILE* output) {
    if (node == NULL) {
        return;
    }
    printTree(node->left, output);
    fprintf(output, "%s%d\n", node->data, Width(node));
    printTree(node->right, output);
}

void freeTree(Tree* node) {
    if (node == NULL) {
        return;
    }
    free(node->data);
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (!inputFile) {
        perror("Error opening the input file");
        return EXIT_FAILURE;
    }
    if (!outputFile) {
        perror("Error opening the output file");
        return EXIT_FAILURE;
    }

    Tree* root = NULL;
    char bufferList[BUFFER_SIZE];

    while (fgets(bufferList, sizeof(bufferList), inputFile)) {
        root = createTree(root, bufferList);
    }
    printTree(root, outputFile);
    fclose(inputFile);
    fclose(outputFile);
    freeTree(root);
    //Unit Tests
    test_createLeaf(); // Проверка создания листа
    test_createTree_empty(); // Проверка добавления в пустое дерево
    test_createTree_noempty_right(); // Проверка добавления в не пустое дерево (вправо)
    test_createTree_noempty_left(); // Проверка добавления в не пустое дерево (влево)
    test_Width_oneElement(); // Проверка вычисления ширины поддерева с одним элементом
    test_Width_nononeElement(); // Проверка вычисления ширины поддерева с более чем одним элементом
    test_Width_nononeElement_leftList(); // Проверка вычисления ширины поддерева у вырожденного в список по возрастанию
    test_Width_nononeElement_rightList(); // Проверка вычисления ширины поддерева у вырожденного в список по убыванию
    test_Width_nononeElement_FullTree(); // Проверка вычисления ширины поддерева у полного дерева
    test_Width_nononeElement_RandomTree(); // Проверка вычисления ширины поддерева

}
//Unit Tests
int test_createLeaf() {
    Tree* root = createLeaf("A");
    assert(strcmp(root->data, "A")==0 && root->left == NULL && root->right == NULL);
}
int test_createTree_empty() {
    Tree* root = NULL;
    root=createTree(root, "A");
    assert( strcmp(root->data, "A") == 0 && root->left == NULL && root->right == NULL );
}
int test_createTree_noempty_right() {
    Tree* root = NULL;
    root=createTree(root, "A");
    root=createTree(root, "AA");
    assert(strcmp(root->right->data, "AA") == 0 && root->right->left == NULL && root->right->right == NULL);
}
int test_createTree_noempty_left() {
    Tree* root = NULL;
    root = createTree(root, "AA");
    root = createTree(root, "A");
    assert(strcmp(root->left->data, "A") == 0 && root->left->left == NULL && root->left->right == NULL);
}
int test_Width_oneElement() {
    Tree* root = NULL;
    root = createTree(root, "A");
    int w = Width(root);
    assert(w==1);
}
int test_Width_nononeElement() {
    Tree* root = NULL;
    root = createTree(root, "A");
    root = createTree(root, "AA");
    int w = Width(root);
    assert(w == 3);
}
int test_Width_nononeElement_leftList() {
    Tree* root = NULL;
    root = createTree(root, "AAA");
    root = createTree(root, "AA");
    root = createTree(root, "A");
    int w = Width(root);
    assert(w == 6);
}
int test_Width_nononeElement_rightList() {
    Tree* root = NULL;
    root = createTree(root, "A");
    root = createTree(root, "AA");
    root = createTree(root, "AAA");
    int w = Width(root);
    assert(w == 6);
}
int test_Width_nononeElement_FullTree() {
    Tree* root = NULL;
    root = createTree(root, "AA");
    root = createTree(root, "AAA");
    root = createTree(root, "A");
    int w = Width(root);
    assert(w == 6);
}
int test_Width_nononeElement_RandomTree() {
    Tree* root = NULL;
    root = createTree(root, "AA");
    root = createTree(root, "AAA");
    root = createTree(root, "A");
    root = createTree(root, "AAAA");
    int w = Width(root);
    assert(w == 10);
}
