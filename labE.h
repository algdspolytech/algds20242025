#ifndef LABE_H
#define LABE_H

typedef struct node {
    char *data;
    struct node *left;
    struct node *right;
} node;

void free_tree(node *tree);

node *parse_tree(char *str, size_t *);

void remove_spaces(char *str);

char *read_file(char *file_name);

void print_tree(node *tree, int level, int is_left);
#endif //LABE_H
