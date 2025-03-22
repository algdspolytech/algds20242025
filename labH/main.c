#pragma warning(disable : 4996)
#include "rbtree.h"
#include <time.h>

typedef struct BSTnode {
    int data;
    struct BSTnode* left, * right;
} BSTnode;

BSTnode* createBSTNode(int data) {
    BSTnode* newNode = (BSTnode*)malloc(sizeof(BSTnode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertBST(BSTnode** root, int data) {
    if (*root == NULL) {
        *root = createBSTNode(data);
        return;
    }
    if (data < (*root)->data)
        insertBST(&((*root)->left), data);
    else
        insertBST(&((*root)->right), data);
}

double measureTime(void (*function)(void**, int), void** root) {
    clock_t start, end;

    const int N = 100000;
    int* data = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        data[i] = rand();
    }

    start = clock();
    for (int i = 0; i < N; i++) {
        function(root, data[i]);
    }
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    BSTnode* bstRoot = NULL;
    Node* rbtRoot = NULL;

    double bsTime =
        measureTime((void (*)(void**, int))insertBST, (void**)&bstRoot);
    printf("insert BS Tree: %f seconds\n", bsTime);

    double rbTime =
        measureTime((void (*)(void**, int))insertRBT, (void**)&rbtRoot);
    printf("insert RB Tree: %f seconds\n", rbTime);

    return 0;
}