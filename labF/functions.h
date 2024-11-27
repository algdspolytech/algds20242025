#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_RESULTS 100

typedef struct {
    int start;
    int end;
} interval;

typedef struct tree_node {
    interval i; 
    int maxEnd;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;


tree_node* create_node(interval interval);
void insert(tree_node **node, interval interval);
int find_intersections(tree_node* node, interval query, interval* array);
tree_node* find_min_node(tree_node* node);
tree_node* delete_node(tree_node* node, interval interval);
void print_tree(tree_node* node);




#endif