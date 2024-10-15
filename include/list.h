#ifndef LAB1_LIST_H
#define LAB1_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    int len;
    char *str;
    struct List *next;
} List;


List* initList();


int createNode(struct List*, const char*);


int addToList(struct List*, const char*);
    

void deleteList(List*);


void printList(List*);


#endif 