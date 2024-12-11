#include "tree.h"

Node * create_node(const char * name) {
    Node * node = (Node * ) malloc(sizeof(Node));
    strcpy(node -> name, name);
    node -> children = NULL;
    node -> children_count = 0;
    node -> children_capacity = 0;
    return node;
}

void add_path(Node * root,
    const char * path) {
    char buffer[MAX_PATH_LEN + 1];
    strcpy(buffer, path);
    char * token = strtok(buffer, "\\");
    Node * current = root;

    while (token) {
        int found = 0;

        for (int i = 0; i < current -> children_count; i++) {
            if (strcmp(current -> children[i] -> name, token) == 0) {
                current = current -> children[i];
                found = 1;
                break;
            }
        }

        if (!found) {
            if (current -> children_count == current -> children_capacity) {
                current -> children_capacity = current -> children_capacity == 0 ? 2 : current -> children_capacity * 2;
                current -> children = realloc(current -> children, current -> children_capacity * sizeof(Node * ));
            }

            Node * new_node = create_node(token);
            current -> children[current -> children_count++] = new_node;
            current = new_node;
        }

        token = strtok(NULL, "\\");
    }
}

void sort_children(Node * node) {
    if (node -> children_count == 0)
        return;

    for (int i = 0; i < node -> children_count - 1; i++) {
        for (int j = 0; j < node -> children_count - i - 1; j++) {
            if (strcmp(node -> children[j] -> name, node -> children[j + 1] -> name) > 0) {
                Node * temp = node -> children[j];
                node -> children[j] = node -> children[j + 1];
                node -> children[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < node -> children_count; i++) {
        sort_children(node -> children[i]);
    }
}

/* void write_tree_to_file(Node *root, FILE *file, int depth) {
    if (depth > 0) {  // Отступы добавляются только для непустого depth
        for (int i = 0; i < depth; i++) {
            fprintf(file, " ");
        }
    }
    if (depth > 0 || strcmp(root->name, "") != 0) { // Печатаем только непустые узлы
        printf("Condition met");
        fprintf(file, "%s\n", root->name);
    }

    for (int i = 0; i < root->children_count; i++) {
        write_tree_to_file(root->children[i], file, depth + 1);
    }
} */

void write_tree_to_file(Node * root, FILE * file, int depth) {
    int is_not_main_root = strcmp(root -> name, "");
    if (depth >= 0) {
        for (int i = 0; i < depth; i++) {
            fprintf(file, " ");
        }
        if (is_not_main_root != 0) {
            fprintf(file, "%s\n", root -> name);
        }
    }
    // printf("depth: %d , children: %d\n", depth, root->children_count);
    for (int i = 0; i < root -> children_count; i++) {
        if (is_not_main_root == 0) {
            // printf("Removed offset from %s for %s\n", root->name, root->children[i]);
            write_tree_to_file(root -> children[i], file, depth);
        } else {
            // printf("Not removed offset from %s for %s", root->name, root->children[i]);
            write_tree_to_file(root -> children[i], file, depth + 1);
        }
    }
}

void free_tree(Node * root) {
    for (int i = 0; i < root -> children_count; i++) {
        free_tree(root -> children[i]);
    }
    free(root -> children);
    free(root);
}