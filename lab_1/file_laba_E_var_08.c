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
