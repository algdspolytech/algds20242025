#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>

#include "algos1.h"

Node* create_node(const char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    strncpy(new_node->name, name, MAX_NAME_LENGTH - 1);
    new_node->name[MAX_NAME_LENGTH - 1] = '\0';
    new_node->child_count = 0;
    return new_node;
}

int add_path(Node* root, const char* path) {
    char* folder_name;
    char* path_copy = (char*)malloc(256 * sizeof(char));
    if (path_copy == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    strcpy(path_copy, path);
    Node* current = root;

    folder_name = strtok(path_copy, "\\");
    while (folder_name != NULL) {
        int found_name = 0;
        for (int i = 0; i < current->child_count; i++) {
            if (strcmp(current->children[i]->name, folder_name) == 0) {
                current = current->children[i];
                found_name = 1;
                break;
            }
        }
        if (!found_name) {
            Node* new_child = create_node(folder_name);
            current->children[current->child_count] = new_child;
            current->child_count++;
            current = new_child;
        }
        folder_name = strtok(NULL, "\\");
    }

    free(path_copy);
    return 0;
}

int compare(const void* a, const void* b) {
    Node* node_a = *(Node**)a;
    Node* node_b = *(Node**)b;
    return strcmp(node_a->name, node_b->name);
}

void print_tree(Node* node, int level, FILE* filename) {

    if (node == NULL) return;

    qsort(node->children, node->child_count, sizeof(Node*), compare);

    for (int i = 0; i < node->child_count; i++) {
        for (int j = 0; j < level; j++) {
            fprintf(filename, " ");
        }
        fprintf(filename, "%s\n", node->children[i]->name);
        print_tree(node->children[i], level + 1, filename);
    }
}

void free_tree(Node* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->child_count; i++) {
        free_tree(node->children[i]);
    }
    free(node);
}

