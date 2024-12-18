#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }

    return root;
}

void printTree(Node* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}

void saveToFile(Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d\n", root->data);
        saveToFile(root->left, file);
        saveToFile(root->right, file);
    }
}

Node* loadFromFile(FILE* file) {
    int data;
    if (fscanf(file, "%d", &data) != 1) {
        return NULL; 
    }

    Node* root = createNode(data);
    root->left = loadFromFile(file);
    root->right = loadFromFile(file);

    return root;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

Node* interactiveCreateTree() {
    Node* root = NULL;
    int value;
    char choice;

    do {
        printf("Enter a value to add to the tree: ");
        scanf("%d", &value);
        root = insert(root, value);

        printf("Do you want to add another element? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return root;
}

void Test_AddToEmptyTree_no1() {
    Node* root = insert(NULL, 10);
    printTree(root); 
    printf("\n");
    freeTree(root);
}

void Test_AddMultipleElements_no2() {
    Node* root = NULL;
    int elements[] = { 20, 10, 30 };

    for (int i = 0; i < 3; i++) {
        root = insert(root, elements[i]);
    }

    printTree(root); 
    printf("\n");
    freeTree(root);
}

void Test_SaveAndLoad_no3() {
    Node* root = insert(NULL, 5);
    root = insert(root, 3);
    root = insert(root, 7);

    FILE* file = fopen("tree.txt", "w");
    saveToFile(root, file);
    fclose(file);

    freeTree(root);

    file = fopen("tree.txt", "r");
    Node* loadedRoot = loadFromFile(file);
    fclose(file);

    printTree(loadedRoot); 
    printf("\n");

    freeTree(loadedRoot);
}

void Test_PrintEmptyTree_no4() {
    Node* root = NULL;
    printTree(root); 
    printf("\n");
}

void Test_AddDuplicate_no5() {
    Node* root = insert(NULL, 10);


    root = insert(root, 10); 
    printTree(root); 
    printf("\n");

    freeTree(root);
}

void Test_BalancedInsertions_no6() {
    Node* root = NULL;

    int elements[] = { 30, 20, 40, 10, 25, 35, 50 };

    for (int i = 0; i < 7; i++) {
        root = insert(root, elements[i]);
    }

    printTree(root);
    printf("\n");

    freeTree(root);
}

void Test_LoadInvalidFile_no7() {

    FILE* file = fopen("invalid.txt", "r");

    if (file == NULL) {
        printf("The file was not found!\n");
        return;
    }

    Node* loadedRoot = loadFromFile(file);

    if (loadedRoot == NULL) {
        printf("The tree is empty or the file is invalid.\n");
    }
    else {
        printTree(loadedRoot);
        freeTree(loadedRoot);
    }

    fclose(file);
}

void Test_InsertNegativeNumbers_no8() {
    Node* root = NULL;

    int elements[] = { -10, -20, -5 };

    for (int i = 0; i < 3; i++) {
        root = insert(root, elements[i]);
    }

    printTree(root);
    printf("\n");

    freeTree(root);
}

void Test_InteractiveCreation_no9() {
    Node* root = interactiveCreateTree();
    printTree(root); 
    printf("\n");
    freeTree(root);
}

void Test_DeepInsertion_no10() {
    Node* root = NULL;

    for (int i = 1; i <= 100; i++) {
        root = insert(root, i);
    }

    printTree(root); 
    printf("\n");

    freeTree(root);
}

void Test_SingleElementNo11() {
    Node* root = insert(NULL, 42);

    printTree(root);
    printf("\n");

    freeTree(root);
}

void Test_MixedInsertionsNo12() {
    Node* root = NULL;

    int elements[] = { 50, 30, 70, 20, 40, 60, 80 };

    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
        root = insert(root, elements[i]);
    }

    printTree(root); 
    printf("\n");

    freeTree(root);
}

void Test_SaveEmptyTreeNo13() {

    Node* root = NULL;

    FILE* file = fopen("empty_tree.txt", "w");
    saveToFile(root, file);
    fclose(file);

    file = fopen("empty_tree.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), file); 
    if (strlen(buffer) == 0) {
        printf("Файл пустой как и дерево.\n");
    }

    fclose(file);
}

int main() {
    Test_AddToEmptyTree_no1();
    Test_AddMultipleElements_no2();
    Test_SaveAndLoad_no3();
    Test_PrintEmptyTree_no4();
    Test_AddDuplicate_no5();
    Test_BalancedInsertions_no6();
    Test_LoadInvalidFile_no7();
    Test_InsertNegativeNumbers_no8();
    Test_InteractiveCreation_no9();
    Test_DeepInsertion_no10();
    Test_SingleElementNo11();
    Test_MixedInsertionsNo12();
    Test_SaveEmptyTreeNo13();

    return 0;
}
