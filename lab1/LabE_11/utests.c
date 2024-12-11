# include "header.h"

TreeNode* createNode(char* data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* addNode(TreeNode* root, char* data) {
    if (root == NULL) {
        return createNode(data);
    }
    int comparison = strcmp(data, root->data);
    if (comparison < 0) {
        root->left = addNode(root->left, data);
    }
    else if (comparison > 0) {
        root->right = addNode(root->right, data);
    }
    else {
        printf("Такой элемент уже существует!\n");
    }
    return root;
}

TreeNode* loadTreeFromFile(FILE* file) {
    char buffer[100];
    if (fscanf(file, "%99[^\n]\n", buffer) != 1) {
        return NULL;
    }
    TreeNode* root = createNode(buffer);
    root->left = loadTreeFromFile(file);
    root->right = loadTreeFromFile(file);
    return root;
}



void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void test_createNode() {
    TreeNode* node = createNode("Test");
    assert(strcmp(node->data, "Test") == 0);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
}

void test_addNode() {
    TreeNode* tree = NULL;
    tree = addNode(tree, "Root");
    tree = addNode(tree, "Left");
    tree = addNode(tree, "Right");

    assert(strcmp(tree->data, "Root") == 0);
    assert(strcmp(tree->left->data, "Left") == 0);
    assert(strcmp(tree->right->data, "Right") == 0);

    freeTree(tree); 
}

void test_addDuplicateNode() {
    TreeNode* tree = NULL;
    tree = addNode(tree, "Root");
    tree = addNode(tree, "Left");
    tree = addNode(tree, "Root");

    assert(strcmp(tree->data, "Root") == 0);
    assert(tree->left != NULL); 
    assert(tree->right == NULL); 

    freeTree(tree); 
}

void test_loadTreeFromFile() {
    FILE* file = fopen("tree_test.dat", "w");
    fprintf(file, "Root\nLeft\nRight\n");
    fclose(file);

    file = fopen("tree_test.dat", "r");
    TreeNode* tree = loadTreeFromFile(file);
    fclose(file);

    assert(strcmp(tree->data, "Root") == 0);
    assert(strcmp(tree->left->data, "Left") == 0);
    assert(strcmp(tree->right->data, "Right") == 0);

    freeTree(tree); 
}

void test_loadEmptyTreeFromFile() {
    FILE* file = fopen("empty_tree_test.dat", "w");
    fclose(file); 

    file = fopen("empty_tree_test.dat", "r");
    TreeNode* tree = loadTreeFromFile(file);
    fclose(file);

    assert(tree == NULL);  

}

void test_freeTree() {
    TreeNode* tree = NULL;
    tree = addNode(tree, "Root");
    tree = addNode(tree, "Left");
    tree = addNode(tree, "Right");

    freeTree(tree);
}

void test_loadingFromFileWithExtraNewlines() {
    FILE* file = fopen("extra_newlines.dat", "w");
    fprintf(file, "Root\n\nLeft\n\n\nRight\n");
    fclose(file);

    file = fopen("extra_newlines.dat", "r");
    TreeNode* tree = loadTreeFromFile(file);
    fclose(file);

    assert(strcmp(tree->data, "Root") == 0);
    assert(tree->left != NULL);
    assert(strcmp(tree->left->data, "Left") == 0);
    assert(tree->right != NULL);
    assert(strcmp(tree->right->data, "Right") == 0);

    freeTree(tree); 
}

void test_nullFileLoading() {
    FILE* file = NULL; 
    TreeNode* tree = loadTreeFromFile(file);
    assert(tree == NULL);  
}

void test_loadTreeFromFileWithIncorrectFormat() {
    FILE* file = fopen("incorrect_format.dat", "w");
    fprintf(file, "Root\nLeft\n\nRight\n");  
    fclose(file);

    file = fopen("incorrect_format.dat", "r");
    TreeNode* tree = loadTreeFromFile(file);
    fclose(file);

    assert(tree != NULL);  
    assert(strcmp(tree->data, "Root") == 0);
    assert(tree->left != NULL); 
    assert(tree->right != NULL);  
    assert(tree->left->right == NULL);  

    freeTree(tree); 
}

void test_createNodeWithEmptyString() {
    TreeNode* node = createNode("");
    assert(strcmp(node->data, "") == 0);  
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node); 
}