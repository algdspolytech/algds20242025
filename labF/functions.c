#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "functions.h"

tree_node* create_node(interval interval) {
    tree_node* ans = (tree_node*)malloc(sizeof(tree_node));
    ans->i = interval;
    ans->maxEnd = interval.end;
    ans->left = NULL;
    ans->right = NULL;
    return ans;
}

void insert(tree_node** node, interval interval) {
    if (*node == NULL) {
        *node = create_node(interval);
        return;
    }

    if (interval.start < (*node)->i.start) {
        insert(&((*node)->left), interval);
    }
    else {
        insert(&((*node)->right), interval);
    }

    (*node)->maxEnd = ((*node)->maxEnd > interval.end) ? (*node)->maxEnd : interval.end;
}


int find_intersections(tree_node* node, interval query, interval* array) {
    if (node == NULL) {
        return 0;
    }

    int count = 0;

    if (query.start <= node->i.end && query.end >= node->i.start) {
        array[count++] = node->i;
    }

    if (node->left != NULL && node->left->maxEnd >= query.start) {
        count += find_intersections(node->left, query, &array[count]);
    }

    count += find_intersections(node->right, query, &array[count]);

    return count;
}

tree_node* find_min_node(tree_node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

tree_node* delete_node(tree_node* node, interval interval) {
    if (node == NULL) {
        return NULL;
    }

    if (interval.start < node->i.start) {
        node->left = delete_node(node->left, interval);
    }
    else if (interval.start > node->i.start) {
        node->right = delete_node(node->right, interval);
    }
    else {
        if (node->left == NULL) {
            tree_node* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            tree_node* temp = node->left;
            free(node);
            return temp;
        }

        tree_node* temp = find_min_node(node->right);
        node->i = temp->i;
        node->right = delete_node(node->right, temp->i);
    }

    if (node != NULL) {
        node->maxEnd = (node->right != NULL) ? (node->right->maxEnd > node->i.end ? node->right->maxEnd : node->i.end) : node->i.end;
        if (node->left != NULL) {
            node->maxEnd = (node->left->maxEnd > node->maxEnd) ? node->left->maxEnd : node->maxEnd;
        }
    }

    return node;
}

void print_tree(tree_node* node) {
    if (node == NULL) {
        return;
    }
    print_tree(node->left);
    printf("[%d, %d] ", node->i.start, node->i.end);
    print_tree(node->right);       
}