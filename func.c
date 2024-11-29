#include "header.h"
tree* insert(int data) {
    tree* tmp = (tree*)malloc(sizeof(tree));

    if (tmp == NULL) {
        printf("malloc error\n");
        exit(1);
    }

    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

void addElement(tree** tr, int data) {
    if (*tr == NULL) {
        *tr = insert(data);
    }
    else {
        tree* tmp = *tr;
        if (data > tmp->data) {
            if (tmp->right == NULL) {
                tmp->right = insert(data);
            }
            else {
                addElement(&(tmp->right), data);
            }
        }
        else if (data < tmp->data) {
            if (tmp->left == NULL) {
                tmp->left = insert(data);
            }
            else {
                addElement(&(tmp->left), data);
            }
        }
    }
}

void findKthSmallest(tree* tr, int k, int* count, int* result) {
    if (tr == NULL || *count >= k) {
        return;
    }

    findKthSmallest(tr->left, k, count, result);

    (*count)++;
    if (*count == k) {
        *result = tr->data;
        return;
    }

    findKthSmallest(tr->right, k, count, result);
}

void printElementsLessThanK(tree* tr, int k, int* count) {
    if (tr == NULL || *count >= k) {
        return;
    }

    printElementsLessThanK(tr->left, k, count);

    (*count)++;
    if (*count < k) {
        printf("%d ", tr->data);
    }

    printElementsLessThanK(tr->right, k, count);
}
