#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define MAX_WORD_LEN 100
#define MAX_LIST_SIZE 100

typedef struct {
    char word[MAX_WORD_LEN];
    int key;
} Item;

int scan_check(FILE* file, Item newItem) {
    if (fscanf(file, "%s %d", newItem.word, &newItem.key) == 2) {
        return 1;
    }
    else {
        return 0;
    }
}

void insert_sorted(Item list[], int* size, Item newItem) {
    int i;
    for (i = 0; i < *size; i++) {
        if (list[i].key == newItem.key) {
            printf("Error: keyword %d already exist for word %s \n", newItem.key,
                list[i].word);
            exit(EXIT_FAILURE);
        }
    }

    for (i = *size - 1; (i >= 0 && list[i].key > newItem.key); i--) {
        list[i + 1] = list[i];
    }
    list[i + 1] = newItem;
    (*size)++;
}

int print_list(Item list[], int size) {
    printf("List:\n");
    for (int i = 0; i < size; i++) {
        printf("%s %d \n", list[i].word, list[i].key);
    }
    if (size == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

int find_word_by_key(Item list[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (list[i].key == key) {
            printf("Word for keyword %d: %s\n", key, list[i].word);
            return 1;
        }
    }
    return 0;
}