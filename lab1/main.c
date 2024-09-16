#include <malloc.h>
#include <stdio.h>
#include <intrin.h>

#include "main.h"
#include "test/tests.h"

List *initList(char *word) {
    List *tr = malloc(sizeof(List));
    tr->len = strlen(word);
    tr->word = malloc(sizeof(char) * (tr->len + 1));
    strcpy(tr->word, word);
    tr->next = NULL;
    return tr;
}

//my own lexico-len-graphical strcmp
int cmpstr(int lena, const char *a, int lenb, const char *b) {
    if (lena == lenb) return strcmp(a, b);
    if (lena < lenb) return -1;
    else return 1;
}

List *addToList(List *l, List *toAdd) {
    if (l == NULL || toAdd == NULL) return l;
    if (cmpstr(toAdd->len, toAdd->word, l->len, l->word) <= 0) {
        toAdd->next = l;
        return toAdd;
    }

    List *iter = l;
    while (iter->next != NULL && cmpstr(iter->next->len, iter->next->word, toAdd->len, toAdd->word) < 0) {
        iter = iter->next;
    }
    toAdd->next = iter->next;
    iter->next = toAdd;

    return l;
}

void deleteList(List *l) {
    while (l != NULL) {
        List *next = l->next;
        free(l->word);
        free(l);
        l = next;
    }
}

void printList(List *l) {
    do {
        printf("%s: %d\n", l->word, l->len);
        l = l->next;
    } while (l != NULL);
}

int check_if_contains(List *l, int len) {
    while (l != NULL && l->len < len) l = l->next;
    if (l != NULL && l->len == len) return 1;
    else return 0;
}

List *List_longer_n(List *l, int len) {
    while (l != NULL && l->len <= len) l = l->next;
    return l;
}

int main() {
    runAllTests();
    const char *filename = "../input.txt";
    FILE *f = fopen(filename, "r");
    if (f) {
        char *s;
        fscanf(f, "%s", s);
        List *l = initList(s);
        while (fscanf(f, "%s", s) == 1) {
            l = addToList(l, initList(s));
        }
        int len = 0;
        printf("Printing all list:\n");
        printList(l);
        printf("Printing all words larger that: ");
        scanf("%d", &len);
        printList(List_longer_n(l, len));
        if (check_if_contains(l, len)) {
            printf("List contains word with this length %d\n", len);
        } else {
            printf("List does not contains word with length %d\n", len);
        }

        deleteList(l);


    } else {
        printf("Failed to open file: %s\n", filename);
    }
    return 0;
}