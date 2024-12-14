#define _CRT_SECURE_NO_WARNINGS
#ifndef code_h
#define code_h
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* insert(Node* root, int data);


void findKthSmallest(Node* root, int* count, int K, int* result);


void printElementsLessThanK(Node* root, int K, int* count);


void processKthSmallest(Node* root, int K);

#endif