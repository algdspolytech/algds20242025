#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100003
#define MAX_STRING_LENGTH 100

typedef struct {
    int key;
    char value[MAX_STRING_LENGTH];
} Element;

Element* table[TABLE_SIZE];
Element* DELETED = (Element*)-1;

int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return 1 + (key % (TABLE_SIZE - 1));
}

void insert(int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;
    int first_deleted = -1;

    while (table[(index + i * step) % TABLE_SIZE] != NULL) {
        int current = (index + i * step) % TABLE_SIZE;
        if (table[current] == DELETED) {
            if (first_deleted == -1) first_deleted = current;
        }
        else if (table[current]->key == key) {
            return;
        }
        i++;
    }

    int target = (first_deleted != -1) ? first_deleted : (index + i * step) % TABLE_SIZE;
    table[target] = (Element*)malloc(sizeof(Element));
    table[target]->key = key;
    sprintf(table[target]->value, "Element %d", key);
}

void remove_element(int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    while (table[(index + i * step) % TABLE_SIZE] != NULL) {
        int current = (index + i * step) % TABLE_SIZE;
        if (table[current] != DELETED && table[current]->key == key) {
            free(table[current]);
            table[current] = DELETED;
            return;
        }
        i++;
    }
}

int find(int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    while (table[(index + i * step) % TABLE_SIZE] != NULL) {
        int current = (index + i * step) % TABLE_SIZE;
        if (table[current] != DELETED && table[current]->key == key) {
            return 1;
        }
        i++;
    }

    return 0;
}

int main() {
    char operation;
    int key;

    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    while (scanf(" %c %d", &operation, &key) != EOF) {
        if (operation == 'a') {
            insert(key);
        }
        else if (operation == 'r') {
            remove_element(key);
        }
        else if (operation == 'f') {
            if (find(key)) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL && table[i] != DELETED) {
            free(table[i]);
        }
    }

    return 0;
}
