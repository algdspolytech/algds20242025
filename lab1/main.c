#include "tree.h"

int main() {
    FILE * input = fopen("input.txt", "r");
    FILE * output = fopen("output.txt", "w");

    if (!input || !output) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int n;
    fscanf(input, "%d\n", & n);

    Node * root = create_node("");

    char path[MAX_PATH_LEN + 1];
    for (int i = 0; i < n; i++) {
        fgets(path, sizeof(path), input);
        path[strcspn(path, "\n")] = '\0';
        add_path(root, path);
    }

    sort_children(root);
    write_tree_to_file(root, output, 0);

    free_tree(root);
    fclose(input);
    fclose(output);

    return 0;
}