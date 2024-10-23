#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <time.h>

#include <windows.h>

typedef struct Node {
	char* str;
	struct Node* next;
}
Node;

Node* init(char* s);
void add_node(Node* head, char* s);
int len_of_full_str(Node* head);
char* get_full_str(Node* head);
void print_list(Node* head);
void free_list(Node* head);

#endif