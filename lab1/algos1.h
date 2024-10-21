
#pragma once
#ifndef ALGOS1_H
#define ALGOS1_H
#ifdef __cplusplus  
extern "C" {
#endif  

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#define MAX_CHILDREN 500
#define MAX_NAME_LENGTH 9

    typedef struct Node {
        char name[MAX_NAME_LENGTH];
        struct Node* children[MAX_CHILDREN];
        int child_count;
    } Node;

    // Объявления функций
    Node* create_node(const char* name);
    int add_path(Node* root, const char* path);
    int compare(const void* a, const void* b);
    void free_tree(Node* root);
    void print_tree(Node* root, int level, FILE* filename);


#ifdef __cplusplus  
}
#endif  

#endif 
