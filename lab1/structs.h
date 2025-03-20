#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node* left, * right, * parent;
} Node;

typedef struct RBTree {
    Node* root;
} RBTree;

#endif