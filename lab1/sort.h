#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char* val;
	struct Node* next;
} Node;

void push(Node* head, char* element);

void pop(Node* head, char* st);

int compareWords(char* a, char* b);

void insertAfter(Node* goal, char* val);

void merge(Node* h1, Node* h2);

void showList(Node* head);

void destroyList(Node* head);

#endif