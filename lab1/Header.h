#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct node { //связный список
	int data; 
	struct node* next;
}node;

typedef struct Set {//множество
	node* head;		//первый элемент, иначе корень
}Set;
Set* initialization();
bool contains(Set*, int);
void add(Set*, int);
bool removee(Set*, int);
Set* union_sets(Set*, Set*);
Set* intersection(Set*, Set*);
Set* free_set(Set*);
void print_set(Set*);

