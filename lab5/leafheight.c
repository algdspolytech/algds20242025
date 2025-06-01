#include "leafheight.h"

Branch* createBranch() {
    Branch* newBranch = (Branch*)malloc(sizeof(Branch));
    newBranch->value = 0; 
    newBranch->left = NULL;
    newBranch->right = NULL;
    return newBranch;
}

void clearTree(Branch* root) {
    if (root == NULL) {
        fprintf(stderr, "Null Pointer Input");
        exit(1);
    }
    if (root->left!=NULL) {
        clearTree(root->left);
    }
    if (root->right != NULL) {
        clearTree(root->right);
    }
    free(root);
}

int minLeafHeight(Branch* root) {
    if (root == NULL) {
        return -1;
    }
    else if (root->left == NULL && root->right == NULL) {
        return 0;
    } 
    else {
        int rightHeight = minLeafHeight(root->right);
        int leftHeight = minLeafHeight(root->left);

        if (root->right == NULL) {
            return leftHeight + 1;
        }
        if (root->left == NULL) {
            return rightHeight + 1;
        }
        if (leftHeight < rightHeight) {
            return leftHeight + 1;
        }
        else {
            return rightHeight + 1;
        }
    }
}

void updateMinLeafHeights(Branch* root) {
    if (root == NULL)
        return;
    root->value = minLeafHeight(root);
    updateMinLeafHeights(root->left);
    updateMinLeafHeights(root->right);
}

void printTreeToFile(Branch* root, int space, FILE* file) {
    if (root == NULL) {
        return;
    }
    space += 5;
    printTreeToFile(root->right, space, file);

    fprintf(file, "\n");
    for (int i = 5; i < space; i++) {
        fprintf(file, " ");
    }
    fprintf(file, "%d\n", root->value);

    printTreeToFile(root->left, space, file);
}