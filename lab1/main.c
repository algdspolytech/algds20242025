#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <locale.h>  
#include "algos1/algos1.h"  
#include <string.h>

int main() {
    setlocale(LC_ALL, "RUS");

    FILE* input_file = fopen("../input.txt", "r");
    FILE* output_file = fopen("../output.txt", "w");

    if (!input_file || !output_file) {
        perror("Ошибка открытия файла\n");
        exit(1);
    }

    int N;
    fscanf(input_file, "%d\n", &N);

    Node* tree = create_node("");

    for (int i = 0; i < N; i++) {
        char path[256];
        fgets(path, sizeof(path), input_file);

        for (int pos = 0; path[pos] != '\0'; pos++) {
            if (path[pos] == '\n') {
                path[pos] = '\0';
                break;
            }
        }
        add_path(tree, path);
    }

    print_tree(tree, 0, output_file);

    fclose(input_file);
    fclose(output_file);

    free_tree(tree);
    return 0;
}