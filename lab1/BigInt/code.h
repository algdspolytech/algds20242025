#ifndef code_h
#define code_h

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
	int value;
	struct Node* next;
} Node;

typedef struct BigInt
{
	Node* head;
	Node* tail;
} BigInt;

void append(BigInt* list, int item);

void rappend(BigInt* list, int item);

BigInt* init(int count, ...);

BigInt* copy(BigInt* list);

void delete(BigInt* list);

void reverse(BigInt* list);

void print(BigInt* list);

BigInt* add(BigInt* a, BigInt* b);

BigInt* mul(BigInt* a, BigInt* b);

BigInt* sub(BigInt* a, BigInt* b);

int equal(BigInt* a, BigInt* b);

BigInt* bigpow(BigInt* a, BigInt* b);
#endif