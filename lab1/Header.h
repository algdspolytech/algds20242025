#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


typedef struct node
{ 
	int data;
	struct node *next;
} node;

typedef struct Set
{				
	node *head;
} Set;

Set *initialization();
bool contains(Set *, int);
void add(Set *, int);
bool removee(Set *, int);
Set *union_sets(Set *, Set *);
Set *intersection(Set *, Set *);
Set *free_set(Set *);
void print_set(Set *);
