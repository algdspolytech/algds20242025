#ifndef LAB1_MAIN_H
#define LAB1_MAIN_H

typedef struct List {
    int len;
    char *word;
    struct List *next;
} List;

List *initList(char *word);

int cmpstr(int lena, const char *a, int lenb, const char *b);

List *addToList(List *l, List *toAdd);

void deleteList(List *l);

void printList(List *l);

int check_if_contains(List *l, int len);

List *List_longer_n(List *l, int len);


#endif //LAB1_MAIN_H
