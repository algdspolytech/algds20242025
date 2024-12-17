#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "lib.h"
#include "tests.h"


int main() {
    runAllTests();
    Node *root = NULL;
    char command[256];
    
    while (1) {
        printf("Input a command (insert, print, save, load, exit): ");
        scanf("%s", command);
        
        if (strcmp(command, "insert") == 0) {
            char data[256];
            printf("Input data: ");
            scanf("%s", data);
            root = insert(root, data);
        } else if (strcmp(command, "print") == 0) {
            printInOrder(root);
        } else if (strcmp(command, "save") == 0) {
            FILE *file = fopen("tree.txt", "w");
            if (file) {
                saveToFile(root, file);
                fclose(file);
                printf("Tree saved in tree.txt\n");
            } else {
                printf("Can't open the file!\n");
            }
        } else if (strcmp(command, "load") == 0) {
            FILE *file = fopen("tree.txt", "r");
            if (file) {
                freeTree(root);
                root = loadFromFile(file);
                fclose(file);
                printf("Tree loaded from tree.txt\n");
            } else {
                printf("Can't open the file!\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }
    }

    freeTree(root);
    return 0;
}
