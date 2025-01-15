#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "labE_tests.h"

#define FIRST_TREE_NODE_PRINT_TREE (-1)

char *read_file(char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("File Not Found\n");
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *str = malloc(size + 1);
    if (str == NULL) {
        printf("Memory Allocation Failed, read_file\n");
        return NULL;
    }
    fread(str, size, 1, fp);
    fclose(fp);
    str[size] = '\0';
    return str;
}

void remove_spaces(char *str) {
    char *src = str;
    char *dest = str;
    while (*src != '\0') {
        if (*src != ' ') {
            *dest = *src;
            dest++;
        }
        src++;
    }
    *dest = '\0';
}

node *create_node(void) {
    node *node = malloc(sizeof(struct node));

    if (node == NULL) {
        printf("Memory Allocation Failed, create_node\n");
        return NULL;
    }

    node->data = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int get_len_node_data(const char *str) {
    int i = 0;
    while ((str)[i] != '\0' && (str)[i] != ')' && (str)[i] != '(') {
        i++;
    }
    return i;
}

char *parse_node_data(char *str) {
    int len = get_len_node_data(str);

    char *res_data = malloc(len + 1);
    if (res_data == NULL) {
        printf("Memory Allocation Failed, parse_node_data\n");
        return NULL;
    }

    memcpy(res_data, str, len);
    res_data[len] = '\0';
    return res_data;
}

node *parse_tree(char *str, size_t *offset) {
    char *data = parse_node_data(str);
    if (data == NULL) {
        return NULL;
    }
    size_t len = strlen(data);
    if (len == 0) {
        if (offset != NULL) {
            *offset = 0;
        }
        free(data);
        return NULL;
    }
    if (offset != NULL) {
        *offset = len;
    }
    node *node = create_node();
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    size_t off;
    str += len;
    if (*str == '(') {
        str++;
        node->left = parse_tree(str, &off);
        str += off;
        str++;
        if (offset != NULL) {
            *offset += off + 2;
        }
        if (*str == '(') {
            str++;
            node->right = parse_tree(str, &off);
            str += off;
            str++;
            if (offset != NULL) {
                *offset += off + 2;
            }
        }
    }
    return node;
}

void print_tree(node *tree, int level, int is_left) {
    if (tree == NULL) return;

    printf("\n");
    for (int i = 0; i < level; i++) {
        printf("<>");
    }
    if (is_left == FIRST_TREE_NODE_PRINT_TREE) {
        printf("%s", tree->data);
    } else if (is_left) {
        printf("left:  %s", tree->data);
    } else {
        printf("right: %s", tree->data);
    }

    print_tree(tree->left, level + 1, 1);
    print_tree(tree->right, level + 1, 0);
}

void free_tree(node *tree) {
    if (tree == NULL) {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    if (tree->data != NULL) free(tree->data);
    tree->data = NULL;
    free(tree);
}


int main(void) {
    tests();
    char *str = read_file("test2.txt");
    if (str == NULL) {
        printf("\n change file path; main\n");
        return 1;
    }

    remove_spaces(str);
    node *tree = parse_tree(str, NULL);
    print_tree(tree, 0, FIRST_TREE_NODE_PRINT_TREE);
    free_tree(tree);
    free(str);
    return 0;
}
