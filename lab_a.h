#ifndef lab_a_h
#define lab_a_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Node {
    char* word;
    int key;
    struct Node* next;
} Node;

Node* createNode(const char* word, int key);

int insertSorted(Node** head, const char* word, int key);

void printList(Node* head);

const char* searchByKey(Node* head, int key);

#endif