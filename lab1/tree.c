
#include "tree.h"
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 256
Node* create_node(const char* name) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->subdir_count = 0;
    return node;
}

void add_subdir(Node* parent, Node* subdir) {
    parent->subdirs[parent->subdir_count++] = subdir;
}


int compare_nodes(const void* a, const void* b) {
    Node* nodeA = *(Node**)a;
    Node* nodeB = *(Node**)b;
    return strcmp(nodeA->name, nodeB->name);
}

void print_tree(Node* node, int level, FILE* output) {
    if (strlen(node->name) > 0) {
        for (int i = 1; i < level; i++) {
            fprintf(output, " ");
        }
        fprintf(output, "%s\n", node->name);
    }

    qsort(node->subdirs, node->subdir_count, sizeof(Node*), compare_nodes);

    for (int i = 0; i < node->subdir_count; i++) {
        print_tree(node->subdirs[i], level + 1, output);
    }
}

void free_tree(Node* node) {
    for (int i = 0; i < node->subdir_count; i++) {
        free_tree(node->subdirs[i]);
    }
    free(node);
}
void build_directory_tree(const char* input_file, const char* output_file) {
    FILE* input = fopen(input_file, "r");
    FILE* output = fopen(output_file, "w");

    if (input == NULL || output == NULL) {
        perror("Error opening file");
        return;
    }

    int N;
    fscanf(input, "%d\n", &N);

    if (N == 0) {
        Node* root = create_node("root");
        print_tree(root, 0, output);
        free_tree(root);
        fclose(input);
        fclose(output);
    }
    else{
        Node* root = create_node("");
        for (int i = 0; i < N; i++) {
            char path[256];
            fgets(path, sizeof(path), input);

            path[strcspn(path, "\n")] = 0;

            char* token = strtok(path, "\\");
            Node* current = root;

            while (token != NULL) {
                int found = 0;
                for (int j = 0; j < current->subdir_count; j++) {
                    if (strcmp(current->subdirs[j]->name, token) == 0) {
                        current = current->subdirs[j];
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    Node* new_node = create_node(token);
                    add_subdir(current, new_node);
                    current = new_node;
                }

                token = strtok(NULL, "\\");
            }
        }

        print_tree(root, 0, output);

        free_tree(root);
        fclose(input);
        fclose(output);
    }

}
