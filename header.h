#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>
#define CRT_SECURE_NO_WARNINGS

typedef struct Tree{
    int data;
    struct Tree* left;
    struct Tree* right;
}tree;

tree* insert(int data);
void addElement(tree** tr, int data);
void findKthSmallest(tree* tr, int k, int* count, int* result);
void printElementsLessThanK(tree* tr, int k, int* count);