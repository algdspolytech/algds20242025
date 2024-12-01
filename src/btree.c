#include "btree.h"


static struct btree* initLeaf(char val)
{
    struct btree* tree = malloc(sizeof(struct btree));
    tree->left = NULL;
    tree->right = NULL;
    tree->value = val;
    tree->leaf_count = 0;
    return tree;
}

void pushBack(struct btree** tree, char val)
{
    if(*tree == NULL) *tree = initLeaf(val);
    else if ((*tree)->value == val) return;
    else if((*tree)->value < val) pushBack(&(*tree)->right, val);
    else pushBack(&(*tree)->left, val);
}

static unsigned int get_height(struct btree* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

unsigned int countLeafs(struct btree* tree)
{
    if(tree == NULL) return 0;
    if(tree->left == NULL && tree->right == NULL)
    {
        tree->leaf_count = 1;
        return 1;
    }
    tree->leaf_count = countLeafs(tree->right) + countLeafs(tree->left);
    return tree->leaf_count; 
}

static void fillMatrix(struct btree* tree, int** matrix, int row, int col, int width) {
    if (tree == NULL) {
        return;
    }
    matrix[row][col] = tree->leaf_count;
    fillMatrix(tree->left, matrix, row + 1, col - width / 2, width / 2);
    fillMatrix(tree->right, matrix, row + 1, col + width / 2, width / 2);
}

int** getMatrix(struct btree* tree, unsigned int* height, unsigned int* width)
{
    *height = get_height(tree);
    *width = pow(2, *height) - 1;
    int** matrix = malloc(sizeof(int*) * *height);
    for(int i = 0; i < *height; ++i) 
    { 
        matrix[i] = malloc(sizeof(int) * *width * 3);
        for(int j = 0; j < *width; ++j) matrix[i][j] = 0;
    }
    fillMatrix(tree, matrix, 0, (*width - 1) / 2, *width / 2);
    return matrix;
}

void printMatrix(int** matrix, unsigned int height, unsigned int width)
{
    for(unsigned int i = 0; i < height; ++i)
    {
        for(unsigned int j = 0; j < width; ++j)
        {
            if(matrix[i][j] != 0) printf("%d ", matrix[i][j]);
            else printf("  ");
        }
        printf('\n');
    }
}

void deleteTree(struct btree* tree)
{
    if(tree == NULL) return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}


