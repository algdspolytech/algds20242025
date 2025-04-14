#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла в двоичном дереве
typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Функция для создания нового узла
TreeNode* createNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для удаления всего поддерева
void deleteSubtree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    deleteSubtree(root->left);
    deleteSubtree(root->right);
    free(root);
}

// Функция для удаления поддерева из ключа
TreeNode* deleteSubtreeWithKey(TreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

   
    if (root->key == key) {
        deleteSubtree(root);
        return NULL; 

   
    root->left = deleteSubtreeWithKey(root->left, key);
    root->right = deleteSubtreeWithKey(root->right, key);

    return root;
}

void printTree(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("-> %d\n", root->key);
    printTree(root->left, level + 1);
}


int main() {
    
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Arbre initial :\n");
    printTree(root, 0);

   
    root = deleteSubtreeWithKey(root, 2);

    printf("\nArbre après suppression du sous-arbre avec la clé 2 :\n");
    printTree(root, 0);

   
    deleteSubtree(root);

    return 0;
}


// lab E test

#include <cstdio>
#include <stdlib.h>
#include <tree.c>
#include <gtest/gtest.h>

TEST(TreeTest, InitNode_n1) {
    TreeNode* node = initNode(10);
    EXPECT_EQ(node->data, 10);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

TEST(TreeTest, AddNodeToEmptyTree_n2) {
    TreeNode* root = nullptr;
    addNode(&root, 1);
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    free(root);
}

TEST(TreeTest, AddNodeToLeft_n3) {
    TreeNode* root = initNode(1);
    addNode(&root, 0);
    EXPECT_EQ(root->left->data, 0);
    freeTree(root);
}

TEST(TreeTest, AddNodeToRight_n4) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    EXPECT_EQ(root->right->data, 2);
    freeTree(root);
}

TEST(TreeTest, AddNodeSeveralNodes_n5) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    EXPECT_EQ(root->right->data, 2);
    EXPECT_EQ(root->left->data, 0);
    EXPECT_EQ(root->left->left->data, -1);
    freeTree(root);
}

TEST(TreeTest, AddNodeEqualNode_n6) {
    TreeNode* root = initNode(1);
    addNode(&root, 1);
    EXPECT_EQ(root->right->data, 1);
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeRootIsNull_n7) {
    TreeNode* root = nullptr;
    EXPECT_FALSE(deleteSubtree(&root, 1));
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeNotNodeIsExsist_n8) {
    TreeNode* root = initNode(2);
    EXPECT_FALSE(deleteSubtree(&root, 1));
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeNormalCase_n9) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    EXPECT_TRUE(deleteSubtree(&root, 0));
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeDeleteSeveral_n10) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    EXPECT_TRUE(deleteSubtree(&root, 0));
    EXPECT_FALSE(deleteSubtree(&root, -1));
    freeTree(root);
}
