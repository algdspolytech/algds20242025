#include <stdio.h>
#include <stdlib.h>
#include "code.h"



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


void findKthSmallest(Node* root, int* count, int K, int* result) {
    if (root == NULL || *count >= K) {
        return;
    }

    
    findKthSmallest(root->left, count, K, result);

    
    (*count)++;
    if (*count == K) {
        *result = root->data;
        return;
    }

    
    findKthSmallest(root->right, count, K, result);
}


void printElementsLessThanK(Node* root, int K, int* count) {
    if (root == NULL || *count >= K) {
        return;
    }


    printElementsLessThanK(root->left, K, count);


    if (*count < K) {
        printf("%d ", root->data);
    }
    (*count)++;


    printElementsLessThanK(root->right, K, count);
}

void processKthSmallest(Node* root, int K) {
    int count = 0;
    int result = 0;


    findKthSmallest(root, &count, K, &result);


    if (count < K) {
        printf("\nЁлемент с пор€дковым номером K не найден.\n");
        return;
    }

    if (result % 2 == 0) {
        printf("\nK-й наименьший элемент: %d", result);
        count = 0; 
        printf("Ёлементы с пор€дковыми номерами меньше K: ");
        printElementsLessThanK(root, K, &count);
        printf("\n");
    }
    else {
        printf("\nK-й наименьший элемент: %d (нечетный)\n", result);
    }
}
